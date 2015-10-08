//
//  MyApp.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef MyApp_hpp
#define MyApp_hpp

#include "App.hpp"
#include "Particle.hpp"



class MyApp: public Engine::App
{
public:
    MyApp():App(){};
    virtual ~MyApp(){};
    
    //Do main context init staffs
    virtual Tool::ReturnCode Init()
    {
        App::Init();
        
        NewP.Create(CUBE);
        NewP.AddToScene();
        NewP.SetLocation(float3(0,1,5));
        
        
        NewP.Create(SPHERE);
        //NewP1.AddToScene();
        NewP1.SetLocation(float3(2,-1,5));
        
        NewPlane.Create(PLANE);
        NewPlane.AddToScene();
        NewPlane.SetLocation(float3(0,-1,0));

        return Tool::Success();
    };
    //Deinit staffs
    virtual Tool::ReturnCode Deinit()
    {
        App::Deinit();
        return Tool::Success();
    };
    //User update
    virtual Tool::ReturnCode Update()
    {
        App::Update();
        return Tool::Success();
    };
    
private:
    
    Physics::Particle NewP;
    Physics::Particle NewP1;
    Physics::Particle NewPlane;
    
};

#endif /* MyApp_hpp */
