//
//  MDSUserDataModel.h
//  MidasconSDK
//
//  Created by HeroK on 2015. 9. 7..
//  Copyright (c) 2015년 Hanvit. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface MDSUserDataModel : NSManagedObject

@property (nonatomic, retain) NSData * userData;
@property (nonatomic, retain) NSString * uuid;

@end
