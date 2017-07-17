//
//  NemoFilterView.m
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import "linCollectionView.h"
#import "linCollectionCell.h"
#import <KMCShortVideo/KMCMaterial.h>

#define kEffectNum  7

@interface linCollectionView()<UICollectionViewDataSource,UICollectionViewDelegate>{
    
}
@property (nonatomic, strong) NSMutableDictionary *cellDic;


@end


@implementation linCollectionView

- (instancetype)init{
    if (self = [super init]) {
        self.materials = [[NSMutableArray alloc] initWithCapacity:100];
        [self initCollectionView];
        self.cellDic = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)initCollectionView{
    // flow Layout
    UICollectionViewFlowLayout *allFlowLayout = [[UICollectionViewFlowLayout alloc] init];
    allFlowLayout.itemSize = CGSizeMake(63, 91);
    allFlowLayout.minimumInteritemSpacing = 5.0f;
    allFlowLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
    _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:allFlowLayout];
    _collectionView.showsHorizontalScrollIndicator = NO;
    _collectionView.backgroundColor = [UIColor clearColor];
    _collectionView.allowsMultipleSelection = NO;
    _collectionView.dataSource = self;
    _collectionView.delegate = self;
    _collectionView.scrollsToTop = NO;
    [self addSubview:_collectionView];
    
    [_collectionView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self);
    }];
    
    [_collectionView reloadData];
}

#pragma mark - UICollectionViewDataSource

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section{
    return self.materials.count+1;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath{
    // 每次先从字典中根据IndexPath取出唯一标识符
    NSString *identifier = [_cellDic objectForKey:[NSString stringWithFormat:@"%@", indexPath]];
    // 如果取出的唯一标示符不存在，则初始化唯一标示符，并将其存入字典中，对应唯一标示符注册Cell
    if (identifier == nil) {
        identifier = [NSString stringWithFormat:@"collectionCell%@", [NSString stringWithFormat:@"%@", indexPath]];
        [_cellDic setValue:identifier forKey:[NSString stringWithFormat:@"%@", indexPath]];
        // 注册Cell
        [self.collectionView registerClass:[linCollectionCell class] forCellWithReuseIdentifier:identifier];

    }
    
    linCollectionCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:identifier forIndexPath:indexPath];

    if(indexPath.row > 0)
        cell.material = _materials[indexPath.row -1];
    else
        cell.material = nil;
    
    return cell;
}

#pragma mark - UICollectionViewDelegate
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath{
    linCollectionCell * cell = (linCollectionCell *)[collectionView cellForItemAtIndexPath:indexPath];
    
    //关闭
    if(cell.material == nil){
        if(self.delegate){
            KMCMaterial * material = [[KMCMaterial alloc] init];
            material.strType = self.strType;
            [self.delegate removeMeterial:material];
        }
        return;
    }
    //下载文件
    if(![self isMaterialDownloaded:cell.material.strName]){
        [cell startDownload];
        if(self.delegate){
            [self.delegate downloadMeterial:cell.material onSuccess:^{
                [cell finishDownload];
                [self.delegate applyMeterial:cell.material];
            } onFailure:^(int iErrorCode, NSString *strMessage) {
                [cell downloadFail];
            } onProgress:^(float fProgress, int64_t iSize) {
                [cell downloading:fProgress];
            }];
        }
    }else{
    //直接应用
        if(self.delegate){
            [self.delegate applyMeterial:cell.material];
        }
    }
    cell.selectedMaskView.hidden=NO;
}



#pragma mark - utility
- (BOOL)isMaterialDownloaded:(NSString *)strName{
    NSString *ourDocumentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,  NSUserDomainMask,YES) objectAtIndex:0];
    NSString *FilePath=[ourDocumentPath stringByAppendingPathComponent:strName];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL result = [fileManager fileExistsAtPath:FilePath];
    return result;
}
@end
