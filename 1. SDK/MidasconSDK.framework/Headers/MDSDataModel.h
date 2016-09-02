//
//  MDSDataModel.h
//  MidasconSDK
//
//  Created by HeroK on 2015. 8. 26..
//  Copyright (c) 2015년 Hanvit. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

typedef NS_ENUM(NSUInteger, MDSBeaconType) {
    MDSBeaconTypeMidascon = 1,
    MDSBeaconTypeBeacon = 2,
};

@interface MDSBeaconDataModel : NSObject

/**
 비콘 타입 (MDSBeaconTypeBeacon : iBeacon ,MDSBeaconTypeMidascon : Midascon)
 */
@property (nonatomic, readonly) MDSBeaconType beaconType;

/**
 Hanvit unique Id 값 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSString *beaconId;

/**
 UUID 값
 */
@property (nonatomic, readonly) NSString *uuid;

/**
 Major 값   (iBeacon 일때 반환)
 */
@property (nonatomic, readonly) NSInteger major;

/**
 Minor 값   (iBeacon 일때 반환)
 */
@property (nonatomic, readonly) NSInteger minor;

/**
 rssi 신호
 */
@property (nonatomic, readonly) NSInteger rssi;

/**
 txPower, 거리측정에 기준이 되는 값 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSInteger txPower;

/**
 응급 신호 플래그, 일반상태 0/응급상태 1 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSInteger emergency;

/**
 베터리 상태(0~100) (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSInteger battery;

/**
 온도 데이터 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSString *temperature;

/**
 습도 데이터 값 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSString *humidity;

/**
 Hanvit unique Id 값 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSString *uniqueId;

/**
 TBD 값 (Midascon 일때 반환)
 */
@property (nonatomic, readonly) NSString *tbd;

/**
 비콘 상태 값
 */
@property (nonatomic, readonly) CLRegionState status;

/**
 비콘 최종 수신된 시간
 */
@property (nonatomic, readonly) NSDate *statusUpdatedDate;

/**
 가속센서 x축 값
 */
@property (nonatomic, readonly) NSString *xAccel;

/**
 가속센서 y축 값
 */
@property (nonatomic, readonly) NSString *yAccel;

/**
 가속센서 z축 값
 */
@property (nonatomic, readonly) NSString *zAccel;

@end
