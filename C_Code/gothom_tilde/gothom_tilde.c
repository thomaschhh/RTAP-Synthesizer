/**
 * @file gothom_tilde.c
 * @brief Source code of the Pd external "gothom~"
 *
 * This files contains both functions as well as structs.
 *
 * @author Tim-Tarek Grund
 * @author Gonzalo Gallo
 * @author Thomas Holz
 */

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

/**
 * preparing the class
 * delayerr_tilde_class is a pointer to the new class
 */
static t_class *gothom_tilde_class;

/**
 * @struct combF0
 * @brief A structure of combF0
 * @var combF0::t_samples cf_n_samps
 * @var combF0::t_sample cf_coef
 * @var combF0::t_sample cf_buffer
 * @var combF0::t_combF0
 */
typedef struct combF0{
    t_sample cf_n_samps;       /**< delay in samples */
    t_sample cf_coef;          /**< amount of comb filter */
    t_sample cf_buffer[l_CB0]; /**< ringbuffer */
} t_combF0;

/**
 * @struct combF1
 * @brief A structure of combF1
 * @var combF1::t_samples cf_n_samps
 * @var combF1::t_sample cf_coef
 * @var combF1::t_sample cf_buffer
 * @var combF1::t_combF1
 */
typedef struct combF1{
    t_sample cf_n_samps;       /**< delay in samples */
    t_sample cf_coef;          /**< amount of comb filter */
    t_sample cf_buffer[l_CB1]; /**< ringbuffer */
} t_combF1;

/**
 * @struct combF2
 * @brief A structure of combF2
 * @var combF2::t_samples cf_n_samps
 * @var combF2::t_sample cf_coef
 * @var combF2::t_sample cf_buffer
 * @var combF2::t_combF2
 */
typedef struct combF2{
    t_sample cf_n_samps;       /**< delay in samples */
    t_sample cf_coef;          /**< amount of comb filter */
    t_sample cf_buffer[l_CB2]; /**< ringbuffer */
} t_combF2;

/**
 * @struct combF3
 * @brief A structure of combF3
 * @var combF3::t_samples cf_n_samps
 * @var combF3::t_sample cf_coef
 * @var combF3::t_sample cf_buffer
 * @var combF3::t_combF3
 */
typedef struct combF3{
    t_sample cf_n_samps;       /**< delay in samples */
    t_sample cf_coef;          /**< amount of comb filter */
    t_sample cf_buffer[l_CB3]; /**< ringbuffer */
} t_combF3;

/**
 * @struct allpassF0
 * @brief A structure of allpassF0
 * @var allpassF0::t_samples ap_n_samps
 * @var allpassF0::t_sample ap_coef
 * @var allpassF0::t_sample ap_buffer
 * @var allpassF0::t_allpassF0
 */
typedef struct allpassF0{
    t_sample ap_n_samps;       /**< delay in samples */
    t_sample ap_coef;          /**< amount of all-pass filter */
    t_sample ap_buffer[l_AP0]; /**< ringbuffer */
} t_allpassF0;

/**
 * @struct allpassF1
 * @brief A structure of allpassF1
 * @var allpassF1::t_samples ap_n_samps
 * @var allpassF1::t_sample ap_coef
 * @var allpassF1::t_sample ap_buffer
 * @var allpassF1::t_allpassF1
 */
typedef struct allpassF1{
    t_sample ap_n_samps;       /**< delay in samples */
    t_sample ap_coef;          /**< amount of all-pass filter */
    t_sample ap_buffer[l_AP1]; /**< ringbuffer */
} t_allpassF1;

/**
 * @struct allpassF2
 * @brief A structure of allpassF2
 * @var allpassF2::t_samples ap_n_samps
 * @var allpassF2::t_sample ap_coef
 * @var allpassF2::t_sample ap_buffer
 * @var allpassF2::t_allpassF2
 */
typedef struct allpassF2{
    t_sample ap_n_samps;        /**< delay in samples */
    t_sample ap_coef;           /**< amount of all-pass filter */
    t_sample ap_buffer[l_AP2];  /**< ringbuffer */
} t_allpassF2;

