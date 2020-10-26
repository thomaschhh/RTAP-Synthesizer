#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "m_pd.h"

#define cbFactor 753
#define apFactor 2
#define l_CB0 9*cbFactor
#define l_CB1 13*cbFactor
#define l_CB2 11*cbFactor
#define l_CB3 17*cbFactor
#define l_AP0 525*apFactor
#define l_AP1 337*apFactor
#define l_AP2 113*apFactor

static t_class *gothom_tilde_class;

typedef struct combF0{
    t_sample cf_n_samps;       // delay in samples
    t_sample cf_coef;          // amount comb filter
    t_sample cf_buffer[l_CB0]; // ringbuffer
} t_combF0;

typedef struct combF1{
    t_sample cf_n_samps;       // delay in samples
    t_sample cf_coef;          // amount comb filter
    t_sample cf_buffer[l_CB1]; // ringbuffer
} t_combF1;

typedef struct combF2{
    t_sample cf_n_samps;       // delay in samples
    t_sample cf_coef;          // amount comb filter
    t_sample cf_buffer[l_CB2]; // ringbuffer
} t_combF2;

typedef struct combF3{
    t_sample cf_n_samps;       // delay in samples
    t_sample cf_coef;          // amount comb filter
    t_sample cf_buffer[l_CB3]; // ringbuffer
} t_combF3;

typedef struct allpassF0{
    t_sample ap_n_samps;       // delay in samples
    t_sample ap_coef;          // amount allpass
    t_sample ap_buffer[l_AP0]; // ringbuffer
} t_allpassF0;

typedef struct allpassF1{
    t_sample ap_n_samps;       // delay in samples
    t_sample ap_coef;          // amount allpass
    t_sample ap_buffer[l_AP1]; // ringbuffer
} t_allpassF1;

typedef struct allpassF2{
    t_sample ap_n_samps;        // delay in sample
    t_sample ap_coef;           // amount allpass
    t_sample ap_buffer[l_AP2];  // ringbuffer
} t_allpassF2;

/*
struct combF *createCombF(struct combF *c, t_sample samples, t_sample coef, int length){
    c = malloc( sizeof(*c) + sizeof(int) * length );
   // s = malloc( sizeof(*s) + sizeof(char) * strlen(a));
    c->cf_n_samps = samples;
    c->cf_coef = coef;
    c->length = length;
    return c;
    
}
*/
typedef struct _gothom_tilde {
    t_object    x_obj;     // is in every struct
    t_float     f;
    
    t_float     c_coef0;
    t_float     c_coef1;
    t_float     c_coef2;
    t_float     c_coef3;
        
    t_float     a_coef;
    
    t_combF0    x_cspace0;
    t_combF0    *x_ctl0;
    
    t_combF1    x_cspace1;
    t_combF1    *x_ctl1;
    
    t_combF2    x_cspace2;
    t_combF2    *x_ctl2;
    
    t_combF3    x_cspace3;
    t_combF3    *x_ctl3;
    
    t_allpassF0 x_aspace0;
    t_allpassF0 *x_atl0;
    
    t_allpassF1 x_aspace1;
    t_allpassF1 *x_atl1;
    
    t_allpassF2 x_aspace2;
    t_allpassF2 *x_atl2;
    
    t_sample    wet;
    
    int         z0, z1, z2, z3; // buffer counter cf
    int         a0, a1, a2;     // buffer counter ap
    
    t_inlet     *x_in2;     // coefCB0
    t_inlet     *x_in3;     // coefCB1
    t_inlet     *x_in4;     // coefCB2
    t_inlet     *x_in5;     // coefCB3
    t_inlet     *x_in6;     // coefAP
    t_inlet     *x_in7;     // wet
    
    t_outlet    *x_out;     // mono out
    
} t_gothom_tilde;


