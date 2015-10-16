//
//  GameViewController.m
//  AppFrame
//
//  Created by Yuan Li on 2015/09/19.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#import "GameViewController.h"
#import "SharedStructures.h"
#import "MainLoop_Bridge.h"
#import "Graphics_Bridge.hpp"
#import <simd/simd.h>

//@import simd;
@import ModelIO;

// The max number of command buffers in flight
//this should be a very large num for each object
static NSUInteger kMaxInflightBuffers = 3;

// Max API memory buffer size.
static const size_t kMaxBytesPerFrame = 1024*1024*128;


id <MTLDevice> _device;

@implementation GameViewController
{
    // view
    MTKView *_view;
    
    // controller
    dispatch_semaphore_t _inflight_semaphore;
    id <MTLBuffer> _dynamicConstantBuffer;
    uint8_t _constantDataBufferIndex;
    
    // renderer
    id <MTLCommandQueue> _commandQueue;
    id <MTLLibrary> _defaultLibrary;
    id <MTLRenderPipelineState> _pipelineState;
    id <MTLDepthStencilState> _depthState;
    
    id<MTLTexture> framebufferTexture;
    
    // uniforms
    matrix_float4x4 _projectionMatrix;
    matrix_float4x4 _viewMatrix;
    uniforms_t _uniform_buffer;
    float _rotation;
    
    // meshes
    MTKMesh *_boxMesh;
    
    NSDate *start;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    
    _constantDataBufferIndex = 0;
    _inflight_semaphore = dispatch_semaphore_create(kMaxInflightBuffers);
    
    [self _setupMetal];
    [self _setupView];
    [self _loadAssets];
    [self _reshape];
    
    self.debugLabel.text = [NSString stringWithFormat:@"%f", self.slider.value];
    
    MainLoopBridge_StartGameLoop();
}

- (void)_setupView
{
    _view = (MTKView *)self.view;
    _view.device = _device;
    _view.delegate = self;
    
    // Setup the render target, choose values based on your app
    _view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
}


- (void)_setupMetal
{
    // Set the view to use the default device
    _device = MTLCreateSystemDefaultDevice();
    
    // Create a new command queue
    _commandQueue = [_device newCommandQueue];
    
    // Load all the shader files with a metal file extension in the project
    _defaultLibrary = [_device newDefaultLibrary];
}

-(IBAction)sliderValueChanged:(UISlider *)sender
{
    self.debugLabel.text = [NSString stringWithFormat:@"%f", sender.value];
}
-(IBAction)OnClick:(UIButton *)
{
    
}

void* Graphics_CreateMesh(enum MeshType Type)
{
    switch (Type)
    {
        case CUBE:
        {
            MDLMesh *mdl = [MDLMesh newBoxWithDimensions:(vector_float3){1,1,1}
                                                segments:(vector_uint3){2,2,2}
                                                geometryType:MDLGeometryTypeTriangles
                                                inwardNormals:NO
                                                allocator:[[MTKMeshBufferAllocator alloc] initWithDevice: _device]];
            
            MTKMesh* Ret = [[MTKMesh alloc] initWithMesh:mdl device:_device error:nil];
            return (__bridge_retained void*)Ret;
        }
        case SPHERE:
        {
            MDLMesh *mdl = [MDLMesh newEllipsoidWithRadii:(vector_float3){1,1,1}
                                    radialSegments:5
                                    verticalSegments:5
                                    geometryType:MDLGeometryTypeTriangles
                                    inwardNormals:NO
                                    hemisphere:NO
                                    allocator:[[MTKMeshBufferAllocator alloc] initWithDevice: _device]];
            
            MTKMesh* Ret = [[MTKMesh alloc] initWithMesh:mdl device:_device error:nil];
            return (__bridge_retained void*)Ret;
        }
        case PLANE:
        {
            MDLMesh *mdl = [MDLMesh newPlaneWithDimensions:(vector_float2){1,1}
                                    segments:(vector_uint2){2,2}
                                    geometryType:MDLGeometryTypeTriangles
                                    allocator:[[MTKMeshBufferAllocator alloc] initWithDevice: _device]];
            
            MTKMesh* Ret = [[MTKMesh alloc] initWithMesh:mdl device:_device error:nil];
            return (__bridge_retained void*)Ret;
            
        }
        default:
            break;
    }
    
    return nil;
}

