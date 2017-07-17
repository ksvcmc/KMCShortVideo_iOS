//
//  QBSlomoIconView.m
//  QBImagePicker
//
//  Created by Julien Chaumond on 22/04/2015.
//  Copyright (c) 2015 Katsuma Tanaka. All rights reserved.
//

#import "slomoIconView.h"

@implementation slomoIconView

- (instancetype)init
{
    self = [super init];
    
    // Set default values
    self.iconColor = [UIColor whiteColor];
    return self;
}

- (void)drawRect:(CGRect)rect
{
    [self.iconColor setStroke];
    
    CGFloat width = 2.2;
    CGRect insetRect = CGRectInset(rect, width / 2, width / 2);
    
    // Draw dashed circle
    UIBezierPath* circlePath = [UIBezierPath bezierPathWithOvalInRect:insetRect];
    circlePath.lineWidth = width;
    CGFloat ovalPattern[] = {0.75, 0.75};
    [circlePath setLineDash:ovalPattern count:2 phase:0];
    [circlePath stroke];
}

@end