void *gothom_tilde_new(t_floatarg f)
{
    t_gothom_tilde *x = (t_gothom_tilde *)pd_new(gothom_tilde_class);
    
    x->x_ctl0 = &x->x_cspace0;
    x->x_ctl1 = &x->x_cspace1;
    x->x_ctl2 = &x->x_cspace2;
    x->x_ctl3 = &x->x_cspace3;
    
    x->x_atl0 = &x->x_aspace0;
    x->x_atl1 = &x->x_aspace1;
    x->x_atl2 = &x->x_aspace2;
    
    x->wet = 0.5;
    
    x->x_in2 = floatinlet_new (&x->x_obj, &x->c_coef0);  // combFcoef0 inlet
    x->x_in3 = floatinlet_new (&x->x_obj, &x->c_coef1);  // combFcoef1 inlet
    x->x_in4 = floatinlet_new (&x->x_obj, &x->c_coef2);  // combFcoef2 inlet
    x->x_in5 = floatinlet_new (&x->x_obj, &x->c_coef3);  // combFcoef3 inlet
    x->x_in6 = floatinlet_new (&x->x_obj, &x->a_coef);   // apCoef inlet
    x->x_in7 = floatinlet_new (&x->x_obj, &x->wet);      // wet/dry inlet
    x->x_out = outlet_new(&x->x_obj, &s_signal);         // signal outlet

    x->z0 = x->z1 = x->z2 = x->z3 = 0;
    x->a0 = x->a1 = x->a2 = 0;
    
    x->x_ctl0->cf_n_samps = l_CB0;  // comb buffer in samples
    x->x_ctl1->cf_n_samps = l_CB1;  // comb buffer in samples
    x->x_ctl2->cf_n_samps = l_CB2;  // comb buffer in samples
    x->x_ctl3->cf_n_samps = l_CB3;  // comb buffer in samples
    x->x_atl0->ap_n_samps = l_AP0;  // allpass buffer in samples
    x->x_atl1->ap_n_samps = l_AP1;  // allpass buffer in samples
    x->x_atl2->ap_n_samps = l_AP2;  // allpass buffer in samples
    
    return (void *)x;
}


