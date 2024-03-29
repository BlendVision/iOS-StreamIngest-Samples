//
//  MakeupItemStatus.h
//  MakeupSDK
//
//  Created by Alex Lin on 2018/9/11.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#ifndef MakeupItemStatus_h
#define MakeupItemStatus_h

typedef NS_ENUM(NSInteger, PerfectLibItemStatus) {
    PerfectLibItemStatusUpdated = 0,
    PerfectLibItemStatusOutdated,
    PerfectLibItemStatusNotFound,
    PerfectLibItemStatusNotSupported,
};

#endif /* MakeupItemStatus_h */
