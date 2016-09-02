//
//  ViewController.m
//  SacnList
//
//  Created by HeroK on 2015. 10. 30..
//  Copyright © 2015년 hanvitsi. All rights reserved.
//

#import "ViewController.h"
#import <MidasconSDK/MidasconSDK.h>

#define _kBeaconUUID            @"00000000-1111-2222-3333-444444444444"

@interface ViewController ()<MDSContextManagerDelegate,UITableViewDelegate,UITableViewDataSource>
{
    NSMutableArray *dataArray;
}
@property (nonatomic, strong) IBOutlet UITableView *tableView;
@property (nonatomic, strong) IBOutlet UIButton *button1;
@property (nonatomic, strong) IBOutlet UIButton *button2;
@property (nonatomic, strong) IBOutlet UILabel *label;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    dataArray = [NSMutableArray new];
    
    [MDSContextManager mdsWithProximityUUID:_kBeaconUUID];
    [MDSContextManager setBeaconType:MDSBeaconTypeBeacon];
    [MDSContextManager setBeaconGroupType:MDSBeaconGroupTypeUUID];
    [MDSContextManager setDelegate:self];
    [MDSContextManager startLeScan];
    self.button1.selected = YES;
    
    [self.label setText:[NSString stringWithFormat:@"Search iBeacon UUID\n%@",_kBeaconUUID]];
    
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
        //iBeacon
        [MDSContextManager mdsWithProximityUUID:_kBeaconUUID];
        [MDSContextManager setBeaconType:MDSBeaconTypeBeacon];
        [MDSContextManager setBeaconGroupType:MDSBeaconGroupTypeUUID];
        
        CGRect frame = self.tableView.frame;
        frame.origin.y = 45.0f;
        frame.size.height -= 45;
        [UIView animateWithDuration:0.3f animations:^{
            self.tableView.frame = frame;
        }];
        
    }else if (button.tag == 1){
        //Midascon
        [MDSContextManager mdsWithProximityUUID:nil];
        [MDSContextManager setBeaconType:MDSBeaconTypeMidascon];
        
        CGRect frame = self.tableView.frame;
        frame.origin.y = 0.0f;
        frame.size.height += 45;
        [UIView animateWithDuration:0.3f animations:^{
            self.tableView.frame = frame;
            }];
        
    }
    [MDSContextManager startLeScan];
    
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return [dataArray count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath{
    return 90;
    
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"Cell" forIndexPath:indexPath];
    MDSBeaconDataModel *dataDic = [dataArray objectAtIndex:indexPath.row];
    
    if (dataDic) {
        
        // 1. type
        UILabel *label = (UILabel *)[cell viewWithTag:101];
        NSString *beaconType;
        if (dataDic.beaconType == MDSBeaconTypeMidascon) {
            beaconType = @"[Midascon]";
        }else if (dataDic.beaconType == MDSBeaconTypeBeacon){
            beaconType = @"[Beacon]";
        }
        label.text = beaconType;
        
        // 2. id
        UILabel *label2 = (UILabel *)[cell viewWithTag:102];
        NSString *beaconId;
        if (dataDic.beaconType == MDSBeaconTypeMidascon) {
            beaconId = [NSString stringWithFormat:@"UniqueId : %@",dataDic.uniqueId];
        }else if (dataDic.beaconType == MDSBeaconTypeBeacon){
            beaconId = [NSString stringWithFormat:@"UUID : %@",dataDic.uuid];
        }
        label2.text = beaconId;
        
        // 3. rssi
        UILabel *label3 = (UILabel *)[cell viewWithTag:103];
        if (dataDic.beaconType == MDSBeaconTypeMidascon) {
            label3.text = [NSString stringWithFormat:@"RSSI : %d",dataDic.rssi];
        }else if (dataDic.beaconType == MDSBeaconTypeBeacon){
            label3.text = [NSString stringWithFormat:@"Major : %d, Minor : %d, RSSI : %d",dataDic.major,dataDic.minor,dataDic.rssi];
        }
        
        // 4. accelerometer
        UILabel *label4 = (UILabel *)[cell viewWithTag:104];
        label4.text = [NSString stringWithFormat:@"X : %d, Y :%d, Z : %d",[dataDic.xAccel integerValue],[dataDic.yAccel integerValue],[dataDic.zAccel integerValue]];
        
    }
    return cell;
}

#pragma mark MDSContextManagerDelegate
- (void)contextManager:(MDSContextManager *)manager forBeacon:(MDSBeaconDataModel *)beacon
{
    
    for (MDSBeaconDataModel *beaconData in dataArray) {
        if ([beacon.uuid isEqualToString:beaconData.uuid]) {
            [dataArray removeObject:beaconData];
        }
    }
    if (beacon.status == CLRegionStateInside) {
        [dataArray addObject:beacon];
    }
    
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.tableView reloadData];
    });
    
    
}

@end
