//
//  PFFrameBufferRenderer.h
//  PerfectLibMakeup
//
//  Created by Steven Chen on 2021/2/4.
//  Copyright © 2021 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class PFFrameBufferRenderer;
NS_SWIFT_NAME(FrameBufferRendererDelegate)
@protocol PFFrameBufferRendererDelegate <NSObject>

- (void)onDirty:(PFFrameBufferRenderer * __nullable)renderer;

@end

/**
 The class provide customized renderer for `PFMakeupCam`
 
 @see `-[PFMakeupCam initWithDelegate:completionHandler:]`
 */
NS_SWIFT_NAME(FrameBufferRenderer)
@interface PFFrameBufferRenderer : NSObject

/// The delegate to reveive `PFMakeupCam` rendering request
@property (weak, nonatomic) id<PFFrameBufferRendererDelegate> delegate;

/**
 Assign the context to the render
 
 @param context is an EAGLContext object, it is the GL context for rendering
 */
- (void)onEGLContextCreated:(id)context;

/**
 Call to render the frame buffer into context
 
 @param frameBuffer the frame buffer to be rendered
 */
- (void)onDraw:(GLuint)frameBuffer;

/**
 Release the allocated resources
 */
- (void)releaseResource;

@end

NS_ASSUME_NONNULL_END
