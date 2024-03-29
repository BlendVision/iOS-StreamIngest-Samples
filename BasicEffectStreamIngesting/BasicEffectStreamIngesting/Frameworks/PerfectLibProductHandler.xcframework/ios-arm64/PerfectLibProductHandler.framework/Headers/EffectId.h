//
//  EffectID.h
//  MakeupLib
//
//  Created by Peni on 2018/8/10.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Struct of Effect related IDs
 */
@interface EffectId : NSObject
/// The effect type of the effect
@property (nonatomic, readonly) PFEffect type;
/// The SKU set GUID of the combination of products used for this effect
@property (nonatomic, readonly, nullable) NSString *skuSetGuid;
/// The product GUID of the effect, specifying a product, if this is not a product effect, the value will be N/A
@property (nonatomic, readonly, nullable) NSString *productGuid;
/// The SKU GUID of the product, specifying a shade or a color, if this is not a SKU effect, the value will be a palette or patter GUID
@property (nonatomic, readonly, nullable) NSString *skuGuid;
@property (nonatomic, readonly, nullable) NSString *paletteGuid;
@property (nonatomic, readonly, nullable) NSString *patternGuid;
@property (nonatomic, readonly, nullable) NSString *wearingStyleGuid;
/// The GUID for fun sticker effect.
@property (nonatomic, readonly, nullable) NSString *funStickerGuid;
/// The intensity array of the effect.
@property (nonatomic, readonly, nullable) NSArray <NSNumber *> *intensities;
@property (nonatomic, readonly) PFNailPosition nailPosition;

/**
 Unavailable. Use MakeupCam:getEffectIDs/PhotoEditor:getEffectIDs to get object.".
 */
- (id _Nonnull )init __attribute__((unavailable("Use MakeupCam:getEffectIDs/PhotoEditor:getEffectIDs to get object.")));

/**
 Unavailable. Use MakeupCam:getEffectIDs/PhotoEditor:getEffectIDs to get object.".
 */
+ (instancetype _Nonnull )new __attribute__((unavailable("Use MakeupCam:getEffectIDs/PhotoEditor:getEffectIDs to get object.")));

@end
