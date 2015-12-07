//
//  ViewController.h
//  HoughApp
//
//  Created by alfa suni on 10/19/15.
//  Copyright © 2015 alfa suni. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@interface ViewController : UIViewController <UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (strong, nonatomic) IBOutlet UIImageView *imageView;
@property BOOL newMedia;

- (IBAction)takePhoto:(UIButton *)sender;
- (IBAction)selectPhoto:(UIButton *)sender;
- (IBAction)processPhoto:(UIButton *)sender;

@end

