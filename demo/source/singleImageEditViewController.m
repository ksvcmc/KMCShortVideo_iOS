//
//  singleVideoEditViewController.m
//  KMCShortVideoDemo
//
//  Created by ksyun on 2017/7/1.
//  Copyright © 2017年 ksyun. All rights reserved.
//

#import "singleImageEditViewController.h"
#import <KMCShortVideo/KMCShortVideo.h>
#import <Photos/Photos.h>
#import "Masonry.h"
#import "linCollectionView.h"
#import "editCollectionView.h"
#import "linImagePickerViewController.h"
#import "SAVideoRangeSlider.h"

@interface singleImageEditViewController ()<SAVideoRangeSliderDelegate,KMCShortVideoDelegate>{
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
//单个视频编辑页
@property (nonatomic,strong) UIView * videoEditView;
@property (nonatomic, strong)UIView *videoPageLine;
@property (nonatomic, strong)UIButton * videoSelectedButton;
@property (nonatomic,strong) UIButton * durationButton;
@property (nonatomic,strong) UIButton * colorButton;
@property (nonatomic,strong) UIButton * rotateButton;
@property (nonatomic,strong) UIButton * saveButton;
//时长
@property (nonatomic,strong) UIView *  durationView;
@property (nonatomic,strong) UILabel * imageDurationLabel;
@property (nonatomic,strong) UISlider * durationSlide;
@property (nonatomic,strong) UILabel * currentTimeLabel;
//色彩
@property (nonatomic,strong) UIView * colorView;
@property (nonatomic,strong) UILabel * brightLabel;
@property (nonatomic,strong) UISlider * brightSlider;
@property (nonatomic,strong) UILabel * contrastLabel;
@property (nonatomic,strong) UISlider * contrastSlider;
@property (nonatomic,strong) UILabel * saturationLabel;
@property (nonatomic,strong) UISlider * saturationSlider;
//旋转
@property (nonatomic,strong) UIView * rotateView;
@property (nonatomic,strong) UIButton * leftRotate;
@property (nonatomic,strong) UIButton * rightRotate;

//数据
@property (nonatomic,assign) CGFloat rotate;
@property (nonatomic,assign) CGFloat duration;


@end

@implementation singleImageEditViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self setupUI];
    [self setupShortVideo];
    // Do any additional setup after loading the view.
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    //时长值
    self.currentTimeLabel.text = [NSString stringWithFormat:@"%lldS",[_kmcShortVideo duration]];
    self.durationSlide.value = [_kmcShortVideo duration];
    self.duration = [_kmcShortVideo duration];
}

#pragma mark - UI
-(void)setupUI{
    self.view.backgroundColor = [UIColor blackColor];
    
    [self setupNavigation];
    //播放器
    [self setupPlayerView];
    //选择页
    [self setupVideoEditView];
}

-(void)setupNavigation{
    self.navigationItem.title = @"单个图像编辑";
    self.navigationItem.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"back"] style:UIBarButtonItemStylePlain target:self action:@selector(back) ];
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
    NSInteger seconds = (NSInteger)ceil(_kmcShortVideo.duration - 60.0 * (double)minutes);
    self.durationLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];
    self.durationLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.durationLabel.font = [UIFont systemFontOfSize:14];
    
    [self.view addSubview:self.PlayerBgView];
    [self.PlayerBgView addSubview:self.liveWindow];
    [self.PlayerBgView addSubview:self.controlView];
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

