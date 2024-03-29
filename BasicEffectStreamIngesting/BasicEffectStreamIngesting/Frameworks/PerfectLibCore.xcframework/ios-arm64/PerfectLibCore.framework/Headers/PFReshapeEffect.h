//
//  PFReshapeEffect.h
//  MakeupSDK
//
//  Created by PX Chen on 2021/6/11.
//  Copyright © 2021 Perfect Corp. All rights reserved.
//

#ifndef PFReshapeEffect_h
#define PFReshapeEffect_h

/**
 The values representing effects for reshape.
 */
typedef NS_ENUM(NSUInteger, PFReshapeEffect) {
    PFReshapeEffectFaceShapeOverall,
    PFReshapeEffectFaceShapeLeft,
    PFReshapeEffectFaceShapeRight,
    PFReshapeEffectFaceWidth,
    PFReshapeEffectJaw,
    
    PFReshapeEffectCheekbone,
    
    PFReshapeEffectChinShapeOverall,
    PFReshapeEffectChinShapeLeft,
    PFReshapeEffectChinShapeRight,
    PFReshapeEffectChinLength,
    
    PFReshapeEffectNoseSize,
    PFReshapeEffectNoseLift,
    PFReshapeEffectNoseBridge,
    PFReshapeEffectNoseTip,
    PFReshapeEffectNoseWing,
    PFReshapeEffectNoseWidth,
    
    PFReshapeEffectLipSize,
    PFReshapeEffectLipWidth,
    PFReshapeEffectLipHeightOverall,
    PFReshapeEffectLipHeightOverallUpper,
    PFReshapeEffectLipHeightOverallLower,
    PFReshapeEffectLipPeak,
    
    PFReshapeEffectEyeSizeOverall,
    PFReshapeEffectEyeSizeLeft,
    PFReshapeEffectEyeSizeRight,
    PFReshapeEffectEyeWidth,
    PFReshapeEffectEyeHeight,
    PFReshapeEffectEyeDistance,
    PFReshapeEffectEyeAngle,
    
    PFReshapeEffectCount
} NS_SWIFT_NAME(ReshapeEffect);

#endif /* PFReshapeEffect_h */
