//
//  MyApp.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "MyApp.hpp"

MyApp::MyApp()
	:App() 
{

};
MyApp::~MyApp()
{

};
//Do main context init staffs
Tool::ReturnCode MyApp::Init()
{
	App::Init();
    for (std::array<Physics::Particle, MyApp::NUMBER_OF_PARTICLES>::iterator it = this->ParticlePool.begin();
			it != this->ParticlePool.end();
			++it)
	{
		it->Create(CUBE);
		it->AddToScene();
		it->SetLocation(float3(0, 1, 0));
	}

	return Tool::Success();
};
//Deinit staffs
Tool::ReturnCode MyApp::Deinit()
{
	App::Deinit();
	return Tool::Success();
};
//User update
Tool::ReturnCode MyApp::Update()
{
	App::Update();
	return Tool::Success();
};