-(void)setupVideoEditView{
    self.videoEditView = [[UIView alloc] init];
    //选择按钮
    self.durationButton = [self setupVideoEditButtonWithTitle:@"时长" Index:0];
    self.colorButton = [self setupVideoEditButtonWithTitle:@"色彩" Index:1];
    self.rotateButton = [self setupVideoEditButtonWithTitle:@"旋转" Index:2];
    //红线
    _videoPageLine = [[UIView alloc]init];
    _videoPageLine.backgroundColor = [UIColor colorWithHexString:@"#9012fe"];
    //保存按钮
    self.saveButton = [[UIButton alloc] init];
    [self.saveButton setTitle:@"完成" forState:(UIControlStateNormal)];
    [self.saveButton setTitleColor:[UIColor colorWithHexString:@"#ffffff"] forState:(UIControlStateNormal)];
    self.saveButton.titleLabel.font = [UIFont systemFontOfSize:18];
    [self.saveButton addTarget:self action:@selector(done) forControlEvents:(UIControlEventTouchUpInside)];
    self.saveButton.backgroundColor = [UIColor colorWithHexString:@"440977"];
    
    //时长
    self.durationView = [[UIView alloc] init];
    //时长label
    self.imageDurationLabel = [[UILabel alloc] init];
    self.imageDurationLabel.font = [UIFont systemFontOfSize:14];
    self.imageDurationLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.imageDurationLabel.text = @"显示时长";
    //时长滑动框
    self.durationSlide = [[UISlider alloc] init];
    self.durationSlide.minimumValue = 0.0f;
    self.durationSlide.maximumValue = 1.0f;
    self.durationSlide.tintColor = [UIColor colorWithHexString:@"#9012FE"];
    [self.durationSlide addTarget:self action:@selector(sliderDurationChanged:) forControlEvents:(UIControlEventValueChanged)];
    //当前时长
    self.currentTimeLabel = [[UILabel alloc] init];
    self.currentTimeLabel.font = [UIFont systemFontOfSize:16];
    self.currentTimeLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];

    //色彩view
    self.colorView = [[UIView alloc] init];
    //亮度
    self.brightLabel = [[UILabel alloc] init];
    self.brightLabel.font = [UIFont systemFontOfSize:14];
    self.brightLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.brightLabel.text = @"亮度";
    //亮度滑动条
    self.brightSlider = [[UISlider alloc] init];
    self.brightSlider.minimumValue = 0.0f;
    self.brightSlider.maximumValue = 10.0f;
    self.brightSlider.tintColor = [UIColor colorWithHexString:@"#9012FE"];
    [self.brightSlider addTarget:self action:@selector(sliderColorChanged:) forControlEvents:(UIControlEventValueChanged)];
    //对比度
    self.contrastLabel = [[UILabel alloc] init];
    self.contrastLabel.font = [UIFont systemFontOfSize:14];
    self.contrastLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.contrastLabel.text = @"对比度";
    //对比度滑动条
    self.contrastSlider = [[UISlider alloc] init];
    self.contrastSlider.minimumValue = 0.0f;
    self.contrastSlider.maximumValue = 10.0f;
    self.contrastSlider.value = 1.0f;
    self.contrastSlider.tintColor = [UIColor colorWithHexString:@"#9012FE"];
    [self.contrastSlider addTarget:self action:@selector(sliderColorChanged:) forControlEvents:(UIControlEventValueChanged)];
    //饱和度
    self.saturationLabel = [[UILabel alloc] init];
    self.saturationLabel.font = [UIFont systemFontOfSize:14];
    self.saturationLabel.textColor = [UIColor colorWithHexString:@"#ffffff"];
    self.saturationLabel.text = @"饱和度";
    //对比度滑动条
    self.saturationSlider = [[UISlider alloc] init];
    self.saturationSlider.minimumValue = 0.0f;
    self.saturationSlider.maximumValue = 10.0f;
    self.saturationSlider.value = 1.0f;
    self.saturationSlider.tintColor = [UIColor colorWithHexString:@"#9012FE"];
    [self.saturationSlider addTarget:self action:@selector(sliderColorChanged:) forControlEvents:(UIControlEventValueChanged)];
    //旋转view
    self.rotateView = [[UIView alloc] init];
    //左旋转
    self.leftRotate = [[UIButton alloc] init];
    [self.leftRotate setImage:[UIImage imageNamed:@"leftRotate"] forState:UIControlStateNormal];
    [self.leftRotate addTarget:self action:@selector(rotate:) forControlEvents:(UIControlEventTouchUpInside)];
    //右旋转
    self.rightRotate = [[UIButton alloc] init];
    [self.rightRotate setImage:[UIImage imageNamed:@"rightRotate"] forState:UIControlStateNormal];
    [self.rightRotate addTarget:self action:@selector(rotate:) forControlEvents:(UIControlEventTouchUpInside)];
    
    [self.view addSubview:self.videoEditView];
    [self.videoEditView addSubview:self.durationButton];
    [self.videoEditView addSubview:self.colorButton];
    [self.videoEditView addSubview:self.rotateButton];
    [self.videoEditView addSubview:self.videoPageLine];
    [self.videoEditView addSubview:self.saveButton];
    [self.videoEditView addSubview:self.colorView];
    [self.colorView addSubview:self.brightLabel];
    [self.colorView addSubview:self.brightSlider];
    [self.colorView addSubview:self.contrastLabel];
    [self.colorView addSubview:self.contrastSlider];
    [self.colorView addSubview:self.saturationLabel];
    [self.colorView addSubview:self.saturationSlider];
    [self.videoEditView addSubview:self.rotateView];
    [self.rotateView addSubview:self.leftRotate];
    [self.rotateView addSubview:self.rightRotate];
    [self.videoEditView addSubview:self.durationView];
    [self.durationView addSubview:self.imageDurationLabel];
    [self.durationView addSubview:self.durationSlide];
    [self.durationView addSubview:self.currentTimeLabel];
    
    [self.videoEditView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.controlView.mas_bottom);
        make.bottom.leading.trailing.equalTo(self.view);
    }];
    [self.durationButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.videoEditView).offset(33);
        make.leading.equalTo(self.videoEditView).offset(83);
        make.height.mas_equalTo(27);
        make.width.mas_equalTo(34);
    }];
    [self.colorButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.videoEditView).offset(33);
        make.leading.equalTo(self.durationButton.mas_trailing).offset(52);
        make.height.mas_equalTo(27);
        make.width.mas_equalTo(34);
    }];
    [self.rotateButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.videoEditView).offset(33);
        make.leading.equalTo(self.colorButton.mas_trailing).offset(52);
        make.height.mas_equalTo(27);
        make.width.mas_equalTo(34);
    }];
    [self.videoPageLine mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.durationButton.mas_bottom).offset(7);
        make.centerX.equalTo(self.durationButton.mas_centerX);
        make.height.mas_equalTo(4);
        make.width.mas_equalTo(33);
    }];
    [self.saveButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.colorView.mas_bottom);
        make.leading.trailing.bottom.equalTo(self.videoEditView);
    }];
    
    [self.colorView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.videoPageLine.mas_bottom);
        make.leading.trailing.equalTo(self.videoEditView);
        make.bottom.equalTo(self.videoEditView).offset(-49);
    }];
    [self.brightLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.colorView).offset(64);
        make.leading.equalTo(self.colorView).offset(34);
    }];
    [self.contrastLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.brightLabel.mas_bottom).offset(36);
        make.leading.equalTo(self.colorView).offset(34);
    }];
    [self.saturationLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.contrastLabel.mas_bottom).offset(36);
        make.leading.equalTo(self.colorView).offset(34);
    }];
    [self.contrastSlider mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.contrastLabel);
        make.leading.equalTo(self.contrastLabel.mas_trailing).offset(33);
        make.trailing.equalTo(self.colorView).offset(-34);
    }];
    [self.saturationSlider mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.saturationLabel);
        make.leading.equalTo(self.saturationLabel.mas_trailing).offset(33);
        make.trailing.equalTo(self.colorView).offset(-34);
    }];
    [self.brightSlider mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.brightLabel);
        make.leading.equalTo(self.contrastSlider);
        make.trailing.equalTo(self.colorView).offset(-34);
    }];
    [self.rotateView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.videoPageLine.mas_bottom);
        make.leading.trailing.equalTo(self.videoEditView);
        make.bottom.equalTo(self.videoEditView).offset(-49);
    }];
    [self.leftRotate mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.equalTo(self.rotateView).offset(92);
        make.top.equalTo(self.rotateView).offset(90);
        make.width.mas_equalTo(62);
        make.height.mas_equalTo(62);
    }];
    [self.rightRotate mas_makeConstraints:^(MASConstraintMaker *make) {
        make.trailing.equalTo(self.rotateView).offset(-91);
        make.top.equalTo(self.rotateView).offset(90);
        make.width.mas_equalTo(62);
        make.height.mas_equalTo(62);
    }];
    [self.durationView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.videoPageLine.mas_bottom);
        make.leading.trailing.equalTo(self.videoEditView);
        make.bottom.equalTo(self.videoEditView).offset(-49);
    }];
    [self.imageDurationLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.equalTo(self.durationView).offset(34);
        make.top.equalTo(self.durationView).offset(112);
    }];
    [self.durationSlide mas_makeConstraints:^(MASConstraintMaker *make) {
        make.leading.equalTo(self.imageDurationLabel.mas_trailing).offset(19);
        make.trailing.equalTo(self.durationView).offset(-34);
        make.centerY.equalTo(self.imageDurationLabel);
    }];
    [self.currentTimeLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(self.durationView);
        make.top.equalTo(self.durationSlide.mas_bottom).offset(24);
    }];

    self.videoSelectedButton = self.durationButton;
}


