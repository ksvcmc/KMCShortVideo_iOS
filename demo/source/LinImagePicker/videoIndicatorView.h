//
//  QBVideoIndicatorView.h
//  QBImagePicker
//
//  Created by Katsuma Tanaka on 2015/04/04.
//  Copyright (c) 2015 Katsuma Tanaka. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "videoIconView.h"
#import "slomoIconView.h"

@interface videoIndicatorView : UIView

@property (nonatomic, strong) UILabel *timeLabel;
@property (nonatomic, strong) videoIconView *videoIcon;
@property (nonatomic, strong) slomoIconView *slomoIcon;


@end
