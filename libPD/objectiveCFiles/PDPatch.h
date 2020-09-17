//
//  PDPatch.h
//  Sinewave
//
//  Created by Thomas Holz on 28.06.20.
//  Copyright © 2020 Thomas Holz. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PdDispatcher.h"  // import
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface PDPatch : NSObject

-(void)onOff:(BOOL)yesNo;
-(instancetype)initWithFile:(NSString *)pdFile;

@end

NS_ASSUME_NONNULL_END