/**
 * @struct _gothom_tilde
 * @brief A structure of _gothom_tilde
 * @var _gothom_tilde::t_object x_obj
 * @var _gothom_tilde::t_float f
 * @var _gothom_tilde::t_float c_coef0
 * @var _gothom_tilde::t_float c_coef1
 * @var _gothom_tilde::t_float c_coef2
 * @var _gothom_tilde::t_float c_coef3
 * @var _gothom_tilde::t_float a_coef
 * @var _gothom_tilde::t_combF0 x_cspace0
 * @var _gothom_tilde::t_combF0 *x_ctl0
 * @var _gothom_tilde::t_combF1 x_cspace1
 * @var _gothom_tilde::t_combF1 *x_ctl1
 * @var _gothom_tilde::t_combF2 x_cspace2
 * @var _gothom_tilde::t_combF2 *x_ctl2
 * @var _gothom_tilde::t_combF3 x_cspace3
 * @var _gothom_tilde::t_combF3 *x_ctl3
 * @var _gothom_tilde::t_allpassF0 x_aspace0
 * @var _gothom_tilde::t_allpassF0 *x_atl0
 * @var _gothom_tilde::t_allpassF1 x_aspace1
 * @var _gothom_tilde::t_allpassF1 *x_atl1
 * @var _gothom_tilde::t_allpassF2 x_aspace2
 * @var _gothom_tilde::t_allpassF2 *x_atl2
 * @var _gothom_tilde::t_sample wet
 * @var _gothom_tilde::t_inlet *x_in2
 * @var _gothom_tilde::t_inlet *x_in3
 * @var _gothom_tilde::t_inlet *x_in4
 * @var _gothom_tilde::t_inlet *x_in5
 * @var _gothom_tilde::t_inlet *x_in6
 * @var _gothom_tilde::t_inlet *x_in7
 * @var _gothom_tilde::t_outlet *x_out
 * @var _gothom_tilde::t_gothom_tilde
 */
typedef struct _gothom_tilde {
    t_object    x_obj;      /**< is used to store internal object-properties (mandatory)*/
    t_float     f;          /**< XXXXX*/
    
    t_float     c_coef0;    /**< amount of comb filter*/
    t_float     c_coef1;    /**< amount of comb filter*/
    t_float     c_coef2;    /**< amount of comb filter*/
    t_float     c_coef3;    /**< amount of comb filter*/
        
    t_float     a_coef;     /**< amount of all-pass filter*/
    
    t_combF0    x_cspace0;  /**< XXXXX*/
    t_combF0    *x_ctl0;    /**< XXXXX*/
    
    t_combF1    x_cspace1;  /**< XXXXX*/
    t_combF1    *x_ctl1;    /**< XXXXX*/
    
    t_combF2    x_cspace2;  /**< XXXXX*/
    t_combF2    *x_ctl2;    /**< XXXXX*/
        
    t_combF3    x_cspace3;  /**< XXXXX*/
    t_combF3    *x_ctl3;    /**< XXXXX*/
    
    t_allpassF0 x_aspace0;  /**< XXXXX*/
    t_allpassF0 *x_atl0;    /**< XXXXX*/
    
    t_allpassF1 x_aspace1;  /**< XXXXX*/
    t_allpassF1 *x_atl1;    /**< XXXXX*/
    
    t_allpassF2 x_aspace2;  /**< XXXXX*/
    t_allpassF2 *x_atl2;    /**< XXXXX*/
    
    t_sample    wet;        /**< amount of wet in signal */
    
    int         z0, z1, z2, z3; // buffer counter cf
    int         a0, a1, a2;     // buffer counter ap
    
    t_inlet     *x_in2;     /**< comb filter coeffeicient 1*/
    t_inlet     *x_in3;     /**< comb filter coeffeicient 2*/
    t_inlet     *x_in4;     /**< comb filter coeffeicient 3*/
    t_inlet     *x_in5;     /**< comb filter coeffeicient 4*/
    t_inlet     *x_in6;     /**< all-pass filter coeffeicients */
    t_inlet     *x_in7;     /**<  amount of wet in signal */
    
    t_outlet    *x_out;     /**< mono output*/
    
} t_gothom_tilde;


/**
 * @brief constructor of gothom
 * @param f XXXXX
 * @var gothom_tilde_new::x
 * @return void *x
 */
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
    
    x->wet = 0.5;   // initializing wet
    
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