t_int *gothom_tilde_perform(t_int *w)
{
    /*The perform-routine is the DSP-heart of each signal class.
    A pointer to an integer-array is passed to it. This array contains the pointers, that were passed via dsp_add, which must be cast back to their real type.
    The perform-routine has to return a pointer to integer, that points to the address behind the stored pointers of the routine. This means, that the return argument equals the argument of the perform-routine plus the number of pointer variables (as declared as the second argument of dsp_add) plus one.*/
  
    t_gothom_tilde *x   =    (t_gothom_tilde *)(w[1]);
    t_sample       *in1 =    (t_sample *)(w[2]);
    t_sample       *out =    (t_sample *)(w[3]);
    t_combF0       *cf0 =    (t_combF0 *)(w[4]);  //pointer to combF in gothom tilde obj
    t_combF1       *cf1 =    (t_combF1 *)(w[5]);
    t_combF2       *cf2 =    (t_combF2 *)(w[6]);
    t_combF3       *cf3 =    (t_combF3 *)(w[7]);
    t_allpassF0    *ap0 =    (t_allpassF0 *)(w[8]);
    t_allpassF1    *ap1 =    (t_allpassF1 *)(w[9]);
    t_allpassF2    *ap2 =    (t_allpassF2 *)(w[10]);
    int            n    =    (int)(w[11]);     // block size
    
    int length_buff0  = sizeof(cf0->cf_buffer)/sizeof(cf0->cf_buffer[0]);
    int length_buff1  = sizeof(cf1->cf_buffer)/sizeof(cf1->cf_buffer[0]);
    int length_buff2  = sizeof(cf2->cf_buffer)/sizeof(cf2->cf_buffer[0]);
    int length_buff3  = sizeof(cf3->cf_buffer)/sizeof(cf3->cf_buffer[0]);
    int length_buff0a = sizeof(ap0->ap_buffer)/sizeof(ap0->ap_buffer[0]);
    int length_buff1a = sizeof(ap1->ap_buffer)/sizeof(ap1->ap_buffer[0]);
    int length_buff2a = sizeof(ap2->ap_buffer)/sizeof(ap2->ap_buffer[0]);
    
    int i, z0, z1, z2, z3, n_s0, n_s1, n_s2, n_s3; //counter of blocksamples, counter of ringbuffer, difference between head and tail
    int a0, a1, a2, m_s0, m_s1, m_s2;
    
    n_s0 = x->x_cspace0.cf_n_samps; //number of samples behind z
    n_s0 = (n_s0<0)?0:(n_s0>length_buff0-1)?length_buff0-1:n_s0;
    
    n_s1 = x->x_cspace1.cf_n_samps; //number of samples behind z
    n_s1 = (n_s1<0)?0:(n_s1>length_buff1-1)?length_buff1-1:n_s1;
    
    n_s2 = x->x_cspace2.cf_n_samps; //number of samples behind z
    n_s2 = (n_s2<0)?0:(n_s2>length_buff2-1)?length_buff2-1:n_s2;
    
    n_s3 = x->x_cspace3.cf_n_samps; //number of samples behind z
    n_s3 = (n_s3<0)?0:(n_s3>length_buff3-1)?length_buff3-1:n_s3;
    
    m_s0 = x->x_aspace0.ap_n_samps; //number of samples behind a
    m_s0 = (m_s0<0)?0:(m_s0>length_buff0a-1)?length_buff0a-1:m_s0;
    
    m_s1 = x->x_aspace1.ap_n_samps; //number of samples behind a
    m_s1 = (m_s1<0)?0:(m_s1>length_buff1a-1)?length_buff1a-1:m_s1;
    
    m_s2 = x->x_aspace2.ap_n_samps; //number of samples behind a
    m_s2 = (m_s2<0)?0:(m_s2>length_buff2a-1)?length_buff2a-1:m_s2;

//t_sample coef = (x->coef_gothom<0)?0.0:(x->coef_gothom>0.99)?0.99:x->coef_gothom;
    t_sample c_coef0 = (x->c_coef0<0)?0.0:(x->c_coef0>0.99)?0.99:x->c_coef0;
    t_sample c_coef1 = (x->c_coef1<0)?0.0:(x->c_coef1>0.99)?0.99:x->c_coef1;
    t_sample c_coef2 = (x->c_coef2<0)?0.0:(x->c_coef2>0.99)?0.99:x->c_coef2;
    t_sample c_coef3 = (x->c_coef3<0)?0.0:(x->c_coef3>0.99)?0.99:x->c_coef3;
    t_sample a_coef0 = (x->a_coef<0)?0.0:(x->a_coef>0.99)?0.99:x->a_coef;
    t_sample a_coef1 = a_coef0;
    t_sample a_coef2 = a_coef0;
    t_sample wet = (x->wet<0)?0.0:(x->wet>0.99)?0.99:x->wet;
    
    for (i = 0; i < n; i++){
        
        t_sample buffer_actual0, buffer_actual1, buffer_actual2, buffer_actual3;
        t_sample buffer_actual0a, buffer_actual1a, buffer_actual2a;
        t_sample buffer_previous0, buffer_previous1, buffer_previous2, buffer_previous3;
        t_sample buffer_previous0a, buffer_previous1a, buffer_previous2a;
        t_sample ap_out0, ap_out1, ap_out2;
        
        z0 = x->z0;
        z1 = x->z1;
        z2 = x->z2;
        z3 = x->z3;
        a0 = x->a0;
        a1 = x->a1;
        a2 = x->a2;
        
        if (z0-n_s0>=0){
            buffer_previous0 = cf0->cf_buffer[z0-n_s0];
        }else {
            buffer_previous0 = cf0->cf_buffer[length_buff0+z0-n_s0];
        };
        
        if (z1-n_s1>=0){
            buffer_previous1 = cf1->cf_buffer[z1-n_s1];
        }else {
            buffer_previous1 = cf1->cf_buffer[length_buff1+z1-n_s1];
        };
        
        if (z2-n_s2>=0){
            buffer_previous2 = cf2->cf_buffer[z2-n_s2];
        }else {
            buffer_previous2 = cf2->cf_buffer[length_buff2+z2-n_s2];
        };
        
        if (z3-n_s3>=0){
            buffer_previous3 = cf3->cf_buffer[z3-n_s3];
        }else {
            buffer_previous3 = cf3->cf_buffer[length_buff3+z3-n_s3];
        };
        
        if (a0-m_s0>=0){
            buffer_previous0a = ap0->ap_buffer[a0-m_s0];
        }else {
            buffer_previous0a = ap0->ap_buffer[length_buff0a+a0-m_s0];
        };
        
        if (a1-m_s1>=0){
            buffer_previous1a = ap1->ap_buffer[a1-m_s1];
        }else {
            buffer_previous1a = ap1->ap_buffer[length_buff1a+a1-m_s1];
        };
        
        if (a2-m_s2>=0){
            buffer_previous2a = ap2->ap_buffer[a2-m_s2];
        }else {
            buffer_previous2a = ap2->ap_buffer[length_buff2a+a2-m_s2];
        };
        
        // allpass0
        buffer_actual0a = *in1 + (-1)*a_coef0 * buffer_previous0a;  //feedback ap0
        ap_out0 = buffer_actual0a *a_coef0 + buffer_previous0a;
        
        // allpass1
        buffer_actual1a = ap_out0 + (-1)*a_coef1 * buffer_previous1a;  //feedback ap1
        ap_out1 = buffer_actual1a *a_coef1 + buffer_previous1a;
        
        // allpass2
        buffer_actual2a = ap_out1 + (-1)*a_coef2 * buffer_previous2a;  //feedback ap2
        ap_out2 = buffer_actual2a *a_coef2 + buffer_previous2a;
        
        //ap_out0=*in1++; //test
        // parallel comb filters
        buffer_actual0 = buffer_actual1 = buffer_actual2 = buffer_actual3 = ap_out2; //change *in++ to ap_out2
        *out++ = wet*((buffer_actual0 + buffer_actual1 + buffer_actual2 + buffer_actual3 + c_coef0 * buffer_previous0 + c_coef1 * buffer_previous1 + c_coef2 * buffer_previous2 + c_coef3 * buffer_previous3)/4) + (1-wet)* *in1++;
        
        cf0->cf_buffer[z0] = buffer_actual0;
        cf1->cf_buffer[z1] = buffer_actual1;
        cf2->cf_buffer[z2] = buffer_actual2;
        cf3->cf_buffer[z3] = buffer_actual3;
        
        ap0->ap_buffer[a0] = buffer_actual0a;
        ap1->ap_buffer[a1] = buffer_actual1a;
        ap2->ap_buffer[a2] = buffer_actual2a;
        
        z0++;
        z1++;
        z2++;
        z3++;
        a0++;
        a1++;
        a2++;
        
        if (z0>length_buff0-1)
        z0 = 0;
        if (z1>length_buff1-1)
        z1 = 0;
        if (z2>length_buff2-1)
        z2 = 0;
        if (z3>length_buff3-1)
        z3 = 0;
        if (a0>length_buff0a-1)
        a0 = 0;
        if (a1>length_buff1a-1)
        a1 = 0;
        if (a2>length_buff2a-1)
        a2 = 0;
        
        x->z0 = z0;
        x->z1 = z1;
        x->z2 = z2;
        x->z3 = z3;
        x->a0 = a0;
        x->a1 = a1;
        x->a2 = a2;
}
    return (w+12);
}


