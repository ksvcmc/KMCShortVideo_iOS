//
//  videoEditController.m
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/6/14.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "videoEditController.h"
#import <KMCShortVideo/KMCShortVideo.h>
#import <Photos/Photos.h>
#import "Masonry.h"
#import "linCollectionView.h"
#import "editCollectionView.h"
#import "singleVideoEditViewController.h"
#import "singleImageEditViewController.h"
#import "linImagePickerViewController.h"
#import <AssetsLibrary/AssetsLibrary.h>

@interface videoEditController()<linCollectionViewDelegate,UITextFieldDelegate,editCollectionViewDelegate,linImagePickerViewControllerDelegate,singleVideoEditViewControllerDelegate,singleImageEditViewControllerDelegate,KMCShortVideoDelegate>{
    NSTimer *_playbackProgressTimer;
}
@property (nonatomic,strong) NvsLiveWindow* liveWindow;
@property (nonatomic,strong) KMCShortVideo* kmcShortVideo;

@property (nonatomic,strong) UIView * PlayerBgView;
@property (nonatomic,strong) UIView * controlView;
@property (nonatomic,strong) UIButton * playButton;
@property (nonatomic,strong) UILabel * currentLabel;
@property (nonatomic,strong) UISlider * slider;
@property (nonatomic,strong) UILabel * durationLabel;
@property (nonatomic, strong)UITextField * themeTextField;
//视频特效页
@property (nonatomic,strong) UIView * PageView;
@property (nonatomic,strong) UIButton * themeButton;
@property (nonatomic,strong) UIButton * musicButton;
@property (nonatomic,strong) UIButton * filterButton;
@property (nonatomic,strong) UIButton * editButton;
@property (nonatomic, strong)UIView *pageLine;
@property (nonatomic, strong)UIButton * selectedButton;
@property (nonatomic, assign)NSInteger insertIndex;
@property (nonatomic, strong)linCollectionView * themeView;
@property (nonatomic, strong)linCollectionView * musicView;
@property (nonatomic, strong)linCollectionView * filterView;
@property (nonatomic, strong)editCollectionView * editView;
//保存
@property (nonatomic,strong) UIButton * saveButton;


@end

@implementation videoEditController
    
-(void)viewDidLoad{
    [super viewDidLoad];
    [self setupUI];
    [self setupShortVideo];
    
}

-(void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
    //显示第一帧
    [self changeDurationLabelValue:_kmcShortVideo.duration];
    [_kmcShortVideo seek:self.slider.value * _kmcShortVideo.duration];

}
#pragma mark - UI
-(void)setupUI{
    self.view.backgroundColor = [UIColor blackColor];

    [self setupNavigation];
    //播放器
    [self setupPlayerView];
    //视频选择页
    [self setupChooseView];
}

