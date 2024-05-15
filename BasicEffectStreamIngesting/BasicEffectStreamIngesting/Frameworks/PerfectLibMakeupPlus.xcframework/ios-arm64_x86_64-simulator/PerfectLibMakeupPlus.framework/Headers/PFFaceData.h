//
//  PFFaceData.h
//  MakeupSDK
//
//  Created by PX Chen on 2018/7/5.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#if __has_include(<PerfectLibMakeupPlus/PFFaceAlignmentData.h>)
#import <PerfectLibMakeupPlus/PFFaceAlignmentData.h>
#elif __has_include(<PerfectLibMakeup/PFFaceAlignmentData.h>)
#import <PerfectLibMakeup/PFFaceAlignmentData.h>
#endif

/**
 An object to store the information of detected face.
 */
@interface PFFaceData : NSObject

/**
 Get the rectangle of detected face.

 @return the rectangle of detected face.
 */
- (CGRect)getFaceRect;

/**
 Get the full face alignment data with facial landmarks.
 
 @return the face alignment data
 */
- (PFFaceAlignmentData*)getFaceAlignmentData;

/**
 Unavailable. Use `PhotoMakeup:detectFace` to get instance.
 */
- (id)init __attribute__((unavailable("Use `PhotoMakeup:detectFace` to get instance")));

/**
 Unavailable. Use `PhotoMakeup:detectFace` to get instance.
 */
+ (instancetype)new __attribute__((unavailable("Use `PhotoMakeup:detectFace` to get instance")));

@end
