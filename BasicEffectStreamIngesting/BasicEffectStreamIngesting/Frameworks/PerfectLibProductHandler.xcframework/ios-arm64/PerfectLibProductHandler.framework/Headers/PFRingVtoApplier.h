//
//  PFRingVtoApplier.h
//  PerfectLibHandlerCore
//
//  Created by Steven Chen on 2020/9/7.
//  Copyright © 2020 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PerfectLibCore/PerfectLibCore.h>
#import <PerfectLibProductHandler/PFHandVtoApplier.h>

@class VtoSetting;
@class LookSetting;
@class EffectId;
@class EffectConfig;
@class ProductId;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(RingVtoApplier)
/// A class to perform virtual try-on effects.
@interface PFRingVtoApplier : PFHandVtoApplier

/// Initialize a `PFRingVtoApplier` instance.
/// @param target The target should be either `PFRingCam` or `PFPhotoRing`.
- (instancetype _Nullable)initWithTarget:(id)target NS_DESIGNATED_INITIALIZER;

/**
 Apply the ring effects of the products specified by the list of `VtoSetting`.
 
 @param vtoSetting The list of `VtoSetting`. Each `VtoSetting` object represents an effect of a product.
 @param effectConfig The effect config object to set blending effect for two SKU of the same type, e.g., hair dye.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
 */
- (void)applyVtoSetting:(VtoSetting *)vtoSetting
           effectConfig:(nullable EffectConfig* )effectConfig
           successBlock:(nullable ApplyEffectSuccessBlock)successBlock
           failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Apply the ring effects specified by the list of `EffectId` on current specified face.
 
 @param effectIDs The list of `EffectId`. Each `EffectId` object represents an effect to be applied.
 @param clearFirst YES: Clear all existing effects before applying. NO: Otherwise.
 @param successBlock A completion called when the operation completed.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
 */
- (void)applyEffectIds:(NSArray <EffectId *> *)effectIDs
            clearFirst:(BOOL)clearFirst
          successBlock:(nullable ApplyEffectSuccessBlock)successBlock
          failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Get the applied effects from current specified face.
 
 @return An array of the applied effects.
 */
- (NSArray<EffectId *> * _Nullable)getEffectIds;

/**
 Get the applied effects of the products from current specified face.
 
 @return An array of the applied effects of the products.
 */
- (NSArray<ProductId *> * _Nullable)getProductIds;

/**
 Remove all the existing ring effects on image.

 @param successBlock    A block object to be executed when effect clean on image successfully.
 @param failureBlock    A block object to be executed when failed.
 */
- (void)clearAllEffectsWithSuccessBlock:(nullable ApplyEffectSuccessBlock)successBlock
                           failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
Unavailable. Use `-initWithTarget:` for `PFRingVtoApplier` object initializing.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
Unavailable. Use `-initWithTarget:` for `PFRingVtoApplier` object initializing.
*/
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
