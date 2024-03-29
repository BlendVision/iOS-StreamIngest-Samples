//
//  EffectSetting.h
//  MakeupLib
//
//  Created by PX Chen on 2018/9/10.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<PerfectLibCore/PerfectLibCore.h>)
#import <PerfectLibCore/PerfectLibCore.h>
#elif __has_include(<PerfectLibSlimCore/PerfectLibSlimCore.h>)
#import <PerfectLibSlimCore/PerfectLibSlimCore.h>
#define SLIM_VERSION
#else
#endif

NS_ASSUME_NONNULL_BEGIN
/**
 Use this class to apply a virtual try-on effect by `-[PFVtoApplier applyVtoSettings:effectConfig:successBlock:failureBlock:]`.
 */
@interface VtoSetting : NSObject

/**
 Unavailable. Use `-[VtoSettingBuilder create]` to get instance.
 */
- (id)init __attribute__((unavailable("Use `VtoSettingBuilder:create` to get instance")));

/**
 Unavailable. Use `-[VtoSettingBuilder create]` to get instance.
 */
+ (instancetype)new __attribute__((unavailable("Use `VtoSettingBuilder:create` to get instance")));

@end

/// The generic interface of extra parameters for some specific VTO type, e.g., EarringParameter for earrings try on
@protocol VtoSettingParameter <NSObject>
@end

/// A builder class to create `VtoSetting`.
@interface VtoSettingBuilder : NSObject
/// Setup product guid to builder.
/// @param productGuid the product guid.
- (VtoSettingBuilder*)SetProductGuid:(NSString* _Nullable)productGuid;
/// Setup SKU guid to builder.
/// @param skuGuid the SKU guid.
- (VtoSettingBuilder*)SetSkuGuid:(NSString* _Nullable)skuGuid;
/// Setup a specify pattern guid to builder.
/// @param patternGuid the pattern guid.
- (VtoSettingBuilder*)SetPatternGuid:(NSString* _Nullable)patternGuid;
/// Setup a specify palette guid to builder.
/// @param paletteGuid the palette guid.
- (VtoSettingBuilder*)SetPaletteGuid:(NSString* _Nullable)paletteGuid;
/// Setup a specify SKU set guid to builder.
/// @param skuSetGuid the SKU set guid.
- (VtoSettingBuilder*)SetSkuSetGuid:(NSString* _Nullable)skuSetGuid;
/// Setup a specify wearing style guid to builder.
/// @param wearingStyleGuid the wearing style guid.
- (VtoSettingBuilder*)SetWearingStyleGuid:(NSString* _Nullable)wearingStyleGuid;
/// Set the extra parameter for the virtual application
/// @param parameter the parameter
- (VtoSettingBuilder*)SetParameter:(id<VtoSettingParameter>)parameter;
/// Create a `VtoSetting` instance, return nil if the input parameters are illegal.
- (VtoSetting* _Nullable)create;
@end

/// Extra parameter for earring VTO
@interface EarringParameter : NSObject<VtoSettingParameter>
/// Specify the current earring application is on the left
@property (nonatomic, assign) BOOL isLeft;
/// Specify the current earring is pierced on the `piercedPosition`
@property (nonatomic, assign) int piercedPosition;
@end

@interface NailParameter: NSObject<VtoSettingParameter>
/// Specify the current nail is on the position `PFNailPosition`
@property (nonatomic, assign) PFNailPosition position;
@end

NS_ASSUME_NONNULL_END
