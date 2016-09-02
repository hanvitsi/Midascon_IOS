//
//  MDSContextManager.h
//  MidasconSDK
//
//  Created by HeroK on 2015. 8. 26..
//  Copyright (c) 2015년 Hanvit. All rights reserved.
//

#import <MidasconSDK/MDSDataManager.h>
#import <CoreBluetooth/CoreBluetooth.h>
@class MDSContextManager;


typedef NS_ENUM(NSInteger, MDSBeaconGroupType){
    MDSBeaconGroupTypeUUID,
    MDSBeaconGroupTypeMajor,
    MDSBeaconGroupTypeMinor
    
};

@protocol MDSContextManagerDelegate <NSObject>
@optional

/**
 비콘 수신시 호출됨
 @param manager this
 @param MDSBeaconDataModel 대상
 */

- (void)contextManager:(MDSContextManager *)manager forBeacon:(MDSBeaconDataModel *)beacon;

/**
 Sensor에 반응될때 발생
 @param manager this
 @param state in/out 상태
 @param sensor 해당 sensor
 */
- (void)contextManager:(MDSContextManager *)manager didDetermineState:(CLRegionState)state forsensor:(CLBeacon *)beaconSensor;

/**
 앱이 활성화 되었을 때 주변에 있는 BeaconSensor들을 반환
 @param manager this
 @param beaconSensors BeaconSensor배열
 
 */
- (void)contextManager:(MDSContextManager *)manager didRangeBeaconSensors:(NSArray *)beaconSensors;

/**
 응급 수신시 호출됨
 @param manager this
 @param MDSBeaconDataModel 대상
 */

- (void)emergencyCallback:(MDSContextManager *)manager forBeacon:(MDSBeaconDataModel *)beacon;

/**
 마이다스콘 BLE의 btye data 반환
 @param manager this
 @param NSArray byte Array (NSSting)
 BLE의 실질적인 byte data 9 ~ 29 까지 데이타가 0 ~ 21 까지로 반환
 */

- (void)contextManager:(MDSContextManager *)manager didByteArray:(NSArray *)byteArray;

@end

@interface MDSContextManager : MDSDataManager

/**
 비콘 타입 (MDSBeaconTypeBeacon : iBeacon ,MDSBeaconTypeMidascon : Midascon)
 */

@property(nonatomic, assign) MDSBeaconType beaconType;

/**
 기본 delegate
 */
@property (nonatomic, assign) id<MDSContextManagerDelegate> delegate;

/**
 클래스 내부적으로 사용되는 locationManager
 @warning delegate은 접근하지 마십시오. 이 클래스의 delegate가 작동하지 않음
 */
@property (nonatomic, readonly) CLLocationManager *locationManager;

/**
 비콘 백그라운드 수신의 그룹을 설정합니다.
 범위가 작을수록 많이 잡히지만 지오팬스를 포함한 20개의 지역뿐이 수신이 되지 않으니 주의하십시오.
 관련 기술은 애플의 기술문서를 참조해주십시오.
 Link: https://developer.apple.com/library/ios/documentation/UserExperience/Conceptual/LocationAwarenessPG/RegionMonitoring/RegionMonitoring.html
 */
@property (nonatomic, assign) MDSBeaconGroupType beaconGroupType;

/**
 비콘 타입 (MDSBeaconTypeBeacon : iBeacon ,MDSBeaconTypeMidascon : Midascon)
 */
+ (void)setBeaconType:(MDSBeaconType)beaconType;

/**
 비콘 백그라운드 수신의 그룹을 설정합니다.
 범위가 작을수록 많이 잡히지만 지오팬스를 포함한 20개의 지역뿐이 수신이 되지 않으니 주의하십시오.
 관련 기술은 애플의 기술문서를 참조해주십시오.
 Link: https://developer.apple.com/library/ios/documentation/UserExperience/Conceptual/LocationAwarenessPG/RegionMonitoring/RegionMonitoring.html
 */
+ (void)setBeaconGroupType:(MDSBeaconGroupType)beaconGroupType;

/**
 일정시간동안 비콘이 수신되지 않도록 기준 시간 설정 (Midascon 일때)
 기본값: 5초
 */
+ (void)setBeaconExitTime:(NSTimeInterval)beaconExitTime;

/**
 이탈 감지 설정 시간 확인 (초)*/
+ (NSTimeInterval)getBeaconExitTime;

/**
 델리게이트 설정
 */
+ (void)setDelegate:(id<MDSContextManagerDelegate>)delegate;

/**
 시작. in/out 이벤트가 백그라운드상태에서까지 제공되며 delegate 에서 캐치할 수 있음 */

+ (void)startLeScan;

/**
 종료 */
+ (void)stopLeScan;

/**
 스캔 중인 상태를 확인 */
+ (BOOL)isLeScan;

/**
 초기화 하며 대상 비콘의 proximityUUID 를 등록하여 객체를 반환합니다. (iBeacon 일때는 beacon의 UUID 이며, Midascon(BLE) 일때는 Service UUID 입니다.
 */
+ (id)mdsWithProximityUUID:(NSString *)proximityuuid;

/**
 초기화 하며 대상 비콘의 proximityUUID와 major 를 등록하여 객체를 반환합니다.
 */
+ (id)mdsWithProximityUUID:(NSString *)proximityuuid major:(CLBeaconMajorValue)major;

/**
 초기화 하며 대상 비콘의 proximityUUID와 major,minor 를 등록하여 객체를 반환합니다.
 */
+ (id)mdsWithProximityUUID:(NSString *)proximityuuid major:(CLBeaconMajorValue)major minor:(CLBeaconMinorValue)minor;


@end



