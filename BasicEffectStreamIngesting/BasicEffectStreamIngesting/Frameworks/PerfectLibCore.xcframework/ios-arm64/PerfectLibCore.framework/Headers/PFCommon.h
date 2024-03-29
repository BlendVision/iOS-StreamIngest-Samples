//
//  PFCommon.h
//  MakeupSDK
//
//  Created by PX Chen on 2018/6/5.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

/**
 The function list, obtains from `+[PerfectLib initWithConfiguration:successBlock:failureBlock:]`, it shows PerfectLib's abilities based on the contract.
 */
typedef NS_ENUM (NSInteger, PFFunctionality) {
    /// The ability to apply makeup related features, such as lipstick, eyeliner, eyelash...etc.
    PFFunctionalityMakeup,
    /// The ability to apply a hair color.
    PFFunctionalityHairColor,
    /// The ability to use skincare function.
    PFFunctionalitySkinCare,
    /// The ability to use shade finder function.
    PFFunctionalityShadeFinder,
    /// The ability to apply a fun sticker.
    PFFunctionalityFunSticker,
    /// The ability to apply reshape effects.
    PFFunctionalityReshape,
    /// The ability to apply eyewear function
    PFFunctionalityEyewear,
    /// The ability to apply 3D eyewear function
    PFFunctionalityEyewear3D,
    /// The ability to use face attribute analyzation function
    PFFunctionalityFaceAttribute,
    /// The ability to apply earrings function
    PFFunctionalityEarrings,
    /// The ability to apply nail function
    PFFunctionalityNail,
    /// The ability to apply ring function
    PFFunctionalityRing,
    /// The ability to apply watch function
    PFFunctionalityWatch,
    /// The ability to apply bracelet function
    PFFunctionalityBracelet,
    /// The ability to apply background function
    PFFunctionalityBackground,
    /// The ability to apply hairstylist function
    PFFunctionalityHairStylist,
    /// The ability to apply tutorial function
    PFFunctionalityTutorial,
};

/**
 Status codes for checking factor quality.
 */
typedef NS_ENUM(NSUInteger, PerfectLibQuality) {
    /**
     Unknown quality
     */
    QUALITY_UNKNOWN,
    /**
     Bad quality, need to adjust
     */
    QUALITY_NOT_GOOD,
    /**
     The quality of this factor is OK but not good
     */
    QUALITY_OK,
    /**
     The factor is in good condition
     */
    QUALITY_GOOD
};

/**
 Status codes for checking overall face area quality.
 */
typedef NS_ENUM(NSUInteger, PFFaceAreaQuality) {
    PFFaceAreaQualityUnknown,
    PFFaceAreaQualityTooSmall,
    PFFaceAreaQualityOutOfBoundary,
    PFFaceAreaQualityGood
};

/**
 Status codes for checking face angle quality.
 */
typedef NS_ENUM(NSUInteger, PFFaceFrontalQuality) {
    PFFaceFrontalQualityUnknown,
    PFFaceFrontalQualityBad,
    PFFaceFrontalQualityGood
};

/**
 Status codes for checking face center quality.
 */
typedef NS_ENUM(NSUInteger, PFFaceCenterQuality) {
    PFFaceCenterQualityUnknown,
    PFFaceCenterQualityTooLeft,
    PFFaceCenterQualityTooRight,
    PFFaceCenterQualityTooHigh,
    PFFaceCenterQualityTooLow,
    PFFaceCenterQualityGood
};

/**
 Status codes for checking lighting quality.
 */
typedef NS_ENUM(NSUInteger, PFLightingQuality) {
    PFLightingQualityUnknown,
    PFLightingQualityDark,
    PFLightingQualityNormal,
    PFLightingQualityGood,
    PFLightingQualityUneven
};

/**
 Status codes for checking lighting v2 quality.
 */
typedef NS_ENUM(NSUInteger, PFLightingQuality2) {
    PFLightingQuality2Unknown,
    PFLightingQuality2Normal,
    PFLightingQuality2Good,
    PFLightingQuality2OverExposed,
    PFLightingQuality2UnderExposed,
    PFLightingQuality2Backlighting,
    PFLightingQuality2Uneven
};

/**
 Status codes for checking eye area quality.
 */
typedef NS_ENUM(NSUInteger, PFNakedEyeQuality) {
    PFNakedEyeQualityUnknown,
    PFNakedEyeQualityNo,
    PFNakedEyeQualityYes,
};

/**
 Status codes for over all quality checking message.
 */
typedef NS_ENUM(NSUInteger, PerfectLibQualityMsg) {
    PerfectLibQualityMsgUnknown,
    PerfectLibQualityMsgGood,
    PerfectLibQualityMsgFaceAreaTooSmall,
    PerfectLibQualityMsgFaceAreaOutOfBoundary,
    PerfectLibQualityMsgLightingNormal,
    PerfectLibQualityMsgLightingOverExposed,
    PerfectLibQualityMsgLightingUnderExposed,
    PerfectLibQualityMsgLightingBacklighting,
    PerfectLibQualityMsgLightingUneven
};

/**
 The position of the face to camera.
 */
typedef NS_ENUM(NSUInteger, PerfectLibFaceSide) {
    PerfectLibFaceSideFront,
    PerfectLibFaceSideLeft,
    PerfectLibFaceSideRight,
};

/**
 The nail position on specific hand
 */
typedef NS_ENUM(NSUInteger, PFNailPosition) {
    PFNailPositionThumb = 0,
    PFNailPositionForefinger,
    PFNailPositionMiddleFinger,
    PFNailPositionRingFinger,
    PFNailPositionLittleFinger,
};
