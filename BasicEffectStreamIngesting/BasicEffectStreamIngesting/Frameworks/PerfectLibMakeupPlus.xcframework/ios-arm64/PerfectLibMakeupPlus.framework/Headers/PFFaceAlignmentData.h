//
//  PFFaceAlignmentData.h
//  MakeupSDK
//
//  Created by PX Chen on 2018/6/26.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Object contains face alignment data.
 */
@interface PFFaceAlignmentData : NSObject

@property (nonatomic, readonly) CGFloat frameWidth;
@property (nonatomic, readonly) CGFloat frameHeight;

@property (nonatomic, readonly) NSArray <NSValue *> *featurePoints;

@end
