//
//  PDPatch.m
//  Sinewave
//
//  Created by Thomas Holz on 28.06.20.
//  Copyright © 2020 Thomas Holz. All rights reserved.
//

#import "PDPatch.h"

@implementation PDPatch

-(void)onOff1:(BOOL)yesNo{ // i added this code
    float yn = (float)yesNo; // i added this code
    [PdBase sendFloat:yn toReceiver:@"onOff1"]; // i added this code
}

-(void)slider1:(float)test1{ // i added this code
    float t1 = (float)test1; // i added this code
    [PdBase sendFloat:t1 toReceiver:@"slider1"]; // i added this code
}

-(void)taste1:(float)druck1{ // i added this code
    float d1 = (float)druck1; // i added this code
    [PdBase sendFloat:d1 toReceiver:@"taste1"]; // i added this code
}

-(instancetype)initWithFile:(NSString *)pdFile{
    void *patch;
    self = [super init];
    if(self){
        patch = [PdBase openFile:pdFile path:[[NSBundle mainBundle]resourcePath]];
        if(!patch){
            UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Uh-oh" message:@"Pd Patch not found" delegate:self cancelButtonTitle:@"Crap" otherButtonTitles:nil, nil];
            [alert show];
        }
    }
    return self;
}
@end
