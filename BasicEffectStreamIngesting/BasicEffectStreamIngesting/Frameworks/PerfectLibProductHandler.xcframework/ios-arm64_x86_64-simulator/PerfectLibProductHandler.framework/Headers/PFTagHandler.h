//
//  TagHandler.h
//  PerfectLib
//
//  Created by PX Chen on 2020/2/11.
//  Copyright © 2020 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

#if __has_include(<PerfectLibProductHandler/PFTagDef.h>)
#import <PerfectLibProductHandler/PFTagDef.h>
#elif __has_include(<PerfectLibSlimProductHandler/PFTagDef.h>)
#import <PerfectLibSlimProductHandler/PFTagDef.h>
#else
#error no header files found
#endif

@class PFTagGroup, PFTag;

typedef void (^TagHandlerCompleteBlock)(BOOL result);
typedef void (^TagHandlerFailureBlock)(NSError * _Nonnull error, NSString * _Nonnull message);
typedef void (^TagHandlerProgressBlock)(float progress);

NS_ASSUME_NONNULL_BEGIN

@protocol CancelableTask;

/**
* Perfect Console provides a way to categorize Products and Looks with tagging system.
* This class provides APIs to retrieve tagging information for application to manage the SKUs or Looks.
* Use `-syncServer:failureBlock:progressBlock:` to get updated tagging information from server.
* Call `-listGroupsByTagType:` with a `PFTagType` to get `PFTagGroup` list.
* Call `-listTagsByTagType:withGroupId:` with a `PFTagType` and ID of a `PFTagGroup` to get `PFTag` list.
* Call `-listGuidsByTagType:withTagId:` with a `PFTagType` and ID of a `PFTag` to get associated SKU or Look GUIDs.
* Delete downloaded data from the local storage by calling `-clearAll`.
*/
NS_SWIFT_NAME(TagHandler)
@interface PFTagHandler : NSObject

+ (PFTagHandler *)sharedManager;

/**
 Update the tagging information from server.

 @param successBlock A callback called when the operation succeeds
 @param failureBlock A callback called when the operation fails
 */
- (id<CancelableTask> _Nullable)syncServer:(TagHandlerCompleteBlock)successBlock
                              failureBlock:(TagHandlerFailureBlock)failureBlock
                             progressBlock:(nullable TagHandlerProgressBlock)progressBlock;

/// Remove all downloaded tagging data.
- (void)clearAll;

/**
 Get  the tag group list specified by a tag type.
 
 @param tagType the category of tag effect.
 @return array of groups in `PFTagGroup`.
 */
- (NSArray <PFTagGroup *> * _Nullable)listGroupsByTagType:(PFTagType)tagType;

/**
 Get  the tag list specified by the a tag type and a group ID.
 
 @param tagType the category of tag effect.
 @param groupId the group id from `PFTagGroup`.
 @return array of tags in `PFTag`.
*/
- (NSArray <PFTag *> * _Nullable)listTagsByTagType:(PFTagType)tagType withGroupId:(NSString *)groupId;

/**
 Get GUID list specified by a tag type and a tag ID.
 
 @param tagType the category of tag effect.
 @param tagId the tag id from `PFTag`.
 @return array of guids, it can be either the product Guid list or the Look Guid list depends on the tagType you input.
*/
- (NSArray <NSString *> * _Nullable)listGuidsByTagType:(PFTagType)tagType withTagId:(NSString *)tagId;

/**
 Unavailable. Use +sharedManager to get object.
 */
- (id)init __attribute__((unavailable("Use +sharedManager to get object")));

/**
 Unavailable. Use +sharedManager to get object.
 */
+ (instancetype)new __attribute__((unavailable("Use +sharedManager to get object")));

@end

NS_ASSUME_NONNULL_END
