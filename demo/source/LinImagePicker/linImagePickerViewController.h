//
//  linImagePickerViewController.h
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/20.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol linImagePickerViewControllerDelegate <NSObject>

-(void)doneWithAssets:(NSArray *)assets;

@end

@interface linImagePickerViewController : UIViewController

@property (nonatomic, assign) BOOL preEdit;

@property(nonatomic,weak) id<linImagePickerViewControllerDelegate> delegate;
@end
