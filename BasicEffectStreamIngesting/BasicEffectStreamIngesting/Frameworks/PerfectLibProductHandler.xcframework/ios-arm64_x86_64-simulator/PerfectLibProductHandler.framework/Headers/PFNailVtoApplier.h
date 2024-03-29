//
//  PFNailVtoApplier.h
//  PerfectLibProductHandler
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

NS_SWIFT_NAME(NailVtoApplier)
/// A class to perform virtual try-on effects.
@interface PFNailVtoApplier : PFHandVtoApplier

/// Initialize a `PFNailVtoApplier` instance.
/// @param target The target should be either `PFNailCam` or `PFPhotoNail`.
- (instancetype _Nullable)initWithTarget:(id)target NS_DESIGNATED_INITIALIZER;

/**
 Apply the nail effects of the products specified by the list of `VtoSetting`.
 
 @param vtoSettings The list of `VtoSetting`. Each `VtoSetting` object represents an effect of a product.
 @param effectConfig The effect config object to set blending effect for two SKU of the same type, e.g., hair dye.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
 */
- (void)applyVtoSettings:(NSArray <VtoSetting *> *)vtoSettings
            effectConfig:(nullable EffectConfig* )effectConfig
            successBlock:(nullable ApplyEffectSuccessBlock)successBlock
            failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Apply the nail effects specified by the list of `EffectId` on current specified face.
 
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
 Apply a set of nail effects specified by the Look GUID.
 
 @param lookSetting The Look GUID.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
 */
- (id<CancelableTask> _Nullable)applyLookSetting:(LookSetting *)lookSetting
                                    successBlock:(nullable ApplyEffectSuccessBlock)successBlock
                                    failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Set the intensities of the effects.
 
 @param intensities A mapping from the effect ID to the intensity.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.

 @note An intensity is an integer value from 0 to 100.
*/
- (void)setIntensities:(NSDictionary <NSNumber *, NSArray *> *)intensities
          successBlock:(nullable ApplyEffectSuccessBlock)successBlock
          failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Get the intensities of the effects from current specified face.
 
 @return A mapping from the effect ID to the intensity.
 */
- (NSDictionary <NSNumber *, NSArray *> * _Nullable)getIntensities;

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
 Remove a specified nail effect on `PFNailPosition` on image.

 @param positions          A specified nail position to be clean.
 @param successBlock    A block object to be executed when effect clean on image successfully.
 @param failureBlock    A block object to be executed when failed.
 */
- (void)clearEffects:(nonnull NSArray<NSNumber *> *)positions
       successBlock:(nullable ApplyEffectSuccessBlock)successBlock
       failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Remove all the existing nail effects on image.

 @param successBlock    A block object to be executed when effect clean on image successfully.
 @param failureBlock    A block object to be executed when failed.
 */
- (void)clearAllEffectsWithSuccessBlock:(nullable ApplyEffectSuccessBlock)successBlock
                           failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
Unavailable. Use `-initWithTarget:` for `PFNailVtoApplier` object initializing.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
Unavailable. Use `-initWithTarget:` for `PFNailVtoApplier` object initializing.
*/
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
