//
//  ApplyEffectCallbackBlock.h
//  MakeupSDK
//
//  Created by Peni on 2018/7/4.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#ifndef ApplyEffectCallbackBlock_h
#define ApplyEffectCallbackBlock_h

typedef void (^ApplyEffectSuccessBlock)(UIImage * _Nullable resultImage);
typedef void (^ApplyEffectCompletionBlock)(BOOL isFinished);
typedef void (^ApplyEffectFailureBlock)(NSError * _Nullable error);
typedef void (^ApplyEffectProgressBlock)(CGFloat progress);

#endif /* ApplyEffectCallbackBlock_h */
