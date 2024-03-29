//
//  LookSetting.h
//  MakeupLib
//
//  Created by PX Chen on 2019/7/9.
//  Copyright © 2019 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Use this class to apply Look effect by `-[PFVtoApplier applyLookSetting:successBlock:failureBlock:progressBlock:]`.
@interface LookSetting : NSObject
/**
 Unavailable. Use `-[LookSettingBuilder create]` to get instance.
 */
- (id)init __attribute__((unavailable("Use `LookSettingBuilder:create` to get instance")));

/**
 Unavailable. Use `-[LookSettingBuilder create]` to get instance.
 */
+ (instancetype)new __attribute__((unavailable("Use `LookSettingBuilder:create` to get instance")));

@end

/// A builder class to create the `LookSetting` instance.
@interface LookSettingBuilder : NSObject
/// Setup Look's GUID
/// @param GUID the guid of a look.
- (LookSettingBuilder *)SetGuid:(NSString *)GUID;
/// To create a `LookSetting` instance.
- (LookSetting * _Nullable)create;
@end


NS_ASSUME_NONNULL_END
