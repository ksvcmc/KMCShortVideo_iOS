//
//  linImagePickerViewController.m
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/20.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "linImagePickerViewController.h"
#import "allContextViewController.h"
#import "videoViewController.h"
#import "pictureViewController.h"
#import "videoEditController.h"

#define ButtonCount 3
//pageview

@interface linImagePickerViewController()<UIScrollViewDelegate,assetViewControllerDelegate>{
    
}

@property (nonatomic, strong)UIScrollView *scroll;
@property (nonatomic, strong)UIButton * selectedButton;
@property (nonatomic, assign)NSInteger currentPages;
@property (nonatomic, strong)UIView *PageView;
@property (nonatomic, strong)UIView *pageLine;

@property (nonatomic, strong)allContextViewController * allVC;
@property (nonatomic, strong)videoViewController *videoVC;
@property (nonatomic, strong)pictureViewController *picVC;

@property (nonatomic, strong) UIButton * startButton;
@property (nonatomic, strong) NSMutableOrderedSet * selectedArray;

@property (nonatomic, strong) PHAssetCollection *assetCollection;

@end

@implementation linImagePickerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //导航栏
    [self setupNavigation];
    //设置分页view
    [self setupPageView];
    //设置可以左右滑动的ScrollView
    [self setupScrollView];
    //相册对象
    [self updateAssetCollections];
    //设置控制的每一个子控制器
    [self setupChildViewControll];
    //开始按钮
    [self setupStartButton];
    //选择数组
    self.selectedArray = [[NSMutableOrderedSet alloc] init];
}

#pragma mark -UI
-(void)setupNavigation{
    self.navigationItem.title = @"选择内容";
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"back"] style:UIBarButtonItemStylePlain target:self action:@selector(back) ];
    self.navigationController.navigationBar.titleTextAttributes = @{NSForegroundColorAttributeName:[UIColor colorWithHexString:@"#FFFFFF"]};
    self.navigationController.navigationBar.translucent = NO;
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#0E0F1A"];
}

-(void)setupPageView{
    self.PageView = [[UIView alloc]init];
    //第一个按钮
    UIButton *btn0 = [self setupButtonWithTitle:@"全部内容" Index:0];
    //第二个按钮
    UIButton *btn1 = [self setupButtonWithTitle:@"视频" Index:1];
    //第三个按钮
    UIButton *btn2 = [self setupButtonWithTitle:@"图片" Index:2];
    //红线
    _pageLine = [[UIView alloc]init];
    _pageLine.backgroundColor = [UIColor colorWithHexString:@"#9012fe"];
    //分割线
    UIView* line = [[UIView alloc]init];
    [line setBackgroundColor:[UIColor colorWithHexString:@"#444344"]];

    [self.view addSubview:self.PageView];
    [self.PageView addSubview:btn0];
    [self.PageView addSubview:btn1];
    [self.PageView addSubview:btn2];
    [self.PageView addSubview:_pageLine];
    [self.PageView addSubview:line];

    [self.PageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.leading.trailing.equalTo(self.view);
        make.height.mas_equalTo(PageViewHeight);
    }];
    
    [btn0 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.leading.equalTo(self.PageView);
        make.height.mas_equalTo(22);
        make.width.equalTo(self.PageView.mas_width).multipliedBy(1.0/ButtonCount);
    }];
    [btn1 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView);
        make.leading.equalTo(btn0.mas_trailing);
        make.height.mas_equalTo(22);
        make.width.equalTo(self.PageView.mas_width).multipliedBy(1.0/ButtonCount);
    }];
    [btn2 mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView);
        make.leading.equalTo(btn1.mas_trailing);
        make.height.mas_equalTo(22);
        make.width.equalTo(self.PageView.mas_width).multipliedBy(1.0/ButtonCount);
    }];
    [_pageLine mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(btn0.mas_bottom).offset(9);
        make.centerX.equalTo(btn0.mas_centerX);
        make.height.mas_equalTo(4);
        make.width.mas_equalTo(33);
    }];
    [line mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(_pageLine.mas_bottom);
        make.leading.trailing.equalTo(self.PageView);
        make.height.mas_equalTo(1);
    }];
    
    self.selectedButton = btn0;
}

