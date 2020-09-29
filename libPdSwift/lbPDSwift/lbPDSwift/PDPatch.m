#import "PDPatch.h"

@implementation PDPatch

/*--- Slider Section ---*/
/* Fundamentals */
-(void)slider_fund1:(float)fund1{
    float fun1 = (float)fund1;
    [PdBase sendFloat:fun1 toReceiver:@"slider_fund1"];
}
-(void)slider_fund2:(float)fund2{
    float fun2 = (float)fund2;
    [PdBase sendFloat:fun2 toReceiver:@"slider_fund2"];
}
-(void)slider_fund3:(float)fund3{
    float fun3 = (float)fund3;
    [PdBase sendFloat:fun3 toReceiver:@"slider_fund3"];
}
-(void)slider_fund4:(float)fund4{
    float fun4 = (float)fund4;
    [PdBase sendFloat:fun4 toReceiver:@"slider_fund4"];
}
-(void)slider_fund5:(float)fund5{
    float fun5 = (float)fund5;
    [PdBase sendFloat:fun5 toReceiver:@"slider_fund5"];
}

/* Frequency Modulation */
-(void)slider_shimFreq1:(float)shimFreq1{
    float shimF1 = (float)shimFreq1;
    [PdBase sendFloat:shimF1 toReceiver:@"slider_shimFreq1"];
}
-(void)slider_shimFreq2:(float)shimFreq2{
    float shimF2 = (float)shimFreq2;
    [PdBase sendFloat:shimF2 toReceiver:@"slider_shimFreq2"];
}
-(void)slider_shimFreq3:(float)shimFreq3{
    float shimF3 = (float)shimFreq3;
    [PdBase sendFloat:shimF3 toReceiver:@"slider_shimFreq3"];
}
-(void)slider_shimFreq4:(float)shimFreq4{
    float shimF4 = (float)shimFreq4;
    [PdBase sendFloat:shimF4 toReceiver:@"slider_shimFreq4"];
}

/* Modulation Strength*/
-(void)slider_shimStrg1:(float)shimStrg1{
    float shimS1 = (float)shimStrg1;
    [PdBase sendFloat:shimS1 toReceiver:@"slider_shimStrg1"];
}
-(void)slider_shimStrg2:(float)shimStrg2{
    float shimS2 = (float)shimStrg2;
    [PdBase sendFloat:shimS2 toReceiver:@"slider_shimStrg2"];
}
-(void)slider_shimStrg3:(float)shimStrg3{
    float shimS3 = (float)shimStrg3;
    [PdBase sendFloat:shimS3 toReceiver:@"slider_shimStrg3"];
}
-(void)slider_shimStrg4:(float)shimStrg4{
    float shimS4 = (float)shimStrg4;
    [PdBase sendFloat:shimS4 toReceiver:@"slider_shimStrg4"];
}

/* Envelope */
-(void)slider_attack:(float)attack{
    float att = (float)attack;
    [PdBase sendFloat:att toReceiver:@"slider_attack"];
}
-(void)slider_decay:(float)decay{
    float dec = (float)decay;
    [PdBase sendFloat:dec toReceiver:@"slider_decay"];
}
-(void)slider_sustain:(float)sustain{
    float sus = (float)sustain;
    [PdBase sendFloat:sus toReceiver:@"slider_sustain"];
}
-(void)slider_release:(float)release{
    float rel = (float)release;
    [PdBase sendFloat:rel toReceiver:@"slider_release"];
}
-(void)slider_exp:(float)expo{
    float exp = (float)expo;
    [PdBase sendFloat:exp toReceiver:@"slider_exp"];
}

/* Spacer / Gain */
-(void)slider_spacer:(float)spacer{
    float space = (float)spacer;
    [PdBase sendFloat:space toReceiver:@"slider_spacer"];
}
-(void)slider_gain:(float)gain{
    float gai = (float)gain;
    [PdBase sendFloat:gai toReceiver:@"slider_gain"];
}

/*--- Button Section ---*/
/* Wavevorms */
-(void)button_sine:(float)sine{
    float sin = (float)sine;
    [PdBase sendFloat:sin toReceiver:@"button_sine"];
}
-(void)button_sawtooth:(float)sawtooth{
    float saw = (float)sawtooth;
    [PdBase sendFloat:saw toReceiver:@"button_sawtooth"];
}
-(void)button_triangle:(float)triangle{
    float tri = (float)triangle;
    [PdBase sendFloat:tri toReceiver:@"button_triangle"];
}
-(void)button_square:(float)square{
    float sqr = (float)square;
    [PdBase sendFloat:sqr toReceiver:@"button_square"];
}

