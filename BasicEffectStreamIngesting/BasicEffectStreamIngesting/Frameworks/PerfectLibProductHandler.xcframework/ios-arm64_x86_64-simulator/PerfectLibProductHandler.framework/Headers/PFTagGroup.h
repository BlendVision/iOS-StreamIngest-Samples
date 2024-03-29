//
//  PFTagGroup.h
//  PerfectLib
//
//  Created by PX Chen on 2020/2/11.
//  Copyright © 2020 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The structure of tag group meta data
 */
NS_SWIFT_NAME(TagGroup)
@interface PFTagGroup : NSObject
/// The identifier of the tag group
@property (nonatomic, readonly) NSString *tagGroupId;
/// The readable name of the tag group.
@property (nonatomic, readonly) NSString *name;
/// Specifies whether this is a free tag.
@property (nonatomic, readonly) BOOL isFreeTag;

@end

NS_ASSUME_NONNULL_END
