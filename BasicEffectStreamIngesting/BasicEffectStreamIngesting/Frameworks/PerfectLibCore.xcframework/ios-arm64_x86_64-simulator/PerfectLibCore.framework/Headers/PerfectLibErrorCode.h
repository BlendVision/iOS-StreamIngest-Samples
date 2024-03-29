//
//  PerfectLibErrorCode.h
//  MakeupSDK
//
//  Created by Peni on 2018/7/10.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 PerfectLib-related Error Codes, Constants used by NSError to indicate errors in the PerfectLib domain
 */
typedef NS_ENUM(NSInteger, PerfectLibErrorCode) {
    /**
     Undefined errors, check the NSLocalizedDescriptionKey in NSError for further information..
     */
    PerfectLibErrorCodeOther                    = -1,
    /**
     To resolve this error, please check the statusCode in the NSError's userInfo for further information.
     - If the statusCode equal to 600, that means a general authorization failure occurred, may related to a network issue.
     - If the statusCode equal to 601, means the app's bundle id isn't registered.
     - If the statusCode equal to 602, means the ip address isn't valid by the contract.
     - If the statusCode equal to 603, means the SDK authorization was expired.
     - If the statusCode equal to 604, means the SDK's activation quota exceeded.
     */
    PerfectLibErrorCodeAuthorizationFailed      = -2,
    /**
     The related model file(s) aren't installed or not ready yet.
     */
    PerfectLibErrorCodeModuleLoadFailed         = -3,
    /**
     General invalid arguments errors, check the NSLocalizedDescriptionKey in NSError for further information.
     */
    PerfectLibErrorCodeInvalidArguments         = -4,
    /**
     General unsupported errors, enable the `+[PerfectLib setDebugMode:]` and check the error message on debug console in Xcode to gain more information.
     */
    PerfectLibErrorCodeNotSupport               = -5,
    /**
     The makeup product isn't supported by current SDK version.
     */
    PerfectLibErrorCodeSkuNotSupported          = -6,
    /**
     The SKU id wasn't found on the [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeSkuNotFound              = -7,
    /**
     The Look id wasn't found on the [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeLookNotFound             = -8,
    /**
     The Look isn't supported by current SDK version.
     */
    PerfectLibErrorCodeLookNotSupported         = -9,
    /**
     The related pattern while downloading Look or makeup product wan't found on the [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeIdSystemDataNotFound     = -10,
    /**
     The network connection issue.
     */
    PerfectLibErrorCodeNoNetworkConnection      = -11,
    /**
     We can't find any faces inside the input image for `-[PFPhotoMakeup setImage:successBlock:failureBlock]`.
     */
    PerfectLibErrorCodeDetectFailed             = -12,
    /**
     To download makeup products or Looks, the country code must setup in advance.
     @see `+[PerfectLib setCountryCode:]`
     */
    PerfectLibErrorCodeCountryCodeNotSet        = -13,
    /**
     To download makeup products or Looks, the locale code must setup in advance.
     @see `+[PerfectLib setLocaleCode:]`
     */
    PerfectLibErrorCodeLocaleCodeNotSet         = -14,
    /**
     The product can't find the corresponding id setup from [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeProductMappingFailed     = -15,
    /**
     The Sku set id wasn't found on the [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeSkuSetNotFound           = -16,
    /**
     The face index for `PFMakeupCam` is invalid, the input range should be 0~3.
     */
    PerfectLibErrorCodeInvalidFaceIndex         = -17,
    /**
     The preload content have some missing items, enable the `+[PerfectLib setDebugMode:]` and check the error message on debug console in Xcode to gain more information.
     */
    PerfectLibErrorCodeContentIssue             = -18,
    /**
     There is not available product for recommendation, call `-[RecommendationHandler syncServer:successBlock:failureBlock:progressBlock:]`.
     */
    PerfectLibErrorCodeNoShadeFinderProduct     = -19,
    /**
     The hair color survey result is empty.
     */
    PerfectLibErrorCodeNoSurveyResult           = -20,
    /**
     call `-[RecommendationHandler syncServer:successBlock:failureBlock:progressBlock:]` before using any product recommendation features.
     */
    PerfectLibErrorCodeNoSurveySetting          = -21,
    /**
     The `-[RecommendationHandler syncServer:successBlock:failureBlock:progressBlock:]` is syncing.
     */
    PerfectLibErrorCodeSurveySyncing            = -22,
    /**
     There will be an issue if PerfectLib's frameworks version are difference, make sure the all frameworks are from same place instead some frameworks are from previous version.
     */
    PerfectLibErrorCodeVersionMismatch          = -23,
    /**
     To use the recommendation feature for skincare, the setting id and survey id must setup in advance.
     @see `-[PerfectLibConfigurationBuilder SetSkinCareSurveyId:andSettingId:]`.
     */
    PerfectLibErrorCodeSkinCareRecommendationIdNotSet = -24,
    /**
     The fun sticker item wasn't found in preload content.
     */
    PerfectLibErrorCodeFunStickerNotFound       = -25,
    /**
     The fun sticker isn't supported by current SDK version.
     */
    PerfectLibErrorCodeFunStickerNotSupported   = -26,
    /**
     Face rectangle out of boundary.
     */
    PerfectLibErrorCodeFaceRectOutOfBoundary    = -27,
    /**
     Face attribute analyzer only supports single face in a photo.
     */
    PerfectLibErrorCodeMultiFaceNotSupported    = -28,
    /**
     The background item wasn't found on the [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeBackgroundNotFound       = -29,
    /**
     The Tutorial item wasn't found on the [Perfect Console](https://business.perfectcorp.com).
     */
    PerfectLibErrorCodeTutorialNotFound         = -30,
};

/// Error domain on `PerfectLib`.
extern NSString * const PerfectLibErrorDomain;