/**
 * @brief gothom perform method <br>
 * @param w pointer to an integer-array
 * @var gothom_tilde_perform::t_delayerr_tilde *x
 * @var gothom_tilde_perform::t_sample *in
 * @var gothom_tilde_perform::t_sample *out
 * @var gothom_tilde_perform::t_combF0 *cf0
 * @var gothom_tilde_perform::t_combF1 *cf1
 * @var gothom_tilde_perform::t_combF2 *cf2
 * @var gothom_tilde_perform::t_combF3 *cf3
 * @var gothom_tilde_perform::t_allpassF0 *ap0
 * @var gothom_tilde_perform::t_allpassF1 *ap1
 * @var gothom_tilde_perform::t_allpassF2 *ap2
 */
t_int *gothom_tilde_perform(t_int *w)
{
    t_gothom_tilde *x   =    (t_gothom_tilde *)(w[1]);  /**< first element is a pointer to the dataspace of this object */
    t_sample       *in1 =    (t_sample *)(w[2]);        /**< pointer to the t_sample arrays that holds the input signal */
    t_sample       *out =    (t_sample *)(w[3]);        /**< pointer to the t_sample arrays that holds the output signal */
    t_combF0       *cf0 =    (t_combF0 *)(w[4]);        /**< pointer to comb filter 0 n gothom tilde object */
    t_combF1       *cf1 =    (t_combF1 *)(w[5]);        /**< pointer to comb filter 1 in gothom tilde object */
    t_combF2       *cf2 =    (t_combF2 *)(w[6]);        /**< pointer to comb filter 2 in gothom tilde object */
    t_combF3       *cf3 =    (t_combF3 *)(w[7]);        /**< pointer to comb filter 3 in gothom tilde object */
    t_allpassF0    *ap0 =    (t_allpassF0 *)(w[8]);     /**< pointer to all-pass filter 0 in gothom tilde object */
    t_allpassF1    *ap1 =    (t_allpassF1 *)(w[9]);     /**< pointer to all-pass filter 1 in gothom tilde object */
    t_allpassF2    *ap2 =    (t_allpassF2 *)(w[10]);    /**< pointer to all-pass filter 2 in gothom tilde object */
    int            n    =    (int)(w[11]);              // XXX block size
    
    int length_buff0  = sizeof(cf0->cf_buffer)/sizeof(cf0->cf_buffer[0]);  // XXXXX
    int length_buff1  = sizeof(cf1->cf_buffer)/sizeof(cf1->cf_buffer[0]);  // XXXXX
    int length_buff2  = sizeof(cf2->cf_buffer)/sizeof(cf2->cf_buffer[0]);  // XXXXX
    int length_buff3  = sizeof(cf3->cf_buffer)/sizeof(cf3->cf_buffer[0]);  // XXXXX
    int length_buff0a = sizeof(ap0->ap_buffer)/sizeof(ap0->ap_buffer[0]);  // XXXXX
    int length_buff1a = sizeof(ap1->ap_buffer)/sizeof(ap1->ap_buffer[0]);  // XXXXX
    int length_buff2a = sizeof(ap2->ap_buffer)/sizeof(ap2->ap_buffer[0]);  // XXXXX
    
    int i, z0, z1, z2, z3, n_s0, n_s1, n_s2, n_s3;  //counter of blocksamples, counter of ringbuffer, difference between head and tail
    int a0, a1, a2, m_s0, m_s1, m_s2;   // XXXXX
    
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

/**
 * @brief DSP method
 * @param x pointer to the class-data space
 * @param sp pointer to an array of signals
 */
void gothom_tilde_dsp(t_gothom_tilde *x, t_signal **sp)
    {
    dsp_add(gothom_tilde_perform, 11, x,
       sp[0]->s_vec, sp[1]->s_vec,x->x_ctl0, x->x_ctl1, x->x_ctl2, x->x_ctl3,x->x_atl0, x->x_atl1, x->x_atl2, sp[0]->s_n);
     }

/**
 * @brief destructor of gothom
 * @var gothom_tilde_free::x
 */
void gothom_tilde_free(t_gothom_tilde *x)
     {
         /* free any ressources associated with the given inlet */
         inlet_free(x->x_in2);
         inlet_free(x->x_in3);
         inlet_free(x->x_in4);
         inlet_free(x->x_in5);
         inlet_free(x->x_in6);
         inlet_free(x->x_in7);
         
         /* free any ressources associated with the given outlet */
         outlet_free(x->x_out);
     }

/**
 * @brief functions space of the class
 */
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
