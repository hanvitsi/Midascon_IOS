//
//  ViewController.m
//  Emergency
//
//  Created by HeroK on 2015. 10. 30..
//  Copyright © 2015년 hanvitsi. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()<MDSContextManagerDelegate>
@property (nonatomic, strong) IBOutlet UIButton *button1;
@property (nonatomic, strong) IBOutlet UIButton *button2;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
   [MDSContextManager setDelegate:self];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)buttonClick:(UIButton *)button
{
    if (button.selected) {
        return;
    }
    self.button1.selected = NO;
    self.button2.selected = NO;
    
    button.selected = YES;
    if (button.tag == 0) {
        //start
        [MDSContextManager startLeScan];
        
    }else if (button.tag == 1){
        //stop
        [MDSContextManager stopLeScan];
        
    }
    
    [self buttonColor];
}

#pragma mark -
#pragma mark MDSContextManagerDelegate
- (void)emergencyCallback:(MDSContextManager *)manager forBeacon:(MDSBeaconDataModel *)beacon
{
    if ([beacon.uniqueId isEqualToString:self.beaconData.uniqueId]) {
        return;
    }
    self.beaconData = beacon;
    
    if (beacon.status == CLRegionStateInside && [UIApplication sharedApplication].applicationState == UIApplicationStateBackground) {
        UILocalNotification *_notification = [UILocalNotification new];
        _notification.alertBody = [NSString stringWithFormat:@"%@ 응급 신호 발생",beacon.uniqueId];
        _notification.userInfo = @{@"identifier":beacon.uuid};
        _notification.soundName = UILocalNotificationDefaultSoundName;
        _notification.repeatInterval = 0;
        [[UIApplication sharedApplication] presentLocalNotificationNow:_notification];
    }else{
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"알림" message:[NSString stringWithFormat:@"%@ 응급 신호 발생",beacon.uniqueId] delegate:self cancelButtonTitle:@"확인" otherButtonTitles:nil];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            [alertView show];
        });
                              
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    self.beaconData = nil;
}


- (void)buttonColor
{
    UIColor *backNonmalColor = [UIColor colorWithRed:200/255.0f green:200/255.0f blue:200/255.0f alpha:1.0];
    
    UIColor *backClickColor = [UIColor colorWithRed:230/255.0f green:230/255.0f blue:230/255.0f alpha:1.0];
    if (self.button1.selected) {
        [self.button1 setBackgroundColor:backClickColor];
    }else{
        [self.button1 setBackgroundColor:backNonmalColor];
    }
    
    if (self.button2.selected) {
        [self.button2 setBackgroundColor:backClickColor];
    }else{
        [self.button2 setBackgroundColor:backNonmalColor];
    }
}
@end