void gothom_tilde_dsp(t_gothom_tilde *x, t_signal **sp)
{
    /*DSP-methods
    Whenever Pd’s audio engine is turned on, all signal-objects declare their perform-routines that are to be added to the DSP-tree.
     The “dsp”-method has two arguments, the pointer to the class-data space, and a pointer to an array of signals. The signal array consists of the input signals (from left to right) and then the output signals (from left to right).
         */
    
    dsp_add(gothom_tilde_perform, 11, x,
       sp[0]->s_vec, sp[1]->s_vec,x->x_ctl0, x->x_ctl1, x->x_ctl2, x->x_ctl3,x->x_atl0, x->x_atl1, x->x_atl2, sp[0]->s_n);
     }

void gothom_tilde_free(t_gothom_tilde *x)
     {
         /*If our object has some dynamically allocated resources (usually this is dynamically allocated memory), we must free them manually in the “free-method” (aka: destructor).*/
         
         inlet_free(x->x_in2);
         inlet_free(x->x_in3);
         inlet_free(x->x_in4);
         inlet_free(x->x_in5);
         inlet_free(x->x_in6);
         inlet_free(x->x_in7);
         outlet_free(x->x_out);
     }

void gothom_tilde_setup(void) {
    gothom_tilde_class = class_new(gensym("gothom~"),
    (t_newmethod)gothom_tilde_new,             //constructor
    (t_method)gothom_tilde_free,               //destructor to free up resources
    sizeof(t_gothom_tilde),
    CLASS_DEFAULT,
    A_DEFFLOAT, 0);
    
    class_addmethod(gothom_tilde_class,
            (t_method)gothom_tilde_dsp, gensym("dsp"), A_CANT, 0);
    CLASS_MAINSIGNALIN(gothom_tilde_class, t_gothom_tilde, f);          //Signal classes that want to provide signal-inlets have to declare this via the CLASS_MAINSIGNALIN-macro
     }
