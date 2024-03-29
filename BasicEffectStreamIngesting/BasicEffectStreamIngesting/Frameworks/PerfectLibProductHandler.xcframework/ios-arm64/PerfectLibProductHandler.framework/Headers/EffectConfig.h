//
//  EffectConfig.h
//  MakeupLib
//
//  Created by Alex Lin on 2019/6/5.
//  Copyright © 2019 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// The configuration of hair dye.
@interface HairDyeEffectConfig : NSObject
/// Coverage ratio is the coverage of color 1 and color 2. , value ranges from -1 to 1
@property (nonatomic, assign) CGFloat coverageRatio;

/// Blend strength is the effect between the 2 colors. Value ranges from 0 to 100. If blend strength is 0, the difference between the two colors will be very obvious.
@property (nonatomic, assign) CGFloat blendStrength;
@end

/// To config the specified effect
@interface EffectConfig : NSObject

/// Effect config for hair dye.
@property (nonatomic, strong) HairDyeEffectConfig* hairDyeEffectConfig;
@end

NS_ASSUME_NONNULL_END