/* Keyboard */
-(void)button_note1:(float)note1{
    float no1 = (float)note1;
    [PdBase sendFloat:no1 toReceiver:@"button_note1"];
}
-(void)button_note2:(float)note2{
    float no2 = (float)note2;
    [PdBase sendFloat:no2 toReceiver:@"button_note2"];
}
-(void)button_note3:(float)note3{
    float no3 = (float)note3;
    [PdBase sendFloat:no3 toReceiver:@"button_note3"];
}
-(void)button_note4:(float)note4{
    float no4 = (float)note4;
    [PdBase sendFloat:no4 toReceiver:@"button_note4"];
}
-(void)button_note5:(float)note5{
    float no5 = (float)note5;
    [PdBase sendFloat:no5 toReceiver:@"button_note5"];
}
-(void)button_note6:(float)note6{
    float no6 = (float)note6;
    [PdBase sendFloat:no6 toReceiver:@"button_note6"];
}
-(void)button_note7:(float)note7{
    float no7 = (float)note7;
    [PdBase sendFloat:no7 toReceiver:@"button_note7"];
}
-(void)button_note8:(float)note8{
    float no8 = (float)note8;
    [PdBase sendFloat:no8 toReceiver:@"button_note8"];
}
-(void)button_note9:(float)note9{
    float no9 = (float)note9;
    [PdBase sendFloat:no9 toReceiver:@"button_note9"];
}
-(void)button_note10:(float)note10{
    float no10 = (float)note10;
    [PdBase sendFloat:no10 toReceiver:@"button_note10"];
}
-(void)button_note11:(float)note11{
    float no11 = (float)note11;
    [PdBase sendFloat:no11 toReceiver:@"button_note11"];
}
-(void)button_note12:(float)note12{
    float no12 = (float)note12;
    [PdBase sendFloat:no12 toReceiver:@"button_note12"];
}
-(void)button_note13:(float)note13{
    float no13 = (float)note13;
    [PdBase sendFloat:no13 toReceiver:@"button_note13"];
}
-(void)button_note14:(float)note14{
    float no14 = (float)note14;
    [PdBase sendFloat:no14 toReceiver:@"button_note14"];
}
-(void)button_note15:(float)note15{
    float no15 = (float)note15;
    [PdBase sendFloat:no15 toReceiver:@"button_note15"];
}
-(void)button_note16:(float)note16{
    float no16 = (float)note16;
    [PdBase sendFloat:no16 toReceiver:@"button_note16"];
}
-(void)button_note17:(float)note17{
    float no17 = (float)note17;
    [PdBase sendFloat:no17 toReceiver:@"button_note17"];
}
-(void)button_note18:(float)note18{
    float no18 = (float)note18;
    [PdBase sendFloat:no18 toReceiver:@"button_note18"];
}
-(void)button_note19:(float)note19{
    float no19 = (float)note19;
    [PdBase sendFloat:no19 toReceiver:@"button_note19"];
}
-(void)button_note20:(float)note20{
    float no20 = (float)note20;
    [PdBase sendFloat:no20 toReceiver:@"button_note20"];
}
-(void)button_note21:(float)note21{
    float no21 = (float)note21;
    [PdBase sendFloat:no21 toReceiver:@"button_note21"];
}
-(void)button_note22:(float)note22{
    float no22 = (float)note22;
    [PdBase sendFloat:no22 toReceiver:@"button_note22"];
}
-(void)button_note23:(float)note23{
    float no23 = (float)note23;
    [PdBase sendFloat:no23 toReceiver:@"button_note23"];
}
-(void)button_note24:(float)note24{
    float no24 = (float)note24;
    [PdBase sendFloat:no24 toReceiver:@"button_note24"];
}
-(void)button_note25:(float)note25{
    float no25 = (float)note25;
    [PdBase sendFloat:no25 toReceiver:@"button_note25"];
}


void envelope1_setup();

-(instancetype)initWithFile:(NSString *)pdFile{
    void *patch;
    self = [super init];
    if(self){
        envelope1_setup();
        patch = [PdBase openFile:pdFile path:[[NSBundle mainBundle]resourcePath]];
        if(!patch){
            UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Uh-oh" message:@"Pd Patch not found" delegate:self cancelButtonTitle:@"Crap" otherButtonTitles:nil, nil];
            [alert show];
        }
    }
    return self;
}
@end
