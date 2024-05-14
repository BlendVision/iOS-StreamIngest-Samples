//
//  MakeupCam.h
//  MakeupLib
//
//  Created by PX Chen on 2018/4/24.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <PerfectLibCore/PerfectLibCore.h>

API_AVAILABLE(ios(9.0))

NS_ASSUME_NONNULL_BEGIN

/**
 Status enumeration for `PFMakeupCam`.
 */
typedef NS_ENUM(NSUInteger, PFMakeupCamLoadStatus) {
    
    /**
     The status of the `PFMakeupCam` is not ready for applying effects.
     */
    PFMakeupCamLoadStatusUnknown,
    /**
     The status of the `PFMakeupCam` is loading.
     */
    PFMakeupCamLoadStatusLoading,
    /**
     The status of the `PFMakeupCam` is ready for applying effects.
     */
    PFMakeupCamLoadStatusReady,
    /**
     The status of the `PFMakeupCam` is load model failed.
     */
    PFMakeupCamLoadStatusFail,
} NS_SWIFT_NAME(MakeupCamLoadStatus);

/**
 Position of inserting plugin
 */
typedef NS_ENUM(NSUInteger, PFPluginPosition) {
    PFPluginPositionFront,
    PFPluginPositionBack,
} NS_SWIFT_NAME(PluginPosition);

@class PFMakeupCam;
@class PFMakeupPlugin;
@class PFFrameBufferRenderer;
@class PFFaceAlignmentData;

NS_SWIFT_NAME(MakeupCamDelegate)
/**
 This protocol provides information of the `PFMakeupCam` object.
 */
@protocol PFMakeupCamDelegate <NSObject>

/**
 This delegate method is called when the status of the `PFMakeupCam` object is changed.
 
 @param makeupCam The `PFMakeupCam` instance.
 @param loadStatus The status of the `PFMakeupCam` object.
 */
- (void)pfMakeupCam:(PFMakeupCam *)makeupCam didChangeLoadStatus:(PFMakeupCamLoadStatus)loadStatus;

@optional

/**
 The delegate method is called when face landmarks updated.
 
 @param makeupCam The `PFMakeupCam` instance.
 @param alignmentData The face landmarks
 */
- (void)pfMakeupCam:(PFMakeupCam *)makeupCam faceLandmarkUpdate:(PFFaceAlignmentData*)alignmentData;

@end

typedef NS_ENUM(NSUInteger, PupilFaceAreaQuality) {
    PupilFaceAreaQualityUnknown,
    PupilFaceAreaQualityTooSmall,
    PupilFaceAreaQualityTooLarge,
    PupilFaceAreaQualityOutOfBoundary,
    PupilFaceAreaQualityGood,
};

typedef NS_ENUM(NSUInteger, PupilFaceFrontalQuality) {
    PupilFaceFrontalQualityUnknown,
    PupilFaceFrontalQualityBad,
    PupilFaceFrontalQualityGood,
};

typedef NS_ENUM(NSUInteger, PupilLightingQuality) {
    PupilLightingQualityUnknown,
    PupilLightingQualityDark,
    PupilLightingQualityNormal,
    PupilLightingQualityGood,
    PupilLightingQualityUneven,
};

typedef NS_ENUM(NSUInteger, PupilNakedEyeQuality) {
    PupilNakedEyeQualityUnknown,
    PupilNakedEyeQualityYes,
    PupilNakedEyeQualityNo,
};

/**
 The result quality of pupil analysis.
 */
@interface PupilQualityCheck: NSObject
/**
 The face position quality
 */
@property (nonatomic, readonly) PupilFaceAreaQuality faceAreaQuality;
/**
 The frontal face position quality
*/
@property (nonatomic, readonly) PupilFaceFrontalQuality faceFrontalQuality;
/**
 The lighting quality
 */
@property (nonatomic, readonly) PupilLightingQuality lightingQuality;
/**
 The naked eye quality
 */
@property (nonatomic, readonly) PupilNakedEyeQuality nakedEyeQuality;
@end

/**
 The result of pupil analysis.
 */
@interface PupilData: NSObject
/// estimated pupil distance
@property (nonatomic, readonly) CGFloat pupilDistance;
/// `true` if the data is valid.
@property (nonatomic, readonly) BOOL isValid;
@end

typedef void (^PFMakeupCamPupilAnalysis)(PupilData* __nullable report, PupilQualityCheck* __nullable qualityCheck);