#pragma mark - action
-(void)back{
    [_kmcShortVideo stopPlay];
    [_kmcShortVideo remove];
    [self.navigationController popViewControllerAnimated:YES];
}



-(void)sliderColorChanged:(id)sender {
    UISlider * slider = sender;
    if(slider == self.brightSlider){
        [_kmcShortVideo changeClip:0 bright:self.brightSlider.value];
        [self InteruptPlay];
    }else if(slider == self.contrastSlider){
        [_kmcShortVideo changeClip:0 contrast:self.contrastSlider.value];
        [self InteruptPlay];
    }else if(slider == self.saturationSlider){
        [_kmcShortVideo changeClip:0 saturation:self.contrastSlider.value];
        [self InteruptPlay];
    }
}

-(void)sliderDurationChanged:(id)sender {
    UISlider * slider = sender;
    if(slider == self.durationSlide){
        self.duration = self.durationSlide.value *[_kmcShortVideo duration];
        [self InteruptPlay];
        self.currentTimeLabel.text = [NSString stringWithFormat:@"%01ldS",(long)self.duration];
    }
}



-(void)rotate:(id)sender {
    UIButton * button = sender;
    if(button == self.leftRotate){
        self.rotate += 90;
        if(self.rotate == 360)
            self.rotate = 0;
    }else if(button == self.rightRotate){
        self.rotate -= 90;
        if(self.rotate == -360)
            self.rotate = 0;
    }
    [_kmcShortVideo changeClip:0 rotate:self.rotate];
    [self InteruptPlay];
}