-(void)setupNavigation{
    self.navigationItem.title = @"视频编辑";
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"back"] style:UIBarButtonItemStylePlain target:self action:@selector(back) ];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"edit"] style:UIBarButtonItemStylePlain target:self action:@selector(editThemeTitle) ];
    self.navigationController.navigationBar.titleTextAttributes = @{NSForegroundColorAttributeName:[UIColor colorWithHexString:@"#FFFFFF"]};
    self.navigationController.navigationBar.translucent = NO;
    self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#0E0F1A"];
}
-(void)setupPlayerView{
    self.PlayerBgView = [[UIView alloc]init];
    //视图
    self.liveWindow = [[NvsLiveWindow alloc]init];
    //控制栏
    self.controlView = [[UIView alloc] init];
    //播放按钮
    self.playButton = [[UIButton alloc]init];
    [self.playButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
    [self.playButton addTarget:self action:@selector(play) forControlEvents:(UIControlEventTouchUpInside)];
    //当前播放时间
    self.currentLabel = [[UILabel alloc] init];
    self.currentLabel.text = @"00:00";
    self.currentLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.currentLabel.font = [UIFont systemFontOfSize:14];
    //进度条
    self.slider = [[UISlider alloc] init];
    self.slider.minimumValue = 0.0f;
    self.slider.maximumValue = 1.0f;
    self.slider.value = 0.0f;
    self.slider.tintColor = [UIColor colorWithHexString:@"#9012FE"];
    [self.slider addTarget:self action:@selector(sliderStrengthValueChanged) forControlEvents:(UIControlEventValueChanged)];
    //文件播放总时长
    self.durationLabel = [[UILabel alloc] init];
    NSInteger minutes = (NSInteger)(_kmcShortVideo.duration / 60.0);
    NSInteger seconds = (NSInteger)(_kmcShortVideo.duration - 60.0 * (double)minutes);
    self.durationLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];
    self.durationLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.durationLabel.font = [UIFont systemFontOfSize:14];
    //主题编辑框
    self.themeTextField = [[UITextField alloc]init];
    self.themeTextField.backgroundColor = [UIColor whiteColor];
    self.themeTextField.alpha = 0.5f;
    self.themeTextField.textColor = [UIColor colorWithString:@"#0E0F1A"];
    self.themeTextField.font = [UIFont systemFontOfSize:16];
    self.themeTextField.delegate = self;
    self.themeTextField.hidden = YES;

    [self.view addSubview:self.PlayerBgView];
    [self.PlayerBgView addSubview:self.liveWindow];
    [self.PlayerBgView addSubview:self.controlView];
    [self.PlayerBgView addSubview:self.themeTextField];
    [self.controlView addSubview:self.playButton];
    [self.controlView addSubview:self.currentLabel];
    [self.controlView addSubview:self.slider];
    [self.controlView addSubview:self.durationLabel];

    [self.PlayerBgView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.trailing.equalTo(self.view);
        make.top.equalTo(self.view);
        make.height.mas_equalTo(kPlaerBgViewHeight);
    }];
    [self.liveWindow mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.trailing.equalTo(self.PlayerBgView);
        make.top.equalTo(self.PlayerBgView).offset(17);
        make.height.mas_equalTo(kPlaerViewHeight);
    }];
    [self.themeTextField mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.trailing.equalTo(self.PlayerBgView);
        make.top.equalTo(self.PlayerBgView).offset(83);
        make.height.mas_equalTo(45);
    }];
    [self.controlView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.trailing.equalTo(self.PlayerBgView);
        make.top.equalTo(self.liveWindow.mas_bottom);
        make.height.mas_equalTo(kControlViewHeight);
    }];
    [self.playButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.equalTo(self.controlView).offset(8);
        make.top.bottom.equalTo(self.controlView);
        make.width.mas_equalTo(40);
    }];
    [self.currentLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.equalTo(self.playButton.mas_trailing);
        make.centerY.equalTo(self.controlView);
    }];
    [self.slider mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.controlView);
        make.leading.equalTo(self.currentLabel.mas_trailing).offset(12);
        make.trailing.equalTo(self.durationLabel.mas_leading).offset(-12);
    }];
    [self.durationLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.controlView);
        make.trailing.equalTo(self.PlayerBgView.mas_trailing).offset(-18);
    }];
   
}

