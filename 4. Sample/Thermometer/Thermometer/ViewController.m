//
//  ViewController.m
//  Thermometer
//
//  Created by HeroK on 2015. 10. 30..
//  Copyright © 2015년 hanvitsi. All rights reserved.
//

#import "ViewController.h"
#import <MidasconSDK/MidasconSDK.h>

@interface ViewController ()<MDSContextManagerDelegate>
@property (nonatomic, strong) IBOutlet UILabel *label1;
@property (nonatomic, strong) IBOutlet UILabel *label2;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
     [MDSContextManager setDelegate:self];
    
    self.label1.text = @"0 ˚C";
    self.label2.text = @"0 %";
}

#pragma mark MDSContextManagerDelegate
- (void)contextManager:(MDSContextManager *)manager forBeacon:(MDSBeaconDataModel *)beacon
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.label1.text = [NSString stringWithFormat:@"%@ ˚C",beacon.temperature];
        self.label2.text = [NSString stringWithFormat:@"%@ %%",beacon.humidity];
        
    });
    
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
