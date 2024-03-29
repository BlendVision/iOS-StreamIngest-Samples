//
//  PFVtoApplier.h
//  PerfectLibHandlerCore
//
//  Created by Steven Chen on 2020/9/7.
//  Copyright © 2020 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<PerfectLibCore/PerfectLibCore.h>)
#import <PerfectLibCore/PerfectLibCore.h>
#elif __has_include(<PerfectLibSlimCore/PerfectLibSlimCore.h>)
#import <PerfectLibSlimCore/PerfectLibSlimCore.h>
#define SLIM_VERSION
#else
#endif

@class VtoSetting;
@class LookSetting;
@class EffectId;
@class EffectConfig;
@class ProductId;
@class PFReshapeEffectId;
@class MakeupEffectProfile;
NS_ASSUME_NONNULL_BEGIN

/// the enumeration for fun sticker actions.
typedef NS_ENUM(NSInteger, PFFunStickerActionHint) {
    PFFunStickerActionHintMouthOpen,
    PFFunStickerActionHintBlink
} NS_SWIFT_NAME(FunStickerActionHint);

/**
 This protocol provides information of the `PFVtoApplier` object.
 */
NS_SWIFT_NAME(VtoApplierDelegate)
@protocol PFVtoApplierDelegate <NSObject>

@optional
/// This method called when client apply a related effects.
/// @param hints the array consist of the enum of `PFFunStickerActionHint`.
- (void)onFunStickerActionHintTrigger:(NSArray <NSNumber *>* _Nullable )hints;

@end

NS_SWIFT_NAME(VtoApplier)
/// A class to perform virtual try-on effects.
@interface PFVtoApplier : NSObject

/// Initialize a `PFVtoApplier` instance.
/// @param target The target should be either `PFMakeupCam` or `PFPhotoMakeup`.
- (instancetype _Nullable)initWithTarget:(id)target NS_DESIGNATED_INITIALIZER;

/// An object implements `PFVtoApplierDelegate` protocol.
@property (weak, nonatomic) id<PFVtoApplierDelegate> delegate;

/**
 Apply the makeup effects of the products specified by the list of `VtoSetting`.
 
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
 Apply the makeup effects specified by the list of `EffectId` on current specified face.
 
 @param effectIDs The list of `EffectId`. Each `EffectId` object represents an effect to be applied.
 @param reshaperEffectIds The list of `PFReshapeEffectId`. Each `PFReshapeEffectId` object represents a reshape effect to be applied.
 @param clearFirst YES: Clear all existing effects before applying. NO: Otherwise.
 @param successBlock A completion called when the operation completed.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
 */
- (void)applyEffectIds:(NSArray <EffectId *> *)effectIDs
      reshapeEffectIds:(nullable NSArray <PFReshapeEffectId *> *)reshaperEffectIds
            clearFirst:(BOOL)clearFirst
          successBlock:(nullable ApplyEffectSuccessBlock)successBlock
          failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;
/**
 Apply a set of makeup effects specified by the Look GUID.
 
 @param lookSetting The Look GUID.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
 */
- (id<CancelableTask> _Nullable)applyLookSetting:(LookSetting *)lookSetting
                                    successBlock:(nullable ApplyEffectSuccessBlock)successBlock
                                    failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

- (id<CancelableTask> _Nullable)applyLookSetting:(LookSetting *)lookSetting
                                    successBlock:(nullable ApplyEffectSuccessBlock)successBlock
                                    failureBlock:(nullable ApplyEffectFailureBlock)failureBlock
                                 completionBlock:(nullable ApplyEffectCompletionBlock)completionBlock;

/**
 Set the intensities of the effects.
 
 @param intensities A mapping from the effect ID to the intensity.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.

 @note An intensity is an integer value from 0 to 100.
 The value range for `PFEffectFaceShaper` and `PFEffectEyeEnlarger` is from -100 to 100, 0 is the default value.
 the `PFEffectEyeshadow` effect may contains multiple intensity depend on the count of colors,
 the `PFEffectEyewear` & `PFEffectHeadband` effect doesn't support intensity changes.
*/
- (void)setIntensities:(NSDictionary <NSNumber *, NSArray *> *)intensities
          successBlock:(nullable ApplyEffectSuccessBlock)successBlock
          failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Set the intensities of the effects.
 
 @param intensities A mapping from the reshape effect to the intensity.
 @param successBlock A completion called when the operation completes.
 @param failureBlock A failure called when the operation fails. The parameter, `PerfectLibErrorCode`, specifies the error code of the failed reason.
*/

- (void)setReshapeIntensities:(NSDictionary <NSNumber *, NSNumber *> *)intensities
               successBlock:(nullable ApplyEffectSuccessBlock)successBlock
               failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Get the intensities of the effects from current specified face.
 
 @return A mapping from the effect ID to the intensity.
 */
- (NSDictionary <NSNumber *, NSArray *> * _Nullable)getIntensities;

/**
 Get the intensities of the effects from current specified face.
 
 @return A mapping from the PFReshapeEffect to the intensity.
 */
- (NSDictionary <NSNumber *, NSNumber *> * _Nullable)getReshapeIntensities;

/**
 Get the applied effects from current specified face.
 
 @return An array of the applied effects.
 */
- (NSArray<EffectId *> * _Nullable)getEffectIds;

/**
 Get the applied reshape effects of the products from current specified face.
 
 @return An array of the applied reshape effects.
 */
- (NSArray<PFReshapeEffectId *> * _Nullable)getReshapeEffectIds;

/**
 Get the applied effects of the products from current specified face.
 
 @return An array of the applied effects of the products.
 */
- (NSArray<ProductId *> * _Nullable)getProductIds;

/**
 Remove a specified makeup effect in `PFEffect` on image.

 @param effect          A specified makeup effect to be clean.
 @param successBlock    A block object to be executed when effect clean on image successfully.
 @param failureBlock    A block object to be executed when failed.
 */
- (void)clearEffect:(PFEffect)effect
       successBlock:(nullable ApplyEffectSuccessBlock)successBlock
       failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Remove all the existing makeup effects on image.

 @param successBlock    A block object to be executed when effect clean on image successfully.
 @param failureBlock    A block object to be executed when failed.
 */
- (void)clearAllEffectsWithSuccessBlock:(nullable ApplyEffectSuccessBlock)successBlock
                           failureBlock:(nullable ApplyEffectFailureBlock)failureBlock;

/**
 Set the lipstick effect transition.
 
 @param duration The duration of the transition in millisecond.
 @param color The start color of the transition.
 @note This feature is for live preivew only, the photo mode doesn't supported.
 */
- (void)setLipstickTransition:(int)duration
                        color:(UIColor *)color;

/**
Unavailable. Use `-initWithTarget:` for `PFVtoApplier` object initializing.
*/
- (instancetype)init NS_UNAVAILABLE;

/**
Unavailable. Use `-initWithTarget:` for `PFVtoApplier` object initializing.
*/
- (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
