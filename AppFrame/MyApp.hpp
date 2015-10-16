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
#include "Sandsimulator.hpp"

class MyApp: public Engine::App
{
public:
    MyApp();
    virtual ~MyApp();
    
    //Do main context init staffs
    virtual Tool::ReturnCode Init();
    //Deinit staffs
    virtual Tool::ReturnCode Deinit();
    //User update
    virtual Tool::ReturnCode Update();
    
    void ResetSimulator();
    SandSimulator& GetSimulator(){return SandSim;};
    
private:
	SandSimulator SandSim;
	Engine::float4x4 ViewMatrix;
};

#endif /* MyApp_hpp */
