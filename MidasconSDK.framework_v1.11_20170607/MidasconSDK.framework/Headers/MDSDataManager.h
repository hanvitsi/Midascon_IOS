//
//  MDSDataManager.h
//  MidasconSDK
//
//  Created by HeroK on 2015. 8. 26..
//  Copyright (c) 2015년 Hanvit. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MidasconSDK/MDSDataModel.h>

@interface MDSDataManager : NSObject

/**
 비콘 기기 수신 로그 정보 저장 여부
 기본값: NO
 */
@property (nonatomic, assign) BOOL isLogSave;


/**
 Singleton 객체
 */
+ (instancetype)shareInstance;

/**
 Sensor 수신시 쌓인 로그
 @param completionBlock 모든 SensorLog정보를 MDSBeaconDataModel 객체배열로 반환
 */
+ (void)selectBeaconLogAllWithCompletionBlock:(void(^)(NSArray *logArray))completionBlock;


/**
 Sensor 수신시 쌓인 로그
 @param completionBlock 모든 SensorLog정보를 JSON 객체배열로 반환
 */
+ (void)selectBeaconLogAllJSONWithCompletionBlock:(void(^)(NSData *logJSONData))completionBlock;

/**
 Sensor 수신시 쌓인 로그 총 갯수
 @param completionBlock 모든 SensorLog 갯수를 NSInteger로 반환
 */
+ (void)selectBeaconLogAllCountWithCompletionBlock:(void(^)(NSInteger logCount))completionBlock;


/**
 Sensor 수신시 쌓인 로그 삭제
 */
+ (void)deleteBeaconLog;


/**
 사용자 임의의 데이터를 uuid(key) 기준으로 등록
 */
+ (void)setBeaconTagWithData:(NSData*)data key:(NSString *)key;

/**
 사용자가 저장한 데이터
 @param completionBlock 사용자가 저장한 uuid(key) 기준으로 반환
 */
+ (void)getBeaconTag:(NSString *)key completionBlock:(void(^)(NSData *userData))completionBlock;

/**
 사용자가 저장한 데이터
 @param completionBlock 사용자가 저장한 모든 data 정보를 MDSUserDataModel 객체배열로 반환
 */
+ (void)getBeaconTagListWithCompletionBlock:(void(^)(NSArray *logArray))completionBlock;

/**
 사용자 저장 데이터 삭제
 */
+ (void)clearBeaconTag;


@end
