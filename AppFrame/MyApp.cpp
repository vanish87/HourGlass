//
//  MyApp.cpp
//  AppFrame
//
//  Created by Yuan Li on 2015/10/04.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#include "MyApp.hpp"

using namespace Engine;

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
    this->SandSim.Init();

	return Tool::Success();
};
//Deinit staffs
Tool::ReturnCode MyApp::Deinit()
{
    this->SandSim.Deinit();
	App::Deinit();
	return Tool::Success();
};
//User update
Tool::ReturnCode MyApp::Update()
{
	App::Update();
    this->SandSim.Update();
	return Tool::Success();
};