//
//  MakeupEffectBlock.h
//  MakeupSDK
//
//  Created by PXChen on 2018/1/30.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AccessoryEffectProfile.h"

@interface MakeupEffectNecklaceProfile : AccessoryEffectProfile
{
    @public
    NSString* obbPath;
    CGPoint anchorLeft;
    CGPoint anchorRight;
}
@end