- (void)_loadAssets
{
    start = [NSDate date];
    
    
    // Generate meshes
    MDLMesh *mdl = [MDLMesh newBoxWithDimensions:(vector_float3){2,2,2} segments:(vector_uint3){1,1,1}
                                    geometryType:MDLGeometryTypeTriangles inwardNormals:NO
                                       allocator:[[MTKMeshBufferAllocator alloc] initWithDevice: _device]];
    
    _boxMesh = [[MTKMesh alloc] initWithMesh:mdl device:_device error:nil];
    
    
    // Allocate one region of memory for the uniform buffer
    _dynamicConstantBuffer = [_device newBufferWithLength:kMaxBytesPerFrame options:0];
    _dynamicConstantBuffer.label = @"UniformBuffer";
    
    // Load the fragment program into the library
    id <MTLFunction> fragmentProgram = [_defaultLibrary newFunctionWithName:@"lighting_fragment"];
    
    // Load the vertex program into the library
    id <MTLFunction> vertexProgram = [_defaultLibrary newFunctionWithName:@"lighting_vertex"];
    
    // Create a vertex descriptor from the MTKMesh
    MTLVertexDescriptor *vertexDescriptor = MTKMetalVertexDescriptorFromModelIO(_boxMesh.vertexDescriptor);
    vertexDescriptor.layouts[0].stepRate = 1;
    vertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
    
    // Create a reusable pipeline state
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"MyPipeline";
    pipelineStateDescriptor.sampleCount = _view.sampleCount;
    pipelineStateDescriptor.vertexFunction = vertexProgram;
    pipelineStateDescriptor.fragmentFunction = fragmentProgram;
    pipelineStateDescriptor.vertexDescriptor = vertexDescriptor;
    
    pipelineStateDescriptor.colorAttachments[0].blendingEnabled = NO;
    pipelineStateDescriptor.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
    pipelineStateDescriptor.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    pipelineStateDescriptor.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorZero;
    pipelineStateDescriptor.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorZero;
    pipelineStateDescriptor.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
    pipelineStateDescriptor.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = _view.colorPixelFormat;
    pipelineStateDescriptor.depthAttachmentPixelFormat = _view.depthStencilPixelFormat;
    pipelineStateDescriptor.stencilAttachmentPixelFormat = _view.depthStencilPixelFormat;
    
    
    id<CAMetalDrawable> drawable = _view.currentDrawable;
    id<MTLTexture> backbuffer = drawable.texture;
    
    MTLTextureDescriptor* txDesc = [[MTLTextureDescriptor alloc] init];
    txDesc.textureType = [backbuffer textureType];
    txDesc.height = [backbuffer height];
    txDesc.width = [backbuffer width];
    txDesc.depth = [backbuffer depth];
    txDesc.pixelFormat = [backbuffer pixelFormat];
    txDesc.arrayLength = 1;
    txDesc.mipmapLevelCount = 1;
    //framebufferTexture =[_device newTextureWithDescriptor:txDesc];

    
    NSError *error = NULL;
    _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error];
    if (!_pipelineState) {
        NSLog(@"Failed to created pipeline state, error %@", error);
    }
    
    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];
}

