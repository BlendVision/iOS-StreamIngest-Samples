//
//  CancelableTask.h
//  MakeupSDK
//
//  Created by Alex Lin on 2018/10/16.
//  Copyright © 2018 Perfect Corp. All rights reserved.
//

#ifndef CancelableTask_h
#define CancelableTask_h

@protocol CancelableTask <NSObject>
@required
- (void)cancel;
- (BOOL)isCanceled;

@end

#endif /* CancelableTask_h */