NS_SWIFT_NAME(MakeupCam)
/**
 The class captures the camera frames and applies virtual makeup.
 
 Create a `PFMakeupCam` object with `+[PFMakeupCam createWithCameraView:completion:]`. This function creates the makeup camera and puts a virtual makeup view on a given view. The `PFMakeupCam` object is returned in the completion block.
 */
@interface PFMakeupCam : NSObject
@property (nonatomic, nullable, readonly) NSArray<NSNumber*>* availableFunctionalities;

/**
 Initialize a `PFMakeupCam` object.
 
 @note This initializer init the `PFMakeupCam` object without AVCaptureDevice created. The video frame will be send to the object by `-[PFMakeupCam sendFrame:]`.
 @param view The superview for the rendering view of the `PFMakeupCam` object
 @return `PFMakeupCam` instance
 @warning Deprecated - use `+[PFMakeupCam createWithCameraView:completion:]` instead.
 */

- (instancetype)initWithCameraView:(UIView *)view __attribute__ ((deprecated));
/**
 Initialize a `PFMakeupCam` object.
 
 @note This initializer init the `PFMakeupCam` object without AVCaptureDevice created. The video frame will be send to the object by `-[PFMakeupCam sendFrame:]`.
 @param view The superview for the rendering view of the `PFMakeupCam` object
 @param delegate An object implements `PFMakeupCamDelegate` protocol for receiving `PFMakeupCam` object status change
 @return `PFMakeupCam` instance
 @warning Deprecated - use `+[PFMakeupCam createWithCameraView:delegate:completion:]` or `+[PFMakeupCam createWithDelegate::completion:]` instead.
 */
- (instancetype)initWithCameraView:(UIView *)view
                          delegate:(id<PFMakeupCamDelegate> _Nullable)delegate NS_DESIGNATED_INITIALIZER __attribute__ ((deprecated));

- (instancetype)initWithDelegate:(id<PFMakeupCamDelegate>)delegate
               completionHandler:(void (^)(PFFrameBufferRenderer *renderer))completionHandler NS_DESIGNATED_INITIALIZER __attribute__ ((deprecated));

/**
 Create a `PFMakeupCam` instance.
 
 @note This initializer init the `PFMakeupCam` object without AVCaptureDevice created. The video frame will be send to the object by `-[PFMakeupCam sendFrame:]`.
 @param view The superview for the rendering view of the `PFMakeupCam` object
 @param completion A completion called when the init operation completes.
*/
+ (void)createWithCameraView:(UIView *)view 
                  completion:(void (^)(PFMakeupCam * _Nullable makeupCam, NSError * _Nullable error))completion;


/**
 Create a `PFMakeupCam` instance.
 
 @note This initializer init the `PFMakeupCam` object without AVCaptureDevice created. The video frame will be send to the object by `-[PFMakeupCam sendFrame:]`.
 @param view The superview for the rendering view of the `PFMakeupCam` object
 @param delegate An object implements `PFMakeupCamDelegate` protocol for receiving `PFMakeupCam` object status change
 @param completion A completion called when the init operation completes.
*/
+ (void)createWithCameraView:(UIView *)view
                    delegate:(id<PFMakeupCamDelegate> _Nullable)delegate
                  completion:(void (^)(PFMakeupCam * _Nullable makeupCam, NSError * _Nullable error))completion;

+ (void)createWithAccessoryCam:(id)accessoryCam
                      delegate:(id<PFMakeupCamDelegate> _Nullable)delegate
                    completion:(void (^)(PFMakeupCam * _Nullable makeupCam, NSError * _Nullable error))completion;

+ (void)createWithDelegate:(id<PFMakeupCamDelegate> _Nullable)delegate
                completion:(nonnull void (^)(PFMakeupCam * _Nullable makeupCam, PFFrameBufferRenderer * _Nullable renderer, NSError * _Nullable error))completion;

/**
 Get the loading status of the `PFMakeupCam` object.
 */
@property (assign, nonatomic, readonly) PFMakeupCamLoadStatus loadStatus;

/**
 Set enable/disable comparison mode. Comparison mode splits the camera view into two parts. The left side is the original image, and the right side is the image with effects. The comparison mode is disabled by default.
 */
@property (nonatomic) BOOL enableComparison;

/**
 Set enable/disable the kiss detection. If the property is enabled, an event is generated when kiss action is detected. The kiss detection is disabled by default.
 @note `PFMakeupCamDelegate didDetectKiss:` will be called when the event occurs.
 */