- (void)_render
{
    dispatch_semaphore_wait(_inflight_semaphore, DISPATCH_TIME_FOREVER);

    // Create a new command buffer for each renderpass to the current drawable
    id <MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label = @"MyCommand";

    // Call the view's completion handler which is required by the view since it will signal its semaphore and set up the next buffer
    __block dispatch_semaphore_t block_sema = _inflight_semaphore;
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        dispatch_semaphore_signal(block_sema);
        
    }];
    
    // Obtain a renderPassDescriptor generated from the view's drawable textures
    MTLRenderPassDescriptor* renderPassDescriptor = _view.currentRenderPassDescriptor;
    
    
    
    id<CAMetalDrawable> drawable = _view.currentDrawable;
    renderPassDescriptor.colorAttachments[0].texture = [drawable texture];
    
    renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
    renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(0.3,0.3,0.3,1.0);

    if(renderPassDescriptor != nil) // If we have a valid drawable, begin the commands to render into it
    {
        Graphics_LockRenderQueue();
        
        if(!Graphics_IsRenderQueueEmpty())
        {
            unsigned long BufferCount = 0;
            
            // Create a render command encoder so we can render into something
            id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
            renderEncoder.label = @"MyRenderEncoder";
            [renderEncoder setDepthStencilState:_depthState];
            
            while (!Graphics_IsRenderQueueEmpty())
            {              
                void* MeshData = Graphics_PopAndGetMeshData();                
                _boxMesh = (__bridge MTKMesh*)Graphics_GetRawData(MeshData);                
                
                if (_boxMesh != nil)
                {
                    // Set context state
                    [renderEncoder pushDebugGroup:[_boxMesh name]];
                    [renderEncoder setRenderPipelineState:_pipelineState];
                    [renderEncoder setVertexBuffer:_boxMesh.vertexBuffers[0].buffer offset:_boxMesh.vertexBuffers[0].offset atIndex:0 ];
                        
                    float x = 0;
                    float y = 0;
                    float z = 0;
                    float xSacle = 1;
                    float ySacle = 1;
                    float zSacle = 1;
                    Graphics_GetLocation(MeshData, &x, &y, &z);
                    Graphics_GetScale(MeshData, &xSacle, &ySacle, &zSacle);
                    
                    matrix_float4x4 base_model = matrix_identity_float4x4;
                    base_model = matrix_multiply(matrix_from_scale(xSacle,ySacle,zSacle)	, base_model);
					//base_model = matrix_multiply(matrix_from_rotation(0, 0.0f, 1.0f, 0.0f)	, base_model);
					base_model = matrix_multiply(matrix_from_translation(x, y, z)			, base_model);
                    matrix_float4x4 base_mv = matrix_multiply(_viewMatrix, base_model);
                    matrix_float4x4 modelViewMatrix = matrix_multiply(base_mv, matrix_from_rotation(0, 1.0f, 1.0f, 1.0f));
                    
                    // Load constant buffer data into appropriate buffer at current index
                    uniforms_t *uniforms = &((uniforms_t *)[_dynamicConstantBuffer contents])[BufferCount];
                    
                    uniforms->normal_matrix = matrix_invert(matrix_transpose(modelViewMatrix));
                    uniforms->modelview_projection_matrix = matrix_multiply(_projectionMatrix, modelViewMatrix);
                    
                    [renderEncoder setVertexBuffer:_dynamicConstantBuffer offset:(sizeof(uniforms_t)*BufferCount) atIndex:1 ];                    
                    BufferCount++;                    
                    MTKSubmesh* submesh = _boxMesh.submeshes[0];
                    // Tell the render context we want to draw our primitives
                    [renderEncoder drawIndexedPrimitives:submesh.primitiveType indexCount:submesh.indexCount indexType:submesh.indexType indexBuffer:submesh.indexBuffer.buffer indexBufferOffset:submesh.indexBuffer.offset];
                    
                    [renderEncoder popDebugGroup];
                    
                }
                
            }            
            // We're done encoding commands
            [renderEncoder endEncoding];
        }
        
        Graphics_UnlockRenderQueue();
        
        
        // Schedule a present once the framebuffer is complete using the current drawable
        [commandBuffer presentDrawable:_view.currentDrawable];
        
        
        // Finalize rendering here & push the command buffer to the GPU
        [commandBuffer commit];
    }
}

/*static simd::float4x4 lookAt(   const simd::float3& eye,
                             const simd::float3& center,
                             const simd::float3& up);
   
static simd::float4x4 lookAt(   const simd::float3& eye,
                            const simd::float3& center,
                            const simd::float3& up)
{
    simd::float3 zAxis = simd::normalize(center - eye);
    simd::float3 xAxis = simd::normalize(simd::cross(up, zAxis));
    simd::float3 yAxis = simd::cross(zAxis, xAxis);
    
    simd::float4 P;
    simd::float4 Q;
    simd::float4 R;
    simd::float4 S;
    
    P.x = xAxis.x;
    P.y = yAxis.x;
    P.z = zAxis.x;
    P.w = 0.0f;
    
    Q.x = xAxis.y;
    Q.y = yAxis.y;
    Q.z = zAxis.y;
    Q.w = 0.0f;
    
    R.x = xAxis.z;
    R.y = yAxis.z;
    R.z = zAxis.z;
    R.w = 0.0f;
    
    S.x = -simd::dot(xAxis, eye);
    S.y = -simd::dot(yAxis, eye);
    S.z = -simd::dot(zAxis, eye);
    S.w =  1.0f;
    
    return simd::float4x4(P, Q, R, S);
} // lookAt*/

