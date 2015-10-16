//
//  MainLoop_Bridge.hpp
//  AppFrame
//
//  Created by Yuan Li on 2015/09/28.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

#ifndef MainLoop_Bridge_hpp
#define MainLoop_Bridge_hpp

#ifdef __cplusplus
extern "C" {
#endif
void MainLoopBridge_StartGameLoop(void);
void MainLoopBridge_ResetSimulator();
void MainLoopBridge_ConfigureSimulator(float Mass, float Aphla, float Beta, float NormalRestitution);
#ifdef __cplusplus
}
#endif

#endif /* MainLoop_Bridge_hpp */