-(void)setupChooseView{
    self.PageView = [[UIView alloc]init];
    //选择按钮
    self.themeButton = [self setupButtonWithTitle:@"主题" Index:0];
    self.musicButton = [self setupButtonWithTitle:@"音乐" Index:1];
    self.filterButton= [self setupButtonWithTitle:@"滤镜" Index:2];
    self.editButton  = [self setupButtonWithTitle:@"编辑" Index:3];
    //红线
    _pageLine = [[UIView alloc]init];
    _pageLine.backgroundColor = [UIColor colorWithHexString:@"#9012fe"];
    //主题选择页
    self.themeView = [[linCollectionView alloc] init];
    self.themeView.delegate = self;
    self.themeView.strType = @"0";
    //音乐选择器
    self.musicView = [[linCollectionView alloc] init];
    self.musicView.delegate = self;
    self.musicView.strType = @"1";
    //滤镜选择页
    self.filterView = [[linCollectionView alloc] init];
    self.filterView.delegate = self;
    self.filterView.strType = @"2";
    //编辑选择页
    self.editView = [[editCollectionView alloc]init];
    self.editView.assets = [self.assets copy];
    self.editView.delegate = self;
    //保存按钮
    self.saveButton = [[UIButton alloc] init];
    [self.saveButton setTitle:@"保存" forState:(UIControlStateNormal)];
    [self.saveButton setTitleColor:[UIColor colorWithHexString:@"#ffffff"] forState:(UIControlStateNormal)];
    self.saveButton.titleLabel.font = [UIFont systemFontOfSize:18];
    [self.saveButton addTarget:self action:@selector(startCompile:) forControlEvents:(UIControlEventTouchUpInside)];
    self.saveButton.backgroundColor = [UIColor colorWithHexString:@"440977"];
    
    
    [self.view addSubview:self.PageView];
    [self.PageView addSubview:self.themeButton];
    [self.PageView addSubview:self.musicButton];
    [self.PageView addSubview:self.filterButton];
    [self.PageView addSubview:self.editButton];
    [self.PageView addSubview:self.pageLine];
    [self.PageView addSubview:self.themeView];
    [self.PageView addSubview:self.musicView];
    [self.PageView addSubview:self.filterView];
    [self.PageView addSubview:self.editView];
    [self.PageView addSubview:self.saveButton];


    
    [self.PageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.controlView.mas_bottom);
        make.bottom.leading.trailing.equalTo(self.view);
    }];
    [self.themeButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView).offset(33);
        make.leading.equalTo(self.PageView).offset(58);
        make.height.mas_equalTo(19.5);
        make.width.mas_equalTo(34);
    }];
    [self.musicButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView).offset(33);
        make.leading.equalTo(self.themeButton.mas_trailing).offset(41);
        make.height.mas_equalTo(19.5);
        make.width.mas_equalTo(34);
    }];
    [self.filterButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView).offset(33);
        make.leading.equalTo(self.musicButton.mas_trailing).offset(41);
        make.height.mas_equalTo(19.5);
        make.width.mas_equalTo(34);
    }];
    [self.editButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.PageView).offset(33);
        make.leading.equalTo(self.filterButton.mas_trailing).offset(41);
        make.height.mas_equalTo(19.5);
        make.width.mas_equalTo(34);
    }];
    [self.pageLine mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.themeButton.mas_bottom).offset(7);
        make.centerX.equalTo(self.themeButton.mas_centerX);
        make.height.mas_equalTo(4);
        make.width.mas_equalTo(33);
    }];
    
    [self.themeView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.pageLine.mas_bottom).offset(64);
        make.leading.equalTo(self.PageView).offset(20);
        make.height.mas_equalTo(91);
        make.width.mas_equalTo(kScreenSizeWidth-20);
    }];
    
    [self.filterView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.pageLine.mas_bottom).offset(64);
        make.leading.equalTo(self.PageView).offset(20);
        make.height.mas_equalTo(91);
        make.width.mas_equalTo(kScreenSizeWidth-20);
    }];
    [self.musicView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.pageLine.mas_bottom).offset(64);
        make.leading.equalTo(self.PageView).offset(20);
        make.height.mas_equalTo(91);
        make.width.mas_equalTo(kScreenSizeWidth-20);
    }];
    [self.editView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.pageLine.mas_bottom).offset(48);
        make.leading.equalTo(self.PageView);
        make.height.mas_equalTo(122+15);
        make.width.mas_equalTo(kScreenSizeWidth);
    }];
    [self.saveButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.height.mas_equalTo(49);
        make.leading.trailing.bottom.equalTo(self.PageView);
    }];
    
    self.selectedButton = self.themeButton;
}


- (UIButton *)setupButtonWithTitle:(NSString *)title Index:(NSInteger)index{
    UIButton *btn = [[UIButton alloc]init];
    [btn setTitle:title forState:(UIControlStateNormal)];
    [btn setTitleColor:[UIColor colorWithHexString:@"#9b9b9b"] forState:(UIControlStateNormal)];
    
    btn.tag = index +kTag;
    btn.titleLabel.font = [UIFont systemFontOfSize:16];
    
    [btn addTarget:self action:@selector(pageClick:) forControlEvents:(UIControlEventTouchUpInside)];

    return btn;
}


#pragma mark - action
-(void)editThemeTitle{
    self.themeTextField.hidden = NO;
}

- (void)sliderStrengthValueChanged {
    [_kmcShortVideo seek:self.slider.value * _kmcShortVideo.duration];
    if(_playbackProgressTimer){
        [_playbackProgressTimer invalidate];
    }
    [self.playButton setImage:[UIImage imageNamed:@"pause"] forState:UIControlStateNormal];
    [_kmcShortVideo playFrom:self.slider.value * _kmcShortVideo.duration To:_kmcShortVideo.duration];
    NSTimeInterval timeInterval = 0.1;
    _playbackProgressTimer = [NSTimer scheduledTimerWithTimeInterval:timeInterval
                                                              target:self
                                                            selector:@selector(handleProgressTimer:)
                                                            userInfo:nil
                                                             repeats:YES];
}

- (void)pageClick:(UIButton *)btn{
    self.selectedButton = btn;
}

