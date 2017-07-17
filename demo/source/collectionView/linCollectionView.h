//
//  NemoFilterView.h
//  Nemo
//
//  Created by ksyun on 17/4/20.
//  Copyright © 2017年 com.ksyun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <KMCShortVideo/KMCMaterial.h>

@protocol linCollectionViewDelegate <NSObject>

- (void)downloadMeterial:(KMCMaterial *) meterial
               onSuccess:(void (^)(void))completeSuccess
               onFailure:(void (^)(int iErrorCode , NSString *strMessage))completeFailure
              onProgress:(void (^)(float fProgress , int64_t iSize))processingCallBack;

-(BOOL)applyMeterial:(KMCMaterial *) meterial;

-(void)removeMeterial:(KMCMaterial *) meterial;


@end


@interface linCollectionView : UIView

@property (nonatomic, weak) id <linCollectionViewDelegate>delegate;
@property (nonatomic , readwrite) NSMutableArray* materials;
@property (nonatomic, strong) NSString * strType;

@property (nonatomic, strong) UICollectionView * collectionView;

@end
