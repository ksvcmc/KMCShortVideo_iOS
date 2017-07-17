//
//  NemoFilterCell.h
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol editCollectionCellDelegate <NSObject>

- (void)deleteCell:(UICollectionViewCell*)cell;

@end

@interface editCollectionCell : UICollectionViewCell

@property (nonatomic, weak) id <editCollectionCellDelegate> delegate;

@property (nonatomic, strong) PHAsset * asset;

@end