- (void)handleProgressTimer:(NSTimer *)timer {
    self.slider.value = self.slider.maximumValue * _kmcShortVideo.curPosition / _kmcShortVideo.duration;
    
    [self changeCurrentLabelValue:self.slider.maximumValue * _kmcShortVideo.curPosition];
    [self changeDurationLabelValue:_kmcShortVideo.duration];
}
-(void)back{
    [_kmcShortVideo stopPlay];
    [self dismissViewControllerAnimated:YES completion:nil];
}
- (void)play{
    if(_playbackProgressTimer){
        [_playbackProgressTimer invalidate];
    }
    if([_kmcShortVideo state] == NvsStreamingEngineState_Playback){
        [_kmcShortVideo stopPlay];
        [self.playButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
        return;
    }
    [self.playButton setImage:[UIImage imageNamed:@"pause"] forState:UIControlStateNormal];
    [_kmcShortVideo playFrom:self.slider.value * _kmcShortVideo.duration To:_kmcShortVideo.duration];
    NSTimeInterval timeInterval = 0.1;
    _playbackProgressTimer = [NSTimer scheduledTimerWithTimeInterval:timeInterval
                                                              target:self
                                                            selector:@selector(handleProgressTimer:)
                                                            userInfo:nil
                                                             repeats:YES];
}

-(void)changeCurrentLabelValue:(float)time{
    //当前时间
    NSInteger minutes = (NSInteger)(time / 60.0);
    NSInteger seconds = (NSInteger)(time - 60.0 * (double)minutes);
    self.currentLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];
}

-(void)changeDurationLabelValue:(float)time{
    //总时长
    NSInteger minutes = (NSInteger)(time / 60.0);
    NSInteger seconds = (NSInteger)(time - 60.0 * (double)minutes);
    self.durationLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];

}
#pragma mark - shortVideoRelate

-(void)setupShortVideo{
    //初始化sdk
    _kmcShortVideo = [[KMCShortVideo alloc] init];
    //鉴权
    
    //初始化窗口
    NvsVideoResolution videoEditRes;
    videoEditRes.imageWidth = 1280;
    videoEditRes.imageHeight = 720;
    videoEditRes.imagePAR = (NvsRational){1, 1};
    NvsRational videoFps = {25, 1};
    NvsAudioResolution audioEditRes;
    audioEditRes.sampleRate = 48000;
    audioEditRes.channelCount = 2;
    audioEditRes.sampleFormat = NvsAudSmpFmt_S16;
    [_kmcShortVideo configWithWindow:self.liveWindow videoResolution:&videoEditRes videoFps:&videoFps audioResolution:&audioEditRes];
    
    _kmcShortVideo.delegate = self;
    //往sdk里面添加视频片段
    for (int i = 0; i<self.assets.count; i++) {
        [_kmcShortVideo insertVideoClip:self.assets[i] atIndex:i];
    }
    //获取主题资源列表
    __weak __typeof(self) weakSelf = self;
    [self.kmcShortVideo fetchThemeMaterialsWithType:Type_Theme
                                          OnSuccess:^(NSArray * materialArray) {
                                              for(int i = 0; i < [materialArray count]; i++)
                                              {
                                                  [weakSelf.themeView.materials addObject:[materialArray objectAtIndex:i]];
                                              }
                                              [weakSelf.themeView.collectionView reloadData];
                                          } onFailure:nil];
    
    //获取音乐资源列表
    [self.kmcShortVideo fetchThemeMaterialsWithType:Type_Music
                                          OnSuccess:^(NSArray * materialArray) {
                                              for(int i = 0; i < [materialArray count]; i++)
                                              {
                                                  [weakSelf.musicView.materials addObject:[materialArray objectAtIndex:i]];
                                              }
                                              [weakSelf.musicView.collectionView reloadData];
                                          } onFailure:nil];
    
    //获取滤镜资源列表
    [self.kmcShortVideo fetchThemeMaterialsWithType:Type_Filter
                                          OnSuccess:^(NSArray * materialArray) {
                                              for(int i = 0; i < [materialArray count]; i++)
                                              {
                                                  [weakSelf.filterView.materials addObject:[materialArray objectAtIndex:i]];
                                              }
                                              [weakSelf.filterView.collectionView reloadData];
                                          } onFailure:nil];
   
    [self.kmcShortVideo setThemeTitleCaptionText:@"金山魔方"];
   
}

