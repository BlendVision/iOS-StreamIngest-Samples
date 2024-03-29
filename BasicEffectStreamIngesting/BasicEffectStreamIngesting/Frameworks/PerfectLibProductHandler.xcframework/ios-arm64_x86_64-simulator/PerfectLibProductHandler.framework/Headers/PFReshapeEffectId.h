//
//  PFReshapeEffectId.h
//  PerfectLibHandlerCore
//
//  Created by PX Chen on 2021/6/11.
//  Copyright © 2021 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<PerfectLibCore/PerfectLibCore.h>)
#import <PerfectLibCore/PFReshapeEffect.h>
#elif __has_include(<PerfectLibSlimCore/PerfectLibSlimCore.h>)
#import <PerfectLibSlimCore/PFReshapeEffect.h>
#endif

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(ReshapeEffectId)
@interface PFReshapeEffectId : NSObject
@property (nonatomic, readonly) PFReshapeEffect type;
@property (nonatomic, readonly) int intensity;
@end

NS_ASSUME_NONNULL_END
