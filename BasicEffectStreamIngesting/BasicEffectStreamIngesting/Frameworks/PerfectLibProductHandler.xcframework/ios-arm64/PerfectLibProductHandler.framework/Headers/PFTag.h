//
//  PFTag.h
//  PerfectLib
//
//  Created by PX Chen on 2020/2/11.
//  Copyright © 2020 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The structure of tag meta data
 */
NS_SWIFT_NAME(Tag)
@interface PFTag : NSObject
/// The identifier of the tag.
@property (nonatomic, readonly) NSString *tagId;
/// The readable name of the tag.
@property (nonatomic, readonly) NSString *name;
/**
 The path for the tag's thumbnail.
 @note this can be a local path or a remote url path depends on the `ImageSource` setting in `PerfectLibConfiguration`.
 */
@property (nonatomic, readonly) NSString *thumbnail;

@end

NS_ASSUME_NONNULL_END
