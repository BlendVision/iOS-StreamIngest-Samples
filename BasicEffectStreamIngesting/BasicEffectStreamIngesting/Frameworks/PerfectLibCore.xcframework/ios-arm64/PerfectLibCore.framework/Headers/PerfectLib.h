//
//  PerfectLib.h
//  PerfectLib
//
//  Created by PXChen on 2017/11/9.
//  Copyright © 2017年 Perfect Corp. All rights reserved.
//

#import <UIKit/UIKit.h>
#if __has_include(<PerfectLibCore/PFCommon.h>)
#import <PerfectLibCore/PFCommon.h>
#elif __has_include(<PerfectLibSlimCore/PFCommon.h>)
#import <PerfectLibSlimCore/PFCommon.h>
#endif
#if __has_include(<PerfectLibCore/PerfectLibConfiguration.h>)
#import <PerfectLibCore/PerfectLibConfiguration.h>
#elif __has_include(<PerfectLibSlimCore/PerfectLibConfiguration.h>)
#import <PerfectLibSlimCore/PerfectLibConfiguration.h>
#endif

/**
 The strategy controls the applying of effects using local cached content or downloaded content.
 */
typedef NS_ENUM(NSUInteger, PFDownloadCacheStrategy) {
    /// The strategy forces to use the local cache if exists, otherwise download contents from server.
    PFDownloadCacheStrategyCacheFirst,
    /// The strategy checks server for contents updating information. If contents are updated, download the updated contents from server and use them. Otherwise use the local cached contents.
    PFDownloadCacheStrategyUpdateFirst,
    /// The strategy forces to use the local cache if exists, but check for update status from server. If the contents are updated, download the updated contents but install the updated contents until next MakeupLib init.
    PFDownloadCacheStrategyCacheFirstThenUpdate,
    /// The strategy use the local cache if exists.
    PFDownloadCacheStrategyCacheOnly,
};

API_AVAILABLE(ios(9.0))

__attribute__((objc_subclassing_restricted))

/**
 PerfectLib is the entry point of the library for configuration and initialization.
 
 Initialize the library using `+[PerfectLib initWithConfiguration:successBlock:failureBlock:]`. Wait until completion block is called to start virtual makeup. Call `+[PerfectLib uninit]` to release the resources used by the library.
 
 Configure the library to get the correct content using `+[PerfectLib setLocaleCode:]` and `+[PerfectLib setCountryCode:]`. Configure the maximum cache size for the downloaded content using `+[PerfectLib setMaxCacheSize:]`.
 
 To apply a virtual try-on, one or more SKUs need to be specified. SKU represents a single cosmetic product such as lipstick, palette or blush. SKU is associated by either a GUID or a vendor defined product code, such as UPC code. PerfectLib provides two modes to access the SKUs: default mode and mapping mode. For default mode, GUIDs are used to access SKUs. For mapping mode, vendor defined product codes are used to access SKUs.
 */
@interface PerfectLib : NSObject

/**
 Initialize the library with a configuration.
 
 @param configuration A configuration object that defines the library's setting.
 @param successBlock A callback block called when initialization succeeded, this block also returns two values, the first is preloadError, it's a dictionary of a product guid or a look guid to the corresponding installed error. the second one is functionList, this array will included the PerfectLib's ability  in `PFFunctionality` based on the contract.
 @param failureBlock A callback block called when initialization failed.
 */
+ (void)initWithConfiguration:(PerfectLibConfiguration*_Nullable)configuration successBlock:(void (^_Nullable)(NSDictionary* _Nullable preloadError, NSArray *_Nullable functionList))successBlock failureBlock:(void (^_Nullable)(NSError* _Nullable error))failureBlock;

/**
 Uninitialize the library and release the memory used by the library.
 @note Release the library instances, e.g., `PFMakeupCam`, before calling `+[PerfectLib uninit]`. Otherwise the operation of uninit cannot be done.
 
 @return YES: The library is successfully released. NO: Some objects of the library are still in use.
 */
+ (BOOL)uninit;

/**
 Get the library version.
 
 @return Version number in NSString format.
 */
+ (NSString * __nonnull)getVersion;

/**
 Set cache size for downloaded templates.
 @note The Look/SKU templates are downloaded from the server and cached in the local storage. When `+[PerfectLib uninit]` is called and the size of cached contents exceeds the cache limit, the library purges cached contents by least recently used strategy. The default cache size is unlimited.
 @param cacheSize Size in megabyte.
 */
+ (void)setMaxCacheSize:(unsigned long)cacheSize;

/**
 Return the value set by `+[PerfectLib setMaxCacheSize:]`.
 
 @return Cache size in megabyte. Default value is ULONG_MAX.
 */
+ (unsigned long)getMaxCacheSize;

/**
 Set locale code to specify SKU/Look content language.
 @note SKU/Look contents are managed by locale and country on the [Perfect Console](https://business.perfectcorp.com). Set locale code before downloading SKU/Look contents. Content download will fail if this function is not called. Set the value to specify the language of SKU/Look.
 @see `+setCountryCode:`

 @param localeCode A composition of the language([ISO 639-1](https://en.wikipedia.org/wiki/ISO_639-1)) and the country([ISO 3166-1 alpha-2](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2#Officially_assigned_code_elements)), which is concatenated by underscore (e.g., "en_US").
 
 @return YES: Set locale code successfully. NO: Failed to set locale code.
 */
+ (BOOL)setLocaleCode:(NSString * __nonnull)localeCode;

/**
 Get locale code that specifies SKU/Look content language.
 @return The locale code. Return nil if the locale code is not set.
 */
+ (NSString * __nullable)getLocaleCode;

/**
 Set country code to specify the country of SKU/Look content.
 @note Set country code before downloading SKU/Look contents. Content download will fail if this function is not called.

 @param countryCode [ISO 3166-1 alpha-2](https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2#Officially_assigned_code_elements), e.g., US.

 @return YES: Set country code successfully. NO: Failed to set country code.
 */
+ (BOOL)setCountryCode:(NSString * __nonnull)countryCode;

/**
 Get country code that specifies the country of SKU/Look content.
 @return the country code, if nil, the country code is never set.
 */
+ (NSString * __nullable)getCountryCode;

/**
 Set download cache strategy.
 @note Set cache strategy before applying/downloading products. The default strategy is `cacheFirst`.
 @param cacheStrategy The strategy for product download cache.
 */
+ (void)setDownloadCacheStrategy:(PFDownloadCacheStrategy)cacheStrategy;

/**
 Get current download cache strategy.
 @return The strategy of product download cache.
 */
+ (PFDownloadCacheStrategy)getDownloadCacheStrategy;

/**
 Set enable/disable debug mode. If the debug mode is enabled, the library prints the console logs and shows toasts for debugging purpose.
 @note Debug mode is disabled by default.
 
 @param debugMode YES: Enable debug mode. NO: otherwise.
 */
+ (void)setDebugMode:(BOOL)debugMode;

/**
 Unavailable. Use `+initWithCompletionHandler` for SDK initializing.
 */
+ (id __nullable)init __attribute__((unavailable("Use +initWithCompletionHandler for SDK initializing")));

/**
 Unavailable. Use `+initWithCompletionHandler` for SDK initializing.
 */
- (id __nonnull)init __attribute__((unavailable("Use +initWithCompletionHandler for SDK initializing")));

/**
 Unavailable. Use `+initWithCompletionHandler` for SDK initializing.
 */
+ (instancetype __nonnull)new __attribute__((unavailable("Use +initWithCompletionHandler for SDK initializing")));

@end

