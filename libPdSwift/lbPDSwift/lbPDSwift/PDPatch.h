#import <Foundation/Foundation.h>
#import "PdDispatcher.h"  // import
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface PDPatch : NSObject

/*--- Slider Section ---*/
/* Fundamentals */
-(void)slider_fund1:(float)fund1;
-(void)slider_fund2:(float)fund2;
-(void)slider_fund3:(float)fund3;
-(void)slider_fund4:(float)fund4;
-(void)slider_fund5:(float)fund5;

/* Frequency Modulation */
-(void)slider_shimFreq1:(float)shimFreq1;
-(void)slider_shimFreq2:(float)shimFreq2;
-(void)slider_shimFreq3:(float)shimFreq3;
-(void)slider_shimFreq4:(float)shimFreq4;

/* Modulation Strength */
-(void)slider_shimStrg1:(float)shimStrg1;
-(void)slider_shimStrg2:(float)shimStrg2;
-(void)slider_shimStrg3:(float)shimStrg3;
-(void)slider_shimStrg4:(float)shimStrg4;

/* Reverb */
-(void)slider_cbF_cof0:(float)cbF_cof0;
-(void)slider_cbF_cof1:(float)cbF_cof1;
-(void)slider_cbF_cof2:(float)cbF_cof2;
-(void)slider_cbF_cof3:(float)cbF_cof3;
-(void)slider_apF_cof:(float)apF_cof;
-(void)slider_wet_dry:(float)wet_dry;

/* Delay */
-(void)slider_delayT1:(float)delayT1;
-(void)slider_decay1:(float)decay1;
-(void)slider_delayT2:(float)delayT2;
-(void)slider_decay2:(float)decay2;

/* Envelope */
-(void)slider_attack:(float)attack;
-(void)slider_decay:(float)decay;
-(void)slider_sustain:(float)sustain;
-(void)slider_release:(float)release;
-(void)slider_exp:(float)expo;

/* Spacer / Gain */
-(void)slider_spacer:(float)spacer;
-(void)slider_gain:(float)gain;

/*--- Button Section ---*/
/* Wavevorms */
-(void)button_sine:(float)sine;
-(void)button_sawtooth:(float)sawtooth;
-(void)button_triangle:(float)triangle;
-(void)button_square:(float)square;

/* Keyboard */
-(void)button_note1:(float)note1;
-(void)button_note2:(float)note2;
-(void)button_note3:(float)note3;
-(void)button_note4:(float)note4;
-(void)button_note5:(float)note5;
-(void)button_note6:(float)note6;
-(void)button_note7:(float)note7;
-(void)button_note8:(float)note8;
-(void)button_note9:(float)note9;
-(void)button_note10:(float)note10;
-(void)button_note11:(float)note11;
-(void)button_note12:(float)note12;
-(void)button_note13:(float)note13;
-(void)button_note14:(float)note14;
-(void)button_note15:(float)note15;
-(void)button_note16:(float)note16;
-(void)button_note17:(float)note17;
-(void)button_note18:(float)note18;
-(void)button_note19:(float)note19;
-(void)button_note20:(float)note20;
-(void)button_note21:(float)note21;
-(void)button_note22:(float)note22;
-(void)button_note23:(float)note23;
-(void)button_note24:(float)note24;
-(void)button_note25:(float)note25;

-(instancetype)initWithFile:(NSString *)pdFile;

@end

NS_ASSUME_NONNULL_END
