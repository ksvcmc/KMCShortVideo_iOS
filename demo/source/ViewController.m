//
//  ViewController.m
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/14.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "ViewController.h"
#import "videoEditController.h"
#import "linImagePickerViewController.h"
#import <KMCShortVideo/KMCShortVideo.h>

@interface ViewController ()
    
@property (weak, nonatomic) IBOutlet UIButton *addButton;
    
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    
    [KMCShortVideo authorizeWithTokeID:@"cd1b62c91553e61ea729b78a3a656f29" onSuccess:^{
        NSLog(@"鉴权成功");
    } onFailure:^(AuthorizeError iErrorCode) {
        if(iErrorCode != 1005 && iErrorCode != 0)
        {
            NSString * errorMessage = [[NSString alloc]initWithFormat:@"鉴权失败，错误码:%lu",(unsigned long)iErrorCode];
            dispatch_async(dispatch_get_main_queue(), ^{
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"错误提示" message:errorMessage delegate:nil cancelButtonTitle:@"好的" otherButtonTitles:nil, nil];
                [alert show];
            });
        }
        NSLog(@"鉴权失败，错误码:%lu",(unsigned long)iErrorCode);
    }];
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
#pragma mark - action
- (IBAction)addVideo:(id)sender {
    linImagePickerViewController* imagePicker = [[linImagePickerViewController alloc]init];
    imagePicker.preEdit = YES;
    UINavigationController* navigation = [[UINavigationController alloc] initWithRootViewController:imagePicker];
    [self presentViewController:navigation animated:YES completion:nil];
    
}



@end
