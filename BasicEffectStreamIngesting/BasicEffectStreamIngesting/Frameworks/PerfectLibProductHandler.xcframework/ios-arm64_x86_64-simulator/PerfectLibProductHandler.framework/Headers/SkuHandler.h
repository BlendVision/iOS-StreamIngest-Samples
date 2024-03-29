//
//  SkuHandler.h
//  MakeupSDK
//
//  Created by PX Chen on 2018/6/4.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//
#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#if __has_include(<PerfectLibCore/PerfectLibCore.h>)
#import <PerfectLibCore/PerfectLibCore.h>
#elif __has_include(<PerfectLibSlimCore/PerfectLibSlimCore.h>)
#import <PerfectLibSlimCore/PerfectLibSlimCore.h>
#endif

NS_ASSUME_NONNULL_BEGIN

extern NSString * const SKUHandlerSaveLookForLaterDone;

typedef void (^SkuHandlerCompleteBlock)(BOOL result);
typedef void (^SkuHandlerFailureBlock)(NSError *error, NSString *message);
typedef void (^SkuHandlerProgressBlock)(CGFloat progress);

/**
 Status code of `-[SkuHandler getListByEffect:]`.
 
 @see `-[SkuHandler getListByEffect:]`.
 */
typedef NS_ENUM(NSInteger, SkuHandlerListStatus) {
    /// All the SKUs and items are correctly mapped
    SkuHandlerListStatusOK                     = 0,
    /// Some SKUs or items are not mapped
    SkuHandlerListStatusMappingIncomplete      = -1,
};

/**
     The values are as same as "Button Icon" of product editing page in Perfect Console.
*/
typedef NS_ENUM(NSInteger, PFActionUrlType) {
    PFActionUrlTypeShopping                     = 0,
    PFActionUrlTypeMoreInfo,
    PFActionUrlTypeHidden
};

@class PFProductInfo, PFSkuInfo, PFSubItemInfo, PFSkuSetInfo;
@protocol CancelableTask;

/**
 SkuHandler provides SKU related APIs.
 - Use `-[SkuHandler checkNeedToUpdate:failureBlock:]` to check if the server updates SKUs.
 - If the server updates SKUs, use `-[SkuHandler syncServer:failureBlock:progressBlock:]` to get updated products from the server.
 - To list specific products, call `-[SkuHandler getListByEffect:]`.
 - Delete downloaded products from the local storage by calling `-[SkuHandler clearAll]`.
 */
@interface SkuHandler : NSObject

/// Get the instance of `SkuHandler`.
+ (SkuHandler *)sharedManager;

/**
 Check if the server updates products.

 @param successBlock A callback called when the checking completes.
 @param failureBlock A callback called when the checking fails.
 */
- (void)checkNeedToUpdate:(SkuHandlerCompleteBlock)successBlock
             failureBlock:(SkuHandlerFailureBlock)failureBlock;

/**
 Check if the server updates products by a specific effect.
 
 @param effect The category of makeup effect
 @param successBlock A callback called when the checking completes.
 @param failureBlock A callback called when the checking fails.
 */
- (void)checkNeedToUpdateByEffect:(PFEffect)effect
                     successBlock:(SkuHandlerCompleteBlock)successBlock
                     failureBlock:(SkuHandlerFailureBlock)failureBlock;

/**
 Update products from server.

 @param successBlock A callback called when the operation succeeds
 @param failureBlock A callback called when the operation fails
 @param progressBlock A callback called when each SKU is downloaded
 */
- (id<CancelableTask> _Nullable)syncServer:(SkuHandlerCompleteBlock)successBlock
                              failureBlock:(SkuHandlerFailureBlock)failureBlock
                             progressBlock:(nullable SkuHandlerProgressBlock)progressBlock;
/**
 Update products from server on specific effect.
 
 @param effect The category of makeup effect
 @param completeBlock A callback called when the operation succeeds
 @param failureBlock A callback called when the operation fails
 @param progressBlock A callback called when each SKU is downloaded
 */