#pragma mark - 懒加载

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
    self.pageLine.center = CGPointMake(_selectedButton.center.x, CGRectGetMaxY(_selectedButton.frame)+7);
    //设置view的隐藏和开启
    if(self.selectedButton == self.themeButton){
        self.themeView.hidden = NO;
        self.musicView.hidden = YES;
        self.filterView.hidden = YES;
        self.editView.hidden = YES;
    }else if(self.selectedButton == self.musicButton){
        self.themeView.hidden = YES;
        self.musicView.hidden = NO;
        self.filterView.hidden = YES;
        self.editView.hidden = YES;
    }
    else if(self.selectedButton == self.filterButton){
        self.themeView.hidden = YES;
        self.musicView.hidden = YES;
        self.filterView.hidden = NO;
        self.editView.hidden = YES;
    } else if(self.selectedButton == self.editButton){
        self.themeView.hidden = YES;
        self.musicView.hidden = YES;
        self.filterView.hidden = YES;
        self.editView.hidden = NO;
    }
    
}

#pragma mark - linCollectionViewDelegate
- (void)downloadMeterial:(KMCMaterial *) meterial
               onSuccess:(void (^)(void))completeSuccess
               onFailure:(void (^)(int iErrorCode , NSString *strMessage))completeFailure
              onProgress:(void (^)(float fProgress , int64_t iSize))processingCallBack{
    return [self.kmcShortVideo downloadMeterial:meterial onSuccess:completeSuccess onFailure:completeFailure onProgress:processingCallBack];
}

-(BOOL)applyMeterial:(KMCMaterial *) meterial{
    [self.kmcShortVideo applyMaterial:meterial];
    [self play];
    return YES;
}

-(void)removeMeterial:(KMCMaterial *) meterial{
    [self.kmcShortVideo removeMaterial:meterial];
    [self play];
}
#pragma mark - UITextFieldDelegate


