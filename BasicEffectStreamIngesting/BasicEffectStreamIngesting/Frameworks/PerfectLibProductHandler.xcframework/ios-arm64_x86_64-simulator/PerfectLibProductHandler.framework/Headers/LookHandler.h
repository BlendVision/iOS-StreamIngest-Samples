//
//  LookHandler.h
//  MakeupSDKDemo2
//
//  Created by PX Chen on 2018/6/6.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<PerfectLibCore/PerfectLibCore.h>)
#import <PerfectLibCore/PerfectLibCore.h>
#elif __has_include(<PerfectLibSlimCore/PerfectLibSlimCore.h>)
#import <PerfectLibSlimCore/PerfectLibSlimCore.h>
#endif


NS_ASSUME_NONNULL_BEGIN

typedef void (^LookHandlerCompleteBlock)(BOOL result);
typedef void (^LookHandlerFailureBlock)(NSError *error, NSString *message);
typedef void (^LookHandlerProgressBlock)(float progress);

extern NSString * const LookHandlerSaveLookForLaterDone;

/**
 Different types of look.
 */
typedef NS_ENUM(NSUInteger, PFLookType) {
    PFLookTypeMakeup,
#if __has_include(<PerfectLibCore/PerfectLibCore.h>)
    PFLookTypeNail,
#endif
};

@class PFLookInfo;

/**
 LookHandler provides Look related APIs.
 
 - Use `-[LookHandler checkNeedToUpdate:failureBlock:]` to check if the server updates Looks.
 - If the server updated Looks, use `-[LookHandler syncServer:completeBlock:failureBlock:]` to get updated Look list from the server.
 - To download specific Looks by calling `-[LookHandler downloadLooks:completeBlock:progressBlock:]` with Look GUIDs.
 - Delete downloaded Looks from local storage by calling `-[LookHandler clearAll]` or `-[LookHandler deleteLooks:]`.
 */
@interface LookHandler : NSObject

/// Get the instance of `LookHandler`.
+ (LookHandler *)sharedManager;

/**
 Check if the server updates Looks.
 
 @param type The type of look (makeup / nail) that server updates.
 @param completeBlock A callback called when the checking completes.
 @param failureBlock A callback called when the checking fails.
 */
- (void)checkNeedToUpdate:(PFLookType)type
            completeBlock:(LookHandlerCompleteBlock)completeBlock
             failureBlock:(LookHandlerFailureBlock)failureBlock;

/**
 Retrieve updated Look list from the server.
 @note this function will *NOT* download look, but only get the published look list on [Perfect Console](https://business.perfectcorp.com). To download a look, call `-downloadLooks:completeBlock:progressBlock:`.
 @param type The type of look (makeup / nail) that server updates.
 @param completeBlock A callback called when the operation completes.
 @param failureBlock A callback called when the operation fails.
 */
- (void)syncServer:(PFLookType)type
     completeBlock:(LookHandlerCompleteBlock)completeBlock
      failureBlock:(LookHandlerFailureBlock)failureBlock;

/**
 Download Looks specified by a list of Look GUIDs.
 
 @param lookGuids The list of Look GUIDs
 @param completeBlock A callback called when download operation completes. The parameter, lookInfos, is a mapping from Look GUIDs to Look metadata. The parameter, downloadFailed, is a mapping from Look GUIDs to error codes.
 @param progressBlock A callback called when each look is downloaded. The parameter, downloadedCount, indicates the number of downloaded Looks. The parameter, totalCount, indicates the total number of Looks.
 */
- (id<CancelableTask>)downloadLooks:(NSArray<NSString*>*)lookGuids
                      completeBlock:(void(^)(NSArray<PFLookInfo *> *lookInfos, NSDictionary<NSString*,NSError*>* downloadFailed))completeBlock
                      progressBlock:(nullable void(^)(NSInteger downloadedCount, NSInteger totalCount, CGFloat progress))progressBlock;

/**
 Delete Looks specified by a list of Look GUIDs from local storage.
 
 @param lookGUIDs The list of Look GUIDs
 */
- (void)deleteLooks:(NSArray<NSString*>*)lookGUIDs;

/**
 Check the update status of Looks specified by a list of Look GUIDs from the server.
 
 @param lookGUIDs The list of Look GUIDs
 @param successBlock A callback called when the operation completes.
 @param failureBlock A callback called when the operation failed.
 */
- (void)checkNeedToUpdateWithGuids:(NSArray<NSString*>*)lookGUIDs
                      successBlock:(void(^)(NSDictionary<NSString*,NSNumber*> *skuStatus))successBlock
                      failureBlock:(LookHandlerFailureBlock)failureBlock;

/**
 Get Look metadata specified by a list of Look GUIDs.
 
 @param lookGUIDs The list of Look GUIDs
 @return The list of Look metadata
 */
- (NSArray<PFLookInfo*>* _Nullable)getLookInfosWithGuids:(NSArray<NSString*>*)lookGUIDs;

/**
 Get Look list.
 @note This function returns the list of all downloaded look and preloaded look if `-[LookHandler syncServer:completeBlock:failureBlock:]` never called before, once the `-[LookHandler syncServer:completeBlock:failureBlock:]` is called and succeeded, it only returns the list of the published looks on [Perfect Console](https://business.perfectcorp.com).
 @param lookType The type of look (makeup / nail) that will be queried.
 @return The list of the Look metadata
 */
- (NSArray <PFLookInfo *>*)getList:(PFLookType)lookType;

/**
 Clear all downloaded Looks and related data from local storage.
 @param type specifies the type of look to be cleared.
 */
- (void)clearAll:(PFLookType)type;

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
 The look information for UI displaying.
 Generated by `-[LookHandler getList:]`
 */
@interface PFLookInfo : NSObject

/// Look GUID
@property (nonatomic, readonly) NSString *guid;
/// Look name
@property (nonatomic, readonly) NSString *name;
/// Look description
@property (nonatomic, readonly) NSString *lookDescription;
/// Indicate the look is downloaded or not.
@property (nonatomic, readonly) BOOL isDownloaded;

/// Look thumbnail URL
- (NSString* __nullable)getThumbnailUrl;
@end

NS_ASSUME_NONNULL_END

