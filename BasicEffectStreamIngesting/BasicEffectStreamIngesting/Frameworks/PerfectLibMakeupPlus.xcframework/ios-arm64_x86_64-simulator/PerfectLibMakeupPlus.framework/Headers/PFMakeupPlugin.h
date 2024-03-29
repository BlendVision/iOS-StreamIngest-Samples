//
//  PFMakeupPlugin.h
//  MakeupSDK
//
//  Created by PX Chen on 2018/6/20.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

NS_ASSUME_NONNULL_BEGIN

@protocol PFMakeupPluginDelegate <NSObject>

- (void)addAttributes:(NSString *)attributeName;
- (GLint)updateAttributes:(NSString *)attributeName;
- (GLint)uniformIndex:(NSString *)uniformName;
- (GLuint)getTextureIDwithSize:(CGSize)size;

- (GLint)firstInputFramebufferTextureID;
- (GLint)filterInputTextureUniform;
- (GLint)filterPositionAttribute;
- (GLint)filterTextureCoordinateAttribute;

- (void)unlockFirstInputFramebuffer;

- (void)renderAtInternal;

@end

//@class PFFaceAlignmentData;

/**
 An object that inserts a customized shader in makeup cam.
 */
@interface PFMakeupPlugin : NSObject

@property (weak, nonatomic, nullable) id<PFMakeupPluginDelegate> delegate;

/**
 Setup vertex shader.
 */
@property (nonatomic) NSString *vertexShaderString;

/**
 Setup fragment shader.
 */
@property (nonatomic) NSString *fragmentShaderFromString;

/**
 Run block in Video processing queue asynchronously.

 @param block code will run under video processing queue.
 */
+ (void)PF_runAsynchronouslyOnVideoProcessingQueue:(void (^)(void))block;

/**
 Run block in Video processing queue asynchronously.
 
 @param block code will run under video processing queue.
 */
+ (void)PF_runSynchronouslyOnVideoProcessingQueue:(void (^)(void))block;

/**
 Execute rendering.
 */
- (void)renderToTextureWithVertices:(const GLfloat *)vertices textureCoordinates:(const GLfloat *)textureCoordinates;

/**
 Execute rendering at internal texture.
 */
- (void)renderInternal;

/**
 init open gl attributes.
 */
- (void)initializeAttributes;

/**
 Update value with glProgram.
 */
- (void)updateProgram;

/**
 Overwrite this function to get notification for new frame ready.
 */
- (void)newFrameReadyAtTime:(CMTime)frameTime atIndex:(NSInteger)textureIndex;

/**
 Overwrite this function to tell the MakeupCam this plugin is used to be a filter, e.g., draw blur effect, or an output, e.g., a raw output for video streaming.
 
 @return YES if this plugin is a filter. NO if this plugin is an output.
 */
- (BOOL)pluginIsFilter;

/**
 Get current EAGLContext object.

 @return glContext.
 */
- (id)glContext;

@end

NS_ASSUME_NONNULL_END
