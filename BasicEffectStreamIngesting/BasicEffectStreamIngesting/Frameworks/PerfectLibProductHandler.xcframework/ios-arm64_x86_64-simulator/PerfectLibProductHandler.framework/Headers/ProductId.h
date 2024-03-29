//
//  ProductID.h
//  MakeupLib
//
//  Created by Peni on 2018/9/7.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Struct of Product related IDs
 */
@interface ProductId : NSObject
/// The effect type of the product
@property (nonatomic,readonly) PFEffect type;
/// The SKU set GUID of the combinations of products
@property (nonatomic,readonly,nullable) NSString *skuSetGuid;
/// The product GUID of the product, specifying a product
@property (nonatomic,readonly,nullable) NSString *productGuid;
/// The SKU GUID of the product, specifying a shade or a color
@property (nonatomic,readonly,nullable) NSString *skuGuid;
@property (nonatomic,readonly,nullable) NSString *paletteGuid;
@property (nonatomic,readonly,nullable) NSString *patternGuid;
@property (nonatomic,readonly,nullable) NSString *wearingStyleGuid;
@property (nonatomic,readonly) PFNailPosition nailPosition;
/// The sub item GUID of the current makeup, this is not information about the product, instead it describe what kind of pattern/palette used to do the makeup

/**
 Unavailable. Use MakeupCam:getEffectIDs/PhotoEditor:getEffectIDs to get object.".
 */
- (id _Nonnull )init __attribute__((unavailable("Use MakeupCam:getProductIDs/PhotoEditor:getProductIDs to get object.")));

/**
 Unavailable. Use MakeupCam:getEffectIDs/PhotoEditor:getEffectIDs to get object.".
 */
+ (instancetype _Nonnull )new __attribute__((unavailable("Use MakeupCam:getProductIDs/PhotoEditor:getProductIDs to get object.")));

@end