- (void)setupScrollView{
    self.scroll = [[UIScrollView alloc]init];
    _scroll.pagingEnabled = YES;
    _scroll.delegate = self;
    _scroll.showsVerticalScrollIndicator = NO;
    _scroll.scrollEnabled = NO;
    //方向锁
    _scroll.directionalLockEnabled = YES;
    //取消自动布局
    self.automaticallyAdjustsScrollViewInsets = YES;
    _scroll.contentSize = CGSizeMake(kScreenSizeWidth * ButtonCount, kScreenSizeHeight);
    
    [self.view addSubview:_scroll];
    
    [self.scroll mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView.mas_bottom);
        make.leading.trailing.bottom.equalTo(self.view);
    }];
}

- (void)setupChildViewControll{
    self.allVC = [[allContextViewController alloc]init];
    self.allVC.assetCollection = self.assetCollection;
    self.allVC.delegate = self;
    
    self.videoVC = [[videoViewController alloc]init];
    self.videoVC.assetCollection = self.assetCollection;
    self.videoVC.delegate = self;

    self.picVC = [[pictureViewController alloc]init];
    self.picVC.assetCollection = self.assetCollection;
    self.picVC.delegate = self;

    //指定该控制器为其子控制器
    [self addChildViewController:self.allVC];
    [self addChildViewController:self.videoVC];
    [self addChildViewController:self.picVC];
    
    //将视图加入ScrollView上
    [_scroll addSubview:self.allVC.view];
    [_scroll addSubview:self.videoVC.view];
    [_scroll addSubview:self.picVC.view];

    self.picVC.view.frame = CGRectMake(2*kScreenSizeWidth, 0, kScreenSizeWidth, kScreenSizeHeight - 64-PageViewHeight);
    self.videoVC.view.frame = CGRectMake(kScreenSizeWidth, 0, kScreenSizeWidth, kScreenSizeHeight - 64-PageViewHeight);
    self.allVC.view.frame = CGRectMake(0, 0, kScreenSizeWidth, kScreenSizeHeight - 64-PageViewHeight);
}

- (UIButton *)setupButtonWithTitle:(NSString *)title Index:(NSInteger)index{
    UIButton *btn = [[UIButton alloc]init];
    [btn setTitle:title forState:(UIControlStateNormal)];
    [btn setTitleColor:[UIColor colorWithHexString:@"#9b9b9b"] forState:(UIControlStateNormal)];

    btn.titleLabel.font = [UIFont systemFontOfSize:14];

    btn.tag = index + kTag;
    
    [btn addTarget:self action:@selector(pageClick:) forControlEvents:(UIControlEventTouchUpInside)];
    return btn;
}

#pragma mark -action
-(void)back{
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)pageClick:(UIButton *)btn{
    self.selectedButton = btn;
    self.currentPages = btn.tag - kTag;
    //滚动到特定页
    CGRect frame;
    frame.origin.x = self.scroll.frame.size.width * self.currentPages;
    frame.origin.y = 0;
    frame.size = _scroll.frame.size;
    [_scroll scrollRectToVisible:frame animated:YES];
}

-(void)setupStartButton{
    self.startButton = [[UIButton alloc]initWithFrame:CGRectMake(0,kScreenSizeHeight-44-64, kScreenSizeWidth, 44)];
    [self.startButton setTitle:@"开始制作视频" forState:(UIControlStateNormal)];
    [self.startButton setTitleColor:[UIColor colorWithHexString:@"#ffffff"] forState:(UIControlStateNormal)];
    self.startButton.titleLabel.font = [UIFont systemFontOfSize:18];
    [self.startButton addTarget:self action:@selector(done) forControlEvents:(UIControlEventTouchUpInside)];
    self.startButton.backgroundColor = [UIColor colorWithHexString:@"440977"];
    
    [self.view addSubview:self.startButton];
}

-(void)done{
    
    NSMutableArray * assets = [[NSMutableArray alloc] init];
    for(int i = 0;i< self.selectedArray.count ;i++){
        assetCell * cell = self.selectedArray[i];
        [assets insertObject:cell.asset atIndex:i];
    }
    if(self.delegate){
        [self.delegate doneWithAssets:[assets copy]];
    }
    
    if(self.preEdit){
        videoEditController * editVC = [[videoEditController alloc]init];
        editVC.assets = [assets copy];
        [self.navigationController pushViewController:editVC animated:YES];
    }else{
        [self dismissViewControllerAnimated:YES completion:Nil];
    }
    
    
}

