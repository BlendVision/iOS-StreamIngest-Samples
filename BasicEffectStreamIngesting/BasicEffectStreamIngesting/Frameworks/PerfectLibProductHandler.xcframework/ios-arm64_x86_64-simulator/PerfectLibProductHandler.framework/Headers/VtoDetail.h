//
//  VtoDetail.h
//  MakeupLib
//
//  Created by Alex Lin on 2019/7/9.
//  Copyright © 2019 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The base class for virtual try on objects
 */
@interface VtoObject : NSObject
/// Unique identifier of the object
@property (nonatomic, readonly, nonnull) NSString* guid;
/// A readable name to represent the object
@property (nonatomic, readonly, nullable) NSString* name;
/// Thumbnail representing the object
@property (nonatomic, readonly, nullable) NSString* thumbnailUrl;
@end

@class VtoPattern;
/**
 The class representing virtual try on palettes
 */
@interface VtoPalette : VtoObject
/// The colors in the palette
@property (nonatomic, readonly, nullable) NSArray<UIColor *>* colors;
/// Related patterns
- (NSArray<VtoPattern*>* __nullable)getPatterns;
@end

/**
 The class representing virtual try on patterns
 */
@interface VtoPattern : VtoObject
/// Related palettes
- (NSArray<VtoPalette*>* __nullable)getPalettes;
@end

/**
 The class representing virtual try on wearing style
 */
@interface VtoWearingStyle: VtoObject
@end

/**
 The class holds palettes and patterns related to a SKU
 */
@interface VtoDetail : NSObject
/// Get all the `VtoPalette` of the current feature
- (NSArray<VtoPalette*>* __nullable)getPalettes;
/// Get al lthe `VtoPattern` of the current feature
- (NSArray<VtoPattern*>* __nullable)getPatterns;
/// Get all the` VtoWearingStyle` of the current feature
- (NSArray<VtoWearingStyle*>* __nullable)getWearingStyles;
@end

NS_ASSUME_NONNULL_END