-(void)done{
    //编辑参数上传
    imageConfig myconfig;
    myconfig.bright = self.brightSlider.value;
    myconfig.Contrast = self.contrastSlider.value;
    myconfig.Saturation = self.saturationSlider.value;
    myconfig.rotate = self.rotate;
    myconfig.duration = self.duration;
    if(self.delegate)
        [self.delegate doneWithImageClipIndex:self.assetIndex Config:myconfig];
    //移除预览
    [self.kmcShortVideo remove];
    [self.navigationController popViewControllerAnimated:YES];
}

- (UIButton *)setupVideoEditButtonWithTitle:(NSString *)title Index:(NSInteger)index{
    UIButton *btn = [[UIButton alloc]init];
    [btn setTitle:title forState:(UIControlStateNormal)];
    [btn setTitleColor:[UIColor colorWithHexString:@"#9b9b9b"] forState:(UIControlStateNormal)];
    
    btn.tag = index +kVideoTag;
    btn.titleLabel.font = [UIFont systemFontOfSize:16];
    
    [btn addTarget:self action:@selector(videoPageClick:) forControlEvents:(UIControlEventTouchUpInside)];
    
    return btn;
}

- (void)videoPageClick:(UIButton *)btn{
    self.videoSelectedButton = btn;
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

- (void)handleProgressTimer:(NSTimer *)timer {
    self.slider.value = self.slider.maximumValue * _kmcShortVideo.curPosition / _kmcShortVideo.duration;
    
    [self changeCurrentLabelValue:self.slider.maximumValue * _kmcShortVideo.curPosition];
    [self changeDurationLabelValue:_kmcShortVideo.duration];
}

-(void)changeCurrentLabelValue:(float)time{
    //当前时间
    NSInteger minutes = (NSInteger)(time / 60.0);
    NSInteger seconds = (NSInteger)ceil(time - 60.0 * (double)minutes);
    self.currentLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];
    [self changeDurationLabelValue:_kmcShortVideo.duration];
}

