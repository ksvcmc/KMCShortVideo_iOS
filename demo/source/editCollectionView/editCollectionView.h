//
//  NemoFilterView.h
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <KMCShortVideo/KMCMaterial.h>

@protocol editCollectionViewDelegate <NSObject>

- (void)addAssetClicked:(NSInteger)insertIndex;
- (void)editAssetClicked:(NSInteger)index;

- (void)deleteAsset:(int)index;

@end

@interface editCollectionView : UIView

@property (nonatomic, strong) UICollectionView * collectionView;

@property(strong,nonatomic) NSArray * assets;

@property(nonatomic,weak) id<editCollectionViewDelegate> delegate;

@end
