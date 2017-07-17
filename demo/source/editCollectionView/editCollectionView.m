//
//  NemoFilterView.m
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import "editCollectionView.h"
#import "editCollectionCell.h"
#import "buttonCollectionCell.h"
#import "editCollectionViewFlowLayout.h"

@interface editCollectionView()<UICollectionViewDataSource,UICollectionViewDelegate,buttonCollectionCellDelegate,editCollectionCellDelegate>{
    
}

@end


@implementation editCollectionView

- (instancetype)init{
    if (self = [super init]) {
        [self initCollectionView];
    }
    return self;
}

- (void)initCollectionView{
    // flow Layout
    editCollectionViewFlowLayout *allFlowLayout = [[editCollectionViewFlowLayout alloc] init];
    allFlowLayout.minimumInteritemSpacing = 0.0f;
    allFlowLayout.minimumLineSpacing = 0.0f;
    allFlowLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
    _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:allFlowLayout];
    _collectionView.showsHorizontalScrollIndicator = NO;
    _collectionView.backgroundColor = [UIColor clearColor];
    _collectionView.allowsMultipleSelection = NO;
    _collectionView.dataSource = self;
    _collectionView.delegate = self;
    _collectionView.scrollsToTop = NO;
    
    [_collectionView registerClass:[editCollectionCell class] forCellWithReuseIdentifier:NSStringFromClass([editCollectionCell class])];
    [_collectionView registerClass:[buttonCollectionCell class] forCellWithReuseIdentifier:NSStringFromClass([buttonCollectionCell class])];
    
    [self addSubview:_collectionView];
    
    [_collectionView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    
    [_collectionView reloadData];
}

#pragma mark - UICollectionViewDataSource

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section{
    return self.assets.count * 2 +1;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath{
    if(indexPath.row % 2 != 0){
        editCollectionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:NSStringFromClass([editCollectionCell class]) forIndexPath:indexPath];
        cell.asset = self.assets[(indexPath.row-1)/2];
        cell.delegate = self;
        return cell;
    }
    
    buttonCollectionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:NSStringFromClass([buttonCollectionCell class]) forIndexPath:indexPath];
    cell.delegate = self;
    return cell;
}

- (CGSize) collectionView:(UICollectionView *)collectionView layout:(nonnull UICollectionViewLayout *)collectionViewLayout sizeForItemAtIndexPath:(nonnull NSIndexPath *)indexPath{
    if(indexPath.row % 2 == 0){
        return CGSizeMake(43, 30);
    }else{
        return CGSizeMake(217+15, 122+15);
    }
}

-(void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath{
    if(indexPath.row % 2 != 0){
        int index = (int)(indexPath.row -1)/2;
        if(self.delegate)
        [self.delegate editAssetClicked:index];
    }
}


#pragma mark -editCollectionCellDelegate
- (void)deleteCell:(UICollectionViewCell*)cell{
    NSIndexPath *indexpath = [self.collectionView indexPathForCell:cell];//获取cell对应的indexpath;
    
    //删除的assetID
    int removeIndex = (int)(indexpath.row-1)/2;
    //删除cell；
    NSMutableArray* muArray = [self.assets mutableCopy];
    [muArray removeObjectAtIndex:removeIndex];
    self.assets = [muArray copy];
    
    [self.collectionView reloadData];
    //告诉上层删除
    if(self.delegate)
        [self.delegate deleteAsset:removeIndex];
}


#pragma mark -buttonCollectionCellDelegate
- (void)addAssetClicked:(UICollectionViewCell *)cell{
    NSIndexPath *indexpath = [self.collectionView indexPathForCell:cell];//获取cell对应的indexpath;
    int insertIndex = (int)indexpath.row/2;
    if(self.delegate)
        [self.delegate addAssetClicked:insertIndex];
}
@end