- (id<CancelableTask> _Nullable)syncServerByEffect:(PFEffect)effect
                                     completeBlock:(SkuHandlerCompleteBlock)completeBlock
                                      failureBlock:(SkuHandlerFailureBlock)failureBlock
                                     progressBlock:(nullable SkuHandlerProgressBlock)progressBlock;

/**
 Download products specified by a list of product GUIDs.
 
 @param productGUIDs the list of product GUIDs
 @param completeBlock A callback called when the operation succeeds
 @param progressBlock A callback called for notifying progress
 */
- (id<CancelableTask>)downloadProducts:(NSArray<NSString*>*)productGUIDs
                         completeBlock:(void(^)(NSArray<PFProductInfo *> *productInfos, NSDictionary<NSString*,NSError*>* failed))completeBlock
                         progressBlock:(nullable SkuHandlerProgressBlock)progressBlock;

/**
 Delete products specified by a list of product GUIDs.
 
 @param productGUIDs the list of product GUIDs
 */
- (void)deleteProducts:(NSArray<NSString*>*)productGUIDs;

/**
 Check the update status of products specified by a list of product GUIDs from the server.
 
 @param successBlock A callback called when the operation succeeds
 @param failureBlock A callback called when the operation fails
 */
- (void)checkNeedToUpdateWithGuids:(NSArray<NSString*>*)productGUIDs
                      successBlock:(void(^)(NSDictionary<NSString*,NSNumber*> *skuStatus))successBlock
                      failureBlock:(SkuHandlerFailureBlock)failureBlock;

/**
 Get product metadata specified by a list of product GUIDs.
 
 @param productGUIDs the list of product GUIDs
 @return the list of product metadata
 */
- (NSArray<PFProductInfo*>* _Nullable)getProductInfosWithGuids:(NSArray<NSString*>*)productGUIDs;

/**
 Get SKU metadata specified by a list of SKU GUIDs.
 
 @param skuGUIDs the list of SKU GUIDs
 @return the list of SKU metadata
 */
- (NSArray<PFSkuInfo*>* _Nullable)getSkuInfosWithGuids:(NSArray<NSString*>*)skuGUIDs;

/**
 Download SKU sets specified by a list of SKU set GUIDs.
 
 @param skuSetGUIDs the list of SKU set GUIDs
 @param completeBlock A callback called when the operation succeeds
 */
- (id<CancelableTask>)downloadSkuSets:(NSArray<NSString*>*)skuSetGUIDs
                        completeBlock:(void(^)(NSArray<PFSkuSetInfo *> *skuSetInfos, NSDictionary<NSString*,NSError*>* failed))completeBlock;

/**
 Delete SKU sets specified by a list of SKU set GUIDs.
 
 @param skuSetGUIDs the list of SKU set GUIDs
 */
- (void)deleteSkuSets:(NSArray<NSString*>*)skuSetGUIDs;

/**
 Check the update status of SKU Sets specified by a list of SKU set GUIDs from the server.
 
 @param successBlock A callback called when the operation succeeds
 @param failureBlock A callback called when the operation fails
 */
- (void)checkNeedToUpdateWithSkuSetGuids:(NSArray<NSString *> *)skuSetGuids
                            successBlock:(void (^)(NSDictionary<NSString *,NSNumber *> * _Nonnull))successBlock
                            failureBlock:(SkuHandlerFailureBlock)failureBlock;

/**
 Get SKU set metadata specified by a list of SKU set GUIDs.
 
 @param skuSetGUIDs the list of SKU set GUIDs
 @return the list of SKU set metadata
 */
- (NSArray<PFSkuSetInfo*>* _Nullable)getSkuSetInfosWithGuids:(NSArray<NSString*>*)skuSetGUIDs;

/**
 Get Product list specified by an effect category.

 @param effect the category of makeup effect
 @return array of SKUs in `PFProductInfo`. You can call `-getListStatusByEffect:` for diagnostic information regarding the result.
 */
- (NSArray<PFProductInfo *> *)getListByEffect:(PFEffect)effect;

/**
 Get SKU set list specified by an effect category.
 
 @param effect the category of makeup effect
 @return array of SKU set infos in `PFSkuSetInfo`.
 */