-(void)changeDurationLabelValue:(float)time{
    //总时长
    NSInteger minutes = (NSInteger)(time / 60.0);
    NSInteger seconds = (NSInteger)ceil(time - 60.0 * (double)minutes);
    self.durationLabel.text = [NSString stringWithFormat:@"%02ld:%02ld", (long)minutes, (long)seconds];
}

-(void)setVideoSelectedButton:(UIButton *)videoSelectedButton{
    if(_videoSelectedButton == videoSelectedButton)
        return;
    //设置button选中颜色
    [videoSelectedButton setTitleColor:[UIColor colorWithHexString:@"#ffffff"] forState:(UIControlStateNormal)];
    if(_videoSelectedButton){
        [_videoSelectedButton setTitleColor:[UIColor colorWithHexString:@"#9b9b9b"] forState:(UIControlStateNormal)];
    }
    _videoSelectedButton = videoSelectedButton;
    //设置pageline的位置
    self.videoPageLine.center = CGPointMake(_videoSelectedButton.center.x, CGRectGetMaxY(_videoSelectedButton.frame)+7);
    //设置色彩页面值
    self.brightSlider.value =[_kmcShortVideo getBright:0];
    self.contrastSlider.value =[_kmcShortVideo getContrast:0];
    self.saturationSlider.value =[_kmcShortVideo getSaturation:0];
    //获得旋转值
    self.rotate = [_kmcShortVideo getRotate:0];
    //设置view的隐藏和开启
    if(self.videoSelectedButton == self.durationButton){
        self.colorView.hidden = YES;
        self.rotateView.hidden = YES;
        self.durationView.hidden = NO;
    }else if(self.videoSelectedButton == self.colorButton){
        self.colorView.hidden = NO;
        self.rotateView.hidden = YES;
        self.durationView.hidden = YES;
    }else if(self.videoSelectedButton == self.rotateButton){
        self.colorView.hidden = YES;
        self.rotateView.hidden = NO;
        self.durationView.hidden = YES;
    }
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

- (void)InteruptPlay{
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

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(void)setupShortVideo{
    //初始化sdk
    _kmcShortVideo = [[KMCShortVideo alloc] init];
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
    
    _kmcShortVideo.delegate =self;
    //往sdk里面添加视频片段
    for (int i = 0; i<self.assets.count; i++) {
        [_kmcShortVideo insertVideoClip:self.assets[i] atIndex:i];
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
#pragma mark - KMCShortVideoDelegate
- (void)didPlaybackEOF{
    if(_playbackProgressTimer){
        [_playbackProgressTimer invalidate];
    }
    
    self.slider.value = 1.0;
    [self changeCurrentLabelValue:_kmcShortVideo.duration];
    [self.playButton setImage:[UIImage imageNamed:@"play"] forState:UIControlStateNormal];

}


@end