-(void)setSelectedButton:(UIButton *)selectedButton{
    if(_selectedButton == selectedButton)
        return;
    //设置button选中颜色
    [selectedButton setTitleColor:[UIColor colorWithHexString:@"#ffffff"] forState:(UIControlStateNormal)];
    if(_selectedButton){
        [_selectedButton setTitleColor:[UIColor colorWithHexString:@"#9b9b9b"] forState:(UIControlStateNormal)];
    }
    _selectedButton = selectedButton;
    //设置pageline的位置
    self.pageLine.center = CGPointMake(_selectedButton.center.x, CGRectGetMaxY(_selectedButton.frame)+9);

}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - ScrollView delegate
- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    CGFloat pageWidth = _scroll.frame.size.width;
    self.currentPages = floor((_scroll.contentOffset.x - pageWidth/2)/pageWidth) + 1;
    
    //设置选中button的样式
    self.selectedButton = (UIButton *)[self.view viewWithTag:self.currentPages+kTag];
}

#pragma mark - AssetCollections

- (void)updateAssetCollections{
    //获取所有相册资源
    PHFetchResult * fetchResult= [PHAssetCollection fetchAssetCollectionsWithType:PHAssetCollectionTypeSmartAlbum subtype:PHAssetCollectionSubtypeAny options:nil];
    NSArray * fetchResults = @[fetchResult];
    NSArray *assetCollectionSubtypes = @[
                                         @(PHAssetCollectionSubtypeSmartAlbumUserLibrary)
                                         ];
    NSMutableDictionary *smartAlbums = [NSMutableDictionary dictionaryWithCapacity:assetCollectionSubtypes.count];
    for (PHFetchResult *fetchResult in fetchResults) {
        [fetchResult enumerateObjectsUsingBlock:^(PHAssetCollection *assetCollection, NSUInteger index, BOOL *stop) {
            PHAssetCollectionSubtype subtype = assetCollection.assetCollectionSubtype;
            
            if ([assetCollectionSubtypes containsObject:@(subtype)]) {
                if (!smartAlbums[@(subtype)]) {
                    smartAlbums[@(subtype)] = [NSMutableArray array];
                }
                [smartAlbums[@(subtype)] addObject:assetCollection];
            }
        }];
    }
    
    NSMutableArray *assetCollections = [NSMutableArray array];
    for (NSNumber *assetCollectionSubtype in assetCollectionSubtypes) {
        NSArray *collections = smartAlbums[assetCollectionSubtype];
        
        if (collections) {
            [assetCollections addObjectsFromArray:collections];
        }
    }
    
    if(assetCollections.count > 0)
        self.assetCollection = assetCollections[0];
}

#pragma mark -assetViewControllerDelegate
- (void)itemSelected:(assetCell *)cell{
    [self.selectedArray addObject:cell];
    [self.startButton setTitle:[NSString stringWithFormat:@"开始制作视频(%lu)",(unsigned long)self.self.selectedArray.count] forState:(UIControlStateNormal)];
    
    cell.clickNumLabel.text = [NSString stringWithFormat:@"%lu",(unsigned long)self.selectedArray.count];
}

- (void)itemDeSelected:(assetCell *)cell{
    [self.selectedArray removeObject:cell];
    for (int i =0;i < self.selectedArray.count;i++) {
        assetCell * clickCell = self.selectedArray[i];
        clickCell.clickNumLabel.text = [NSString stringWithFormat:@"%d",i+1];
    }
    cell.clickNumLabel.text = @"";

    if(self.selectedArray.count > 0){
        [self.startButton setTitle:[NSString stringWithFormat:@"开始制作视频(%lu)",(unsigned long)self.selectedArray.count] forState:(UIControlStateNormal)];
    }else{
        [self.startButton setTitle:[NSString stringWithFormat:@"开始制作视频"] forState:(UIControlStateNormal)];

    }
    
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
