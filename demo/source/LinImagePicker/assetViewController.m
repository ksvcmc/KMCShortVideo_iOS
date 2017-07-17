//
//  assetViewController.m
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/22.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "assetViewController.h"
#import "assetCell.h"

@interface assetViewController ()<UICollectionViewDataSource,UICollectionViewDelegate,UICollectionViewDelegateFlowLayout>

@property (nonatomic, strong) UICollectionView* collectionView;
@property (nonatomic, strong) PHCachingImageManager *imageManager;

@end

@implementation assetViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //导入collectionView
    [self loadCollectionView];
}

- (void)viewWillAppear:(BOOL)animated{
    [self.collectionView reloadData];
}

-(void)loadCollectionView{
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    layout.itemSize =CGSizeMake(kScreenSizeWidth/3, kScreenSizeWidth/3);
    layout.minimumInteritemSpacing = 0.0f;
    layout.minimumLineSpacing = 0.0f;
    self.collectionView = [[UICollectionView alloc] initWithFrame:self.view.bounds collectionViewLayout:layout];
    [self.view addSubview:self.collectionView];
    self.collectionView.backgroundColor = [UIColor clearColor];
    [self.collectionView registerClass:[assetCell class] forCellWithReuseIdentifier:@"assetCell"];

    self.collectionView.delegate = self;
    self.collectionView.dataSource = self;
    self.collectionView.allowsMultipleSelection = YES;
    self.collectionView.bounces = NO;
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
#pragma mark UICollectionViewDataSource
- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView
{
    return 1;
}


- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section
{
    return self.fetchResult.count;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath
{
    assetCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"assetCell" forIndexPath:indexPath];
    cell.tag = indexPath.item;
    
    // Image
    PHAsset *asset = self.fetchResult[indexPath.item];
    cell.asset = asset;
    CGSize itemSize = [(UICollectionViewFlowLayout *)collectionView.collectionViewLayout itemSize];
    CGSize targetSize = CGSizeMake(itemSize.width *[[UIScreen mainScreen] scale], itemSize.height*[[UIScreen mainScreen] scale]);
    
    [self.imageManager requestImageForAsset:asset
                                 targetSize:targetSize
                                contentMode:PHImageContentModeAspectFit
                                    options:nil
                              resultHandler:^(UIImage *result, NSDictionary *info) {
                                  if (cell.tag == indexPath.item) {
                                      cell.imageView.image = result;
                                  }
                              }];
    
    // Video indicator
    if (asset.mediaType == PHAssetMediaTypeVideo) {
        cell.videoIndicatorView.hidden = NO;
        
        NSInteger minutes = (NSInteger)(asset.duration / 60.0);
        NSInteger seconds = (NSInteger)ceil(asset.duration - 60.0 * (double)minutes);
        cell.videoIndicatorView.timeLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];
        
        if (asset.mediaSubtypes & PHAssetMediaSubtypeVideoHighFrameRate) {
            cell.videoIndicatorView.videoIcon.hidden = YES;
            cell.videoIndicatorView.slomoIcon.hidden = NO;
        }
        else {
            cell.videoIndicatorView.videoIcon.hidden = NO;
            cell.videoIndicatorView.slomoIcon.hidden = YES;
        }
    } else {
        cell.videoIndicatorView.hidden = YES;
    }
    
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath{
    assetCell *cell = (assetCell *)[collectionView cellForItemAtIndexPath:indexPath];
    
    if(self.delegate){
        [self.delegate itemSelected:cell];
    }
}

- (void)collectionView:(UICollectionView *)collectionView didDeselectItemAtIndexPath:(nonnull NSIndexPath *)indexPath{
    assetCell *cell =  (assetCell *)[collectionView cellForItemAtIndexPath:indexPath];
    
    if(self.delegate){
        [self.delegate itemDeSelected:cell];
    }
}

#pragma mark 懒加载
- (PHCachingImageManager *)imageManager
{
    if (_imageManager == nil) {
        _imageManager = [PHCachingImageManager new];
    }
    
    return _imageManager;
}



@end