- (NSArray<PFSkuSetInfo*>*)getSkuSetListByEffect:(PFEffect)effect;

/**
 Delete all downloaded SKUs and caches.
 */
- (void)clearAll;

/**
 Get the mapping completeness specified by effect category and the type.
 Use this API to check if all Product GUID/SKU GUID have the corresponding mapping. The status updated after `-getListByEffect:` returned.
 @param effect the category of makeup effect
 @return `SkuHandlerListStatus.SkuHandlerListStatusOK` if all Product GUID/SKU GUID have the corresponding mapping, `SkuHandlerListStatus.SkuHandlerListStatusMappingIncomplete` else
 @see `-getListByEffect:`
 */
- (SkuHandlerListStatus)getListStatusByEffect:(PFEffect)effect;

/**
 Update the product mapping table for mapping mode from the server.
 @param successBlock A completion block called when update completes. The parameter, succeeded, indicates the result of the operation.
 @param failureBlock A callback called when the checking fails.
 */
- (void)updateMappingFromServerWithSuccessBlock:(SkuHandlerCompleteBlock)successBlock
                                   failureBlock:(SkuHandlerFailureBlock)failureBlock;

/**
 Unavailable. Use `+sharedManager` to get object.
 */
- (id)init __attribute__((unavailable("Use +sharedManager to get object")));

/**
 Unavailable. Use `+sharedManager` to get object.
 */
+ (instancetype)new __attribute__((unavailable("Use +sharedManager to get object")));

@end

/**
 The structure of Product metadata.
 */
@interface PFProductInfo : NSObject
/// GUID of the product
@property (nonatomic, readonly) NSString *guid;
/// The vendor of the product
@property (nonatomic, readonly) NSString *vendor;
/// Readible name of the product
@property (nonatomic, readonly) NSString *name;
/// Readible name of the product, in case the name is shorten, this represents the complete name
@property (nonatomic, readonly) NSString *longName;
/// The  effect type of the product
@property (nonatomic, readonly) PFEffect effect;

/// List of SKUs contained in the product
- (NSArray <PFSkuInfo *> *)getSkus;

/// The image used for representing the product
- (NSString * __nullable)getThumbnailUrl;

@end

@class VtoDetail;
/**
 The structure of SKU metadata.
 */
@interface PFSkuInfo : NSObject

/// GUID of the product containing the SKU
@property (nonatomic, readonly) NSString *productGuid;
/// GUID of the SKU
@property (nonatomic, readonly) NSString *guid;
/// Readible name of the SKU
@property (nonatomic, readonly) NSString *name;
/// Readible name of the SKU, in case the name is shorten, this represents the complete name
@property (nonatomic, readonly) NSString *longName;
/// Customer's user data of the SKU
@property (nonatomic, readonly) NSString *customerInfo;
/// URL of the thumbnail image of the SKU
@property (nonatomic, readonly) NSString *thumbnailUrl;
/// Specify if the item is hot
@property (nonatomic, readonly) BOOL hot;

@property (nonatomic, readonly, nullable) VtoDetail* vtoDetail;
/// The action URL.
@property (nonatomic, readonly, nullable) NSString *actionUrl;
/// The action URL type.
@property (nonatomic, readonly) PFActionUrlType actionUrlType;

@end

@class PFSkuSetItemInfo;
/**
 The structure of SKU set metadata.
 */
@interface PFSkuSetInfo : NSObject
/// GUID of the SKU set
@property (nonatomic, readonly) NSString* guid;
/// Readible name of the SKU set
@property (nonatomic, readonly) NSString* name;
/// List of items contained in the SKU set
@property (nonatomic, strong) NSArray<PFSkuSetItemInfo*>* items;
@end

/**
 The structure of SKU set item metadata.
 */
@interface PFSkuSetItemInfo : NSObject
/// The related product info
@property (nonatomic, readonly) PFProductInfo* productInfo;
/// The related SKU info
@property (nonatomic, readonly) PFSkuInfo* skuInfo;
/// The related color info
@property (nonatomic, readonly) UIColor* color;

@end

NS_ASSUME_NONNULL_END
