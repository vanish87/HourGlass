//
//  GameViewController.h
//  AppFrame
//
//  Created by Yuan Li on 2015/09/19.
//  Copyright © 2015年 Yuan Li. All rights reserved.
//

@import UIKit;
@import Metal;
@import MetalKit;

@interface GameViewController : UIViewController<MTKViewDelegate>

@property (weak, nonatomic) IBOutlet UILabel *debugLabel;
@property (weak, nonatomic) IBOutlet UISlider *slider;
@property (weak, nonatomic) IBOutlet UIButton *resetButton;

-(IBAction)sliderValueChanged:(UISlider *)sender;
-(IBAction)OnClick:(UIButton *)sender;

@end