- (void)textFieldDidEndEditing:(UITextField *)textField{
    [self.kmcShortVideo setThemeTitleCaptionText:textField.text];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField{
    [self.themeTextField resignFirstResponder];
    self.themeTextField.hidden = YES;
    return YES;
}

#pragma mark - editCollectionViewDelegate
- (void)addAssetClicked:(NSInteger)insertIndex{
    self.insertIndex = insertIndex;
    linImagePickerViewController* imagePicker = [[linImagePickerViewController alloc]init];
    imagePicker.preEdit = NO;
    imagePicker.delegate = self;
    UINavigationController* navigation = [[UINavigationController alloc] initWithRootViewController:imagePicker];
    [self presentViewController:navigation animated:YES completion:nil];
}

- (void)editAssetClicked:(NSInteger)index{
    NSMutableArray * assets = [[NSMutableArray alloc] init];
    PHAsset * asset = self.assets[index];
    [assets addObject:asset];
    if(asset.mediaType == PHAssetMediaTypeVideo){
        singleVideoEditViewController * singleVC = [[singleVideoEditViewController alloc]init];
        singleVC.assets = [assets copy];
        singleVC.delegate = self;
        singleVC.assetIndex = (int)index;
        [self.navigationController pushViewController:singleVC animated:YES];
    }else if(asset.mediaType == PHAssetMediaTypeImage){
        singleImageEditViewController * singleVC = [[singleImageEditViewController alloc]init];
        singleVC.assets = [assets copy];
        singleVC.delegate = self;
        singleVC.assetIndex = (int)index;
        [self.navigationController pushViewController:singleVC animated:YES];
    }
 }

- (void)deleteAsset:(int)index{
    [_kmcShortVideo removeVideoClip:index];

    //停止预览
    if(_playbackProgressTimer){
        [_playbackProgressTimer invalidate];
    }
    [_kmcShortVideo stopPlay];
    [self.playButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
    
    //更新label
    [self changeCurrentLabelValue:0];
    [self changeDurationLabelValue:_kmcShortVideo.duration];
    self.slider.value = 0.0f;
    _kmcShortVideo.curPosition = 0.0f;
}

#pragma mark - linImagePickerViewControllerDelegate
-(void)doneWithAssets:(NSArray *)assets{
    NSMutableArray *newArray = [[NSMutableArray alloc] init];
    if([self.editView.assets count] > 0){
        for(int i = 0; i < [self.editView.assets count]; i++)
        {
            if(i == self.insertIndex){
                for(int j = 0; j < [assets count]; j++){
                    [newArray addObject:[assets objectAtIndex:j]];
                }
            }
            [newArray addObject:[self.editView.assets objectAtIndex:i]];
        }
        //队尾
        if([self.editView.assets count] == self.insertIndex){
            for(int j = 0; j < [assets count]; j++){
                [newArray addObject:[assets objectAtIndex:j]];
            }
        }
    }else{
        for(int j = 0; j < [assets count]; j++){
            [newArray addObject:[assets objectAtIndex:j]];
        }
    }
    self.editView.assets = [newArray copy];
    [self.editView.collectionView reloadData];
    
    //copy到editVC里面
    self.assets = [newArray copy];
    for (int i = 0; i<assets.count; i++) {
        [_kmcShortVideo insertVideoClip:assets[i] atIndex:(int)(i+self.insertIndex)];
    }
    [self.playButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
}
#pragma mark - singleVideoEditViewControllerDelegate
- (void)doneWithClipIndex:(int)index
                   Config:(config)config{
    if(config.startTime){
        [_kmcShortVideo changeClip:index TrimInPoint:config.startTime];
    }
    if(config.endTime){
        [_kmcShortVideo changeClip:index TrimOutPoint:config.endTime];
    }
    if(config.speed)
        [_kmcShortVideo changeClip:index Speed:config.speed];
    if(config.bright)
        [_kmcShortVideo changeClip:index bright:config.bright];
    if(config.Contrast)
        [_kmcShortVideo changeClip:index contrast:config.Contrast];
    if(config.Saturation)
        [_kmcShortVideo changeClip:index saturation:config.Saturation];
    if(config.rotate)
        [_kmcShortVideo changeClip:index rotate:config.rotate];
    if(config.scale){
        [_kmcShortVideo changeClip:index xScale:config.scale];
        [_kmcShortVideo changeClip:index yScale:config.scale];
    }

}

#pragma mark - singleImageEditViewControllerDelegate
- (void)doneWithImageClipIndex:(int)index
                        Config:(imageConfig)config{
    if(config.duration)
        [_kmcShortVideo changeClip:index TrimOutPoint:config.duration];
    if(config.bright)
        [_kmcShortVideo changeClip:index bright:config.bright];
    if(config.Contrast)
        [_kmcShortVideo changeClip:index contrast:config.Contrast];
    if(config.Saturation)
        [_kmcShortVideo changeClip:index saturation:config.Saturation];
    if(config.rotate)
        [_kmcShortVideo changeClip:index rotate:config.rotate];
}

#pragma mark - KMCShortVideoDelegate
- (void)didPlaybackEOF{
    if(_playbackProgressTimer){
        [_playbackProgressTimer invalidate];
    }
    
    self.slider.value = 1.0;
    [self changeCurrentLabelValue:_kmcShortVideo.duration];
    [self.playButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];
}

- (void)didCompileProgress:(int)progress{
    NSLog(@"process:%d",progress);
    [MBProgressHUD HUDForView:self.view].progress = (float)(progress/100.0);
}

- (void)didCompileFinished:(NSString *)outputFilePath{
    NSLog(@"didCompileFinished");
    [MBProgressHUD hideHUDForView:self.view animated:YES];
    ALAssetsLibrary *library = [[ALAssetsLibrary alloc] init];
    [library writeVideoAtPathToSavedPhotosAlbum:[NSURL fileURLWithPath:outputFilePath]
                                completionBlock:^(NSURL *assetURL, NSError *error) {
                                    if (error) {
                                        NSLog(@"Save video fail:%@",error);
                                    } else {
                                        NSLog(@"Save video succeed.");
                                    }
                                }];
}
#pragma mark - 生成
- (NSString *)getDocumentPath {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    return documentsDirectory;
}

- (NSString *)getCompileTmpPath {
    return [[self getDocumentPath] stringByAppendingPathComponent:@"tmp"];
}

- (NSString *)getCompilePath {
    return [[self getCompileTmpPath] stringByAppendingFormat:@"/video%@.mp4",[self getTimeAndRandom]];
}

- (NSString *)getTimeAndRandom {
    NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyyMMddHHmmss"];
    return [formatter stringFromDate:[NSDate date]];
}

- (void)startCompile:(id)sender {
    [_kmcShortVideo compileFile:[self getCompilePath] resolutionGrade:KMCCompileVideoResolutionGrade720 bitrateGrade:KMCCompileBitrateGradeHigh];
    
    MBProgressHUD* hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    hud.mode = MBProgressHUDModeDeterminateHorizontalBar;
}

@end
