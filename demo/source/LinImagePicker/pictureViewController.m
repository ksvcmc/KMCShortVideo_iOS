//
//  pictureViewController.m
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/22.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "pictureViewController.h"

@interface pictureViewController ()

@end

@implementation pictureViewController

- (void)viewDidLoad {
    PHFetchOptions *options = [PHFetchOptions new];
    options.predicate = [NSPredicate predicateWithFormat:@"mediaType == %ld", PHAssetMediaTypeImage];
    
    self.fetchResult = [PHAsset fetchAssetsInAssetCollection:self.assetCollection options:options];
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
