//
//  PFFrameInfo.h
//  MakeupLib
//
//  Created by Alex Lin on 2019/1/15.
//  Copyright © 2019 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, FRAME_INFO_OPTION) {
    FRAME_INFO_NONE = 0,
    FRAME_INFO_FACE_RECT = 0x1
};

@interface PFRect : NSObject
@property (nonatomic, readonly) CGFloat x;
@property (nonatomic, readonly) CGFloat y;
@property (nonatomic, readonly) CGFloat width;
@property (nonatomic, readonly) CGFloat height;
@end

@interface PFFrameInfo : NSObject
@property (nonatomic, readonly) NSInteger faceCount;
@property (nonatomic, readonly) NSArray<PFRect*>* faceRect;
@end

NS_ASSUME_NONNULL_END
