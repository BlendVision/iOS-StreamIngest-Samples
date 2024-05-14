//
//  PhotoEditor.h
//  MakeupLib for Photo Editing
//
//  Created by Peni on 2018/7/2.
//  Copyright © 2018年 Perfect Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

@class PFFaceData;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(PhotoMakeup)
/**
The class applies virtual makeup on faces in a photo.

To apply virtual makeup, face locations need to be identified. Use `-[PFPhotoMakeup detectFace:failureBlock:]` to identify face locations. There might be more than one faces in a photo. Use `-[PFPhotoMakeup setFace:image:]` to specified the face to edit.
*/
@interface PFPhotoMakeup : NSObject
@property (nonatomic, nullable, readonly) NSArray<NSNumber*>* availableFunctionalities;

/**
 Create a `PFPhotoMakeup` instance.
 @param image The image to be scanned
 @param completion A completion called when the init operation completes.
*/
+ (void)create:(UIImage *)image completion:(void (^)(PFPhotoMakeup * _Nullable photoMakeup, NSError * _Nullable error))completion;

/**
 Create a `PFPhotoMakeup` instance.
 @param image The image to be scanned
 @param enableWhitening Enable skin smooth with whitening effect, by turning the function on, photo processing with skin smooth effect will have same result with live mode. default value is false.
 @param completion A completion called when the init operation completes.
*/
+ (void)create:(UIImage *)image enableWhitening:(BOOL)enableWhitening completion:(void (^)(PFPhotoMakeup * _Nullable photoMakeup, NSError * _Nullable error))completion;

/**
 Create a `PFPhotoMakeup` instance.
 @param photoAccessoryAR combined photo accessory process into PFPhotoMakeup
 @param enableWhitening Enable skin smooth with whitening effect, by turning the function on, photo processing with skin smooth effect will have same result with live mode. default value is false.
 @param completion A completion called when the init operation completes.
*/
+ (void)createWithPhotoAccessoryAR:(id)photoAccessoryAR enableWhitening:(BOOL)enableWhitening completion:(void (^)(PFPhotoMakeup * _Nullable photoMakeup, NSError * _Nullable error))completion;

/**
 Identify face locations on a given image.
 
 @param successBlock A block called when face detection completes. The parameter 'faceDataArray' is an array of `PFFaceData` for faces on the image.
 @param failureBlock A block called when there is no face inside the given image.
 */
- (void)detectFace:(void (^)(NSArray<PFFaceData *> *faceDataArray))successBlock failureBlock:(void (^)(NSError *error))failureBlock;

/**
 Set the target face for applying virtual makeup.
 @see `-[PFPhotoMakeup detectFace:failureBlock:]`
 
 @param faceData The face data of a specific face, an element of the face data array returned by `-[PFPhotoMakeup detectFace:successBlock:failureBlock:]`
 @param image The image to edit
 */
- (void)setFace:(PFFaceData *)faceData image:(UIImage *)image;

/**
 Configure pupil distance.
 @param pupilDistance The estimated puil distance requested from `setPupilAnalysisCallback` or self determined distance.
 */
- (void)setPupilDistance:(CGFloat)pupilDistance;

/**
 Set enable/disable 4 split screen mode, manipulate the MakeupCam:currentFaceIndex to apply effect on differ face.
 @note turn off this value will reset the currentFaceIndex to 0 automatically.
 */
- (void)enable4SplitScreen:(BOOL)isEnabled completion:(void (^)(UIImage *image))completion;

/**
 Set enable/disable the skin smooth on face only. If the property is enabled, the detected face will be whitened. The skin smooth on face only is disabled by default.
 */
- (void)enableSkinSmoothFaceOnly:(BOOL)enableSkinSmoothFaceOnly completion:(void (^)(UIImage *image))completion;

/**
 The index of current face for the makeup effect applying. 0: top left. 1: top right. 2: bottom left. 3: bottom right.
 @note this value should always be 0 if MakeupCam:enable4SplitScreen is off.
 */
- (void)currentFaceIndex:(int)index completion:(void (^)(UIImage *image))completion;

/**
 Unavailable. Use `+[PFPhotoMakeup create:completion:]` for `PFPhotoMakeup` object initializing.
 */
- (id)init __attribute__((unavailable("Use +create")));

/**
 Unavailable. Use `+[PFPhotoMakeup create:completion:]` for `PFPhotoMakeup` object initializing.
 */
+ (instancetype)new __attribute__((unavailable("Use +create")));

@end
NS_ASSUME_NONNULL_END
