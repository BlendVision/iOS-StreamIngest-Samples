//
//  PerfectLibConfiguration.h
//  MakeupLib
//
//  Created by Alex Lin on 2019/4/8.
//  Copyright © 2019 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Represent the type of image source. The images include the thumbnails of Product, SKU, and Look.
 */
typedef NS_ENUM(NSUInteger, ImageSource) {
    /// This type indicates the images are stored in local storage.
    ImageSourceFile,
    /// This type indicates the images are not stored in local storage, use URL to locate the images.
    ImageSourceUrl,
};

/**
 Represent the quality of fun sticker.
 */
typedef NS_ENUM(NSUInteger, FunStickerQuality) {
    FunStickerQualityHD,
    FunStickerQualitySD,
};

NS_ASSUME_NONNULL_BEGIN

/**
 `PerfectLibConfiguration` is used to specify settings of `PerfectLib`.
 */
@interface PerfectLibConfiguration : NSObject
/// Specifies the config file.
@property (nonatomic, readonly) NSString* configFile;

/// Specifies the image source.
@property (nonatomic, readonly) ImageSource imageSource;

/// Specify the path of the model files. If the path is null then the model files are in APP's main bundle.
@property (nonatomic, readonly) NSString* modelsPath;

/// Specify the path containing preload data.
@property (nonatomic, readonly) NSString* preloadPath;

/// Specify the user defined ID to be send with log
@property (nonatomic, readonly) NSString* userId;

/// Mapping mode is the mode that maps product IDs and shade IDs to Perfect Corp.'s SKU IDs and SKU item IDs. Use product IDs and shade IDs to control the library when mapping mode is enabled. The mapping mode is disabled by default.
@property (nonatomic, readonly) BOOL mappingMode;

/// Preview mode is for APP to preview contents (SKUs, Looks, etc.). The contents in preview and online states will be available in preview mode. Switching preview mode clears all downloaded contents. Preview mode is disabled by default.
@property (nonatomic, readonly) BOOL previewMode;

/// For the purpose of development, enable this to bypass the country restriction.
@property (nonatomic, readonly) BOOL developerMode;

@property (nonatomic, readonly) NSString *skinCareSurveyId;

@property (nonatomic, readonly) NSString *skinCareSettingId;
/// the quality of fun sticker.
@property (nonatomic, readonly) FunStickerQuality funStickerQuality;

/**
 Unavailable. Use PerfectLibConfigurationBuilder.create to get object.
 */
- (id)init __attribute__((unavailable("Use PerfectLibConfigurationBuilder to get object")));

/**
 Unavailable. Use PerfectLibConfigurationBuilder.create to get object.
 */
+ (instancetype)new __attribute__((unavailable("Use PerfectLibConfigurationBuilder to get object")));

@end

/**
 A builder class for `PerfectLibConfiguration`.
 */
@interface PerfectLibConfigurationBuilder: NSObject
/**
 Specify the config file to be used, if not specified, config.json under app's main bundle will be used.
 */
- (PerfectLibConfigurationBuilder*)SetConfigFile:(NSString*)configFile;
/**
 Set the type of image source.
 */
- (PerfectLibConfigurationBuilder*)SetImageSource:(ImageSource)imageSource;
/**
 Set the path of the folder containing the model files. If the path is null then the model files are in APP's main bundle.
 */
- (PerfectLibConfigurationBuilder*)SetModelsPath:(NSString*)modelsPath;
/**
 Set the path of the folder containing preload data. Preload data is the data to be bundled with the app, including Products and Looks.
 */
- (PerfectLibConfigurationBuilder*)SetPreloadPath:(NSString*)preloadPath;
/**
 Set the user defined ID to be send with log.
 */
- (PerfectLibConfigurationBuilder*)SetUserId:(NSString*)userId;
/**
 Set enable/disable the preview mode.
 @note Preview mode is for APP to preview contents (SKUs, Looks, etc.). The contents in preview and online states will be available in preview mode. Switching preview mode clears all downloaded contents. Preview mode is disabled by default.
*/
- (PerfectLibConfigurationBuilder*)SetPreviewMode:(BOOL)previewMode;
/**
 Set enable/disable the mapping mode.
 @note Mapping mode is the mode that maps product IDs and shade IDs to Perfect Corp.'s SKU IDs and SKU item IDs. Use product IDs and shade IDs to control the library when mapping mode is enabled. The mapping mode is disabled by default.
*/
- (PerfectLibConfigurationBuilder*)SetMappingMode:(BOOL)mappingMode;
/**
 Set developer mode.

 Developer mode is a mode to facilitate the app development. Currently, developer mode provides below features:
 1. bypass IP address license checking
 2. on-screen overlay developer mode reminder on camera view
 3. toast developer mode reminder
 */
- (PerfectLibConfigurationBuilder*)SetDeveloperMode:(BOOL)developerMode;
/**
 Setup these two values before for skincare surveying or recommendation. These two values can be found in the Publish From on the [Perfect Console](https://business.perfectcorp.com).
 */
- (PerfectLibConfigurationBuilder *)SetSkinCareSurveyId:(NSString *)surveyId andSettingId:(NSString *)settingId;

/// The default value is FunStickerQualityHD, if this value changed compare to previous SDK init's param, all the installed fun stickers & its related look will be removed.
/// @param quality quality of fun sticker
- (PerfectLibConfigurationBuilder *)SetFunStickerQuality:(FunStickerQuality)quality;

/// To create a `PerfectLibConfiguration` instance.
- (PerfectLibConfiguration*)build;
@end

NS_ASSUME_NONNULL_END