- (void)_reshape
{
    // When reshape is called, update the view and projection matricies since this means the view orientation or size changed
    float aspect = fabs(self.view.bounds.size.width / self.view.bounds.size.height);
    _projectionMatrix = matrix_from_perspective_fov_aspectLH(65.0f * (M_PI / 180.0f), aspect, 0.1f, 1000.0f);
    
    //_viewMatrix = matrix_identity_float4x4;
	float ViewMatrix[4][4];

	Graphics_GetCameraViewMatrix(ViewMatrix);
    matrix_float4x4 newView =  {
        .columns[0] = { ViewMatrix[0][0], ViewMatrix[0][1], ViewMatrix[0][2], ViewMatrix[0][3] },
        .columns[1] = { ViewMatrix[1][0], ViewMatrix[1][1], ViewMatrix[1][2], ViewMatrix[1][3] },
        .columns[2] = { ViewMatrix[2][0], ViewMatrix[2][1], ViewMatrix[2][2], ViewMatrix[2][3] },
        .columns[3] = { ViewMatrix[3][0], ViewMatrix[3][1], ViewMatrix[3][2], ViewMatrix[3][3] },
    };
    
    _viewMatrix = newView;
    
}

- (void)_update
{

}

// Called whenever view changes orientation or layout is changed
- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    [self _reshape];
}


// Called whenever the view needs to render
- (void)drawInMTKView:(nonnull MTKView *)view
{
    @autoreleasepool {
        [self _render];
    }
}

#pragma mark Utilities

static matrix_float4x4 matrix_from_perspective_fov_aspectLH(const float fovY, const float aspect, const float nearZ, const float farZ)
{
    float yscale = 1.0f / tanf(fovY * 0.5f); // 1 / tan == cot
    float xscale = yscale / aspect;
    float q = farZ / (farZ - nearZ);
    
    matrix_float4x4 m = {
        .columns[0] = { xscale, 0.0f, 0.0f, 0.0f },
        .columns[1] = { 0.0f, yscale, 0.0f, 0.0f },
        .columns[2] = { 0.0f, 0.0f, q, 1.0f },
        .columns[3] = { 0.0f, 0.0f, q * -nearZ, 0.0f }
    };
    
    return m;
}

static matrix_float4x4 matrix_from_translation(float x, float y, float z)
{
    matrix_float4x4 m = matrix_identity_float4x4;
    m.columns[3] = (vector_float4) { x, y, z, 1.0 };
    return m;
}
static matrix_float4x4 matrix_from_scale(float x, float y, float z)
{
	matrix_float4x4 m = matrix_identity_float4x4;
    m.columns[0][0] = x;
    m.columns[1][1] = y;
    m.columns[2][2] = z;
    return m;
}

static matrix_float4x4 matrix_from_rotation(float radians, float x, float y, float z)
{
    vector_float3 v = vector_normalize(((vector_float3){x, y, z}));
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    matrix_float4x4 m = {
        .columns[0] = {
            cos + cosp * v.x * v.x,
            cosp * v.x * v.y + v.z * sin,
            cosp * v.x * v.z - v.y * sin,
            0.0f,
        },
        
        .columns[1] = {
            cosp * v.x * v.y - v.z * sin,
            cos + cosp * v.y * v.y,
            cosp * v.y * v.z + v.x * sin,
            0.0f,
        },
        
        .columns[2] = {
            cosp * v.x * v.z + v.y * sin,
            cosp * v.y * v.z - v.x * sin,
            cos + cosp * v.z * v.z,
            0.0f,
        },
        
        .columns[3] = { 0.0f, 0.0f, 0.0f, 1.0f
        }
    };
    return m;
}

@end