@property (nonatomic) BOOL enableKissDetection;

/**
 Set the position of the splitter for the comparison mode. The position is represented by a floating-point value between 0.0 and 1.0. Default value is 0.5.
 */
@property (nonatomic) CGFloat comparisonPosition;

/**
 Set enable/disable 4 split screen mode, manipulate the MakeupCam:currentFaceIndex to apply effect on differ face.
 @note turn off this value will reset the currentFaceIndex to 0 automatically.
 */
@property (nonatomic) BOOL enable4SplitScreen;

/**
 Set enable/disable the skin smooth on face only. If the property is enabled, the detected face will be whitened. The skin smooth on face only is disabled by default.
 */
@property (nonatomic) BOOL enableSkinSmoothFaceOnly;

/**
 The index of current face for the makeup effect applying. 0: top left. 1: top right. 2: bottom left. 3: bottom right.
 For eyewear and headband effect, face index greater than 0 would be ignored.
 @note this value should always be 0 if MakeupCam:enable4SplitScreen is off.
 */
@property (nonatomic) int currentFaceIndex;

/**
 Get information of current frame.
 
 @param option A option mask to specify which info is required
 */
- (PFFrameInfo*)getCurrentFrameInfo:(FRAME_INFO_OPTION)option;

- (void)clearView;

#pragma mark - Plug In filter control

/**
 Set the plugin for customization operation in openGL
 @param makeupPlugin the plugin to be inserted, nil to remove the inserted plugin
 @param pos the position of the plugin, front(before the makeup effects are applied) or back(after all makeup effects are applied)
 */
- (void)setPlugin:(PFMakeupPlugin * __nullable)makeupPlugin position:(PFPluginPosition)pos;

#pragma mark - Camera related API

/**
 Send a video frame to the `PFMakeupCam` object create with opening AVCaptureDevice.
 
 @param buffer The frame from AVCaptureDevice in YUV format.
 */
- (void)sendFrame:(CMSampleBufferRef)buffer;

/**
 Tells the `PFMakeupCam` object, the AVCaptureDevice is already opened and ready to send frame.
 
 @param isFront Notify the object whether the opened camera is front facing camera or rear camera.
 */
- (void)onCameraOpen:(BOOL)isFront;

/**
 Capture the current image frames.
 
 @param completion A completion called when the frames are captured. The parameters of the block are the original image(originalImage), the processed image(makeupImage), and the state of the operation(isSuccess).
 */
- (void)takePicture:(void (^)(UIImage *originalImage, UIImage *makeupImage, bool isSuccess))completion;

/**
 Start video recording.
 
 @param recordFilePath The output path of the recorded video.
 @param completionHandler A block object to be executed when the operation done.
 */
- (BOOL)startRecording:(NSURL *)recordFilePath completionHandler:(void (^)(void))completionHandler;

/**
 Stop video recording.
 @note The video will be available after the completion block is called.
 
 @param completionHandler A completion called when video recording completes.
 */
- (void)stopRecordingWithCompletionHandler:(void (^ _Nullable)(void))completionHandler;

///**
// Get the camera object for seamless switching between features.
// @return `PFCameraCore` instance
//*/
//- (PFCameraCore *)getCameraCore;

/**
 Start the data flow of the camera.
 */
- (void)play;
/**
 Pause the data flow of the camera.
 */
- (void)pause;
/**
 Resume the data flow of the camera.
 */
- (void)resume;
/**
 Stop the data flow of the camera.
 */
- (void)stop;

#pragma mark - Cube eyewear
/**
 Set a callback to receive pupil analysis report.
 @param callback the callback block to be called when analysis status updates.
 */
- (void)setPupilAnalysisCallback:(PFMakeupCamPupilAnalysis __nullable)callback;

/**
 Configure pupil distance.
 @param pupilDistance The estimated puil distance requested from `setPupilAnalysisCallback` or self determined distance.
 */
- (void)setPupilDistance:(CGFloat)pupilDistance;

#pragma mark -
/**
 Unavailable. Use `+[PFMakeupCam createWithCameraView:delegate:complete:]` to create`PFMakeupCam` object.
 */
- (id)init __attribute__((unavailable("Use +create")));

/**
 Unavailable. Use `+[PFMakeupCam createWithCameraView:delegate:complete:]` to create `PFMakeupCam` object.
 */
+ (instancetype)new __attribute__((unavailable("Use +create")));

@end

NS_ASSUME_NONNULL_END



