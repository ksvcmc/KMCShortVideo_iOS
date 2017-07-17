//
//  NemoFilterCell.m
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import "linCollectionCell.h"

@interface linCollectionCell(){
    
}

@property (nonatomic, strong) UIImageView * imageView;
@property (nonatomic, strong) UILabel * imageName;
@property(nonatomic,strong)UIButton * downloadBtn;
@property (nonatomic, strong) UIView * maskView;
@property (nonatomic, strong) MBProgressHUD *hud;

@end

@implementation linCollectionCell

- (id)initWithFrame:(CGRect)frame
{
    if (self = [super initWithFrame:frame]) {
        [self setupUI];
    }
    return self;
}

- (void)setupUI{
    //缩略图
    self.imageView = [[UIImageView alloc] init];
    //缩略图名称
    self.imageName = [[UILabel alloc] init];
    self.imageName.font = [UIFont systemFontOfSize:12];
    self.imageName.backgroundColor = [UIColor colorWithHexString:@"#ffffff"];
    self.imageName.textColor = [UIColor colorWithHexString:@"#0e0f1a"];
    self.imageName.textAlignment = NSTextAlignmentCenter;
    //选中遮罩层
    self.selectedMaskView = [[UIView alloc]init];
    self.selectedMaskView.backgroundColor = [UIColor colorWithHexString:@"#9013FE"];
    self.selectedMaskView.alpha = 0.4;
    self.selectedMaskView.hidden = YES;

    //遮罩层
    self.maskView = [[UIView alloc]init];
    self.maskView.backgroundColor = [UIColor blackColor];
    self.maskView.alpha = 0.4;
    self.maskView.hidden = YES;
    
    //下载按钮
    _downloadBtn = [[UIButton alloc]init];
    [_downloadBtn setImage:[UIImage imageNamed:@"download"] forState:UIControlStateNormal];
    _downloadBtn.userInteractionEnabled = NO;
    _downloadBtn.hidden = YES;

    [self.contentView addSubview:self.imageView];
    [self.contentView addSubview:self.imageName];
    [self.contentView addSubview:self.selectedMaskView];
    [self.contentView addSubview:self.maskView];
    [self.contentView addSubview:_downloadBtn];
    
    [self.imageView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.contentView);
        make.leading.equalTo(self.contentView);
        make.width.mas_equalTo(63);
        make.height.mas_equalTo(70);
    }];
    [self.imageName mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.imageView.mas_bottom);
        make.leading.equalTo(self.contentView);
        make.width.mas_equalTo(63);
        make.height.mas_equalTo(21);
    }];
    
    [self.selectedMaskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.contentView);
    }];
    
    [self.maskView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(self.contentView);
    }];
    
    [_downloadBtn mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(self.contentView);
        make.centerX.equalTo(self.contentView);
        make.height.mas_equalTo(26);
        make.width.mas_equalTo(26);
    }];
}


-(void)setMaterial:(KMCMaterial *)material{
    _material = material;
    
    //设置缩略图
    if(!_material){
        [self.imageView setImage:[UIImage imageNamed:@"forbid"]];
        self.imageView.contentMode =  UIViewContentModeCenter;
    }else{
        [self.imageView sd_setImageWithURL:[NSURL URLWithString:_material.strThumbnailURL] placeholderImage:nil options:SDWebImageRefreshCached];
        NSLog(@"url:%@",_material.strThumbnailURL);
    }
    //设置缩略图名称
    if(!_material){
        self.imageName.text = @"无";
    }
    else{
        self.imageName.text = _material.strThumbnailName;
    }
    
    //设置下载图标
    if ( !_material || [self isMaterialDownloaded:self.material.strName] ) {
        self.downloadBtn.hidden = YES;
        self.maskView.hidden = YES;
    }else{
        self.downloadBtn.hidden = NO;
        self.maskView.hidden = NO;
    }
}

- (BOOL)isMaterialDownloaded:(NSString *)strName{
    NSString *ourDocumentPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,  NSUserDomainMask,YES) objectAtIndex:0];
    NSString *FilePath=[ourDocumentPath stringByAppendingPathComponent:strName];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    BOOL result = [fileManager fileExistsAtPath:FilePath];
    return result;
}

-(void)startDownload{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self showHud];
        self.downloadBtn.hidden = YES;
        self.maskView.hidden = YES;
    });
}

-(void)downloading:(float)process{
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0), ^{
            dispatch_async(dispatch_get_main_queue(), ^{
                self.hud.progress = process;
            });
    });
}

-(void)finishDownload{
    dispatch_async(dispatch_get_main_queue(), ^{
            [MBProgressHUD hideAllHUDsForView:self.imageView animated:NO];
    });
}

-(void)downloadFail{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.downloadBtn.hidden = NO;
        self.maskView.hidden = NO;
        [MBProgressHUD hideAllHUDsForView:self.imageView animated:NO];
    });
}

-(void)showHud{
    self.hud = [MBProgressHUD showHUDAddedTo:self.imageView animated:YES];
    self.hud.mode = MBProgressHUDModeDeterminate;
    self.hud.color = [UIColor clearColor];
}
    
- (void)setSelected:(BOOL)selected{
    [super setSelected:selected];
    if (selected) {
        self.selectedMaskView.hidden = NO;
    }else{
        self.selectedMaskView.hidden = YES;
    }
}


@end
