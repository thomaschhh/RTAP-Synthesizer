/**
 * @file envelope1.c
 * @brief Source code of the Pd external "envelope1"
 *
 * This files contains both functions as well as structs.
 *
 * @author Tim-Tarek Grund
 * @author Gonzalo Gallo
 * @author Thomas Holz
 */

/* -- Includes -- */
#include <stdio.h>
#include <stdbool.h>
#include "m_pd.h"  /* -- including the interface -- */
#include <math.h>

/**
 * preparing the class
 * envelope1_class is a pointer to the new class
 */
static t_class *envelope1_class;

/**
 * @struct _envelope1
 * @brief A structure of _envelope1
 * @var _envelope1::t_object x_obj
 * @var _envelope1::t_float attack
 * @var _envelope1::t_float decay
 * @var _envelope1::t_float sustain
 * @var _envelope1::t_float release
 // @var _envelope1::t_float mode
 * @var _envelope1::t_float exp_setting
 * @var _envelope1::t_symbol *x_arrayname
 // @var _envelope1::t_word *x_vec
 * @var _envelope1::t_inlet *x_in1
 * @var _envelope1::t_inlet *x_in2
 * @var _envelope1::t_inlet *x_in3
 * @var _envelope1::t_inlet *x_in4
 * @var _envelope1::t_inlet *x_in5
 // @var _envelope1::t_inlet *x_in6
 // @var _envelope1::t_outlet *f_out
 * @var _envelope1::t_envelope1
 */
typedef struct _envelope1 { //data space definition
    t_object  x_obj;    /**< is used to store internal object-properties (mandatory)*/
    t_float attack;     /**< >0 in ms */
    t_float decay;      /**< >=0 in ms */
    t_float sustain;    /**< 1 - 0 */
    t_float release;    /**< >0 in ms*/
    
    t_float exp_setting;/**<  curvature of attack*/
    t_symbol *x_arrayname;      /**< save array name*/
    
    
    t_inlet *x_in1;     /**< pointer for the inlet 1 (attack) */
    t_inlet *x_in2;     /**< pointer for the inlet 2 (decay) */
    t_inlet *x_in3;     /**< pointer for the inlet 3 (sustain) */
    t_inlet *x_in4;     /**< pointer for the inlet 4 (release) */
    t_inlet *x_in5;     /**< pointer for the inlet 5 (exp_setting) */
    
    
    
} t_envelope1;

//method space
/**
 * @brief Envelope bang<br>
 * @param x data space as argument, COULD manipulate dataspace
 * @var envelope1_bang::t_float attack_ms
 * @var envelope1_bang::t_float decay_ms
 * @var envelope1_bang::t_float sustain
 * @var envelope1_bang::t_float release_ms
 * @var envelope1_bang::t_float curve_factor
 */
void envelope1_bang(t_envelope1 *x) //has data space as argument, COULD manipulate dataspace
{
    t_float attack_ms = x->attack;              /**< reads attack value from pointer x */
    t_float decay_ms = x->decay;                /**<  reads decay value from pointer x */
    t_float sustain = x->sustain;               /**<  reads sustain value from pointer x */
    t_float release_ms = x->release;            /**<  reads release value from pointer x */
    t_float curve_faktor = x->exp_setting;      /**<  reads exp setting value from pointer x, faktor = 1 -> linear, faktor > 1 -> exponential */
    
    // cutting off a higher sustain than 1
    if (sustain >1){
        sustain = 1;
    }else if (sustain<0){
        sustain = 0;
    };
    
    t_float sr = 10000;                                 /**< internal samplerate  */
    t_float attack_sp = sr/1000 * attack_ms;            /**< attack in number of samples  */
    t_float decay_sp = sr/1000 * decay_ms;              /**< decay in number of samples  */
    t_float release_sp = sr/1000 * release_ms;          /**< release in number of samples  */
    t_float length = attack_sp + decay_sp + release_sp; /**< total length of array in samples  */
    
    int vecsize;    /**< size of vector or array  */
    t_garray *a;    /**< an array  */
    t_word *vec;    /**< pointer to the vector */

    //below: error handler from tabread_float: https://github.com/pure-data/pure-data/blob/master/src/d_array.c
    
    if (!(a = (t_garray *)pd_findbyclass(x->x_arrayname, garray_class)))
        pd_error(x, "%s: no such array", x->x_arrayname->s_name); // error if no array
    else if (!garray_getfloatwords(a, &vecsize, &vec))
        pd_error(x, "%s: bad template for tabwrite", x->x_arrayname->s_name); // error
    else if (length == 0){
        printf("length = 0!!!");
    }else
    {
    
        garray_resize_long(a, (long)length);   // changes the size of the arrays
        
        
        int n = 0;
        if (curve_faktor < 1){           // if exp setting 1 -> linear attack
            for (n = 0; n < attack_sp; n++){
                vec[n].w_float = ((1/attack_sp) * n) ;
        }
        }else if (curve_faktor > 1){     // if exp setting > 1 -> exp attack
            for (n = 0; n < attack_sp; n++){
                    vec[n].w_float = (pow(curve_faktor,((2/attack_sp)*n))-1)/(pow(curve_faktor,2)-1);
            }
        };
        for (n = attack_sp; n < attack_sp + decay_sp; n++){ // modelling the decay
        
            int j = n - attack_sp;
            vec[n].w_float = 1-((1-sustain)/decay_sp)*j;
        };
        for (n = attack_sp + decay_sp; n < length; n++){ // modelling the release
        
            int k = n - attack_sp - decay_sp;
            vec[n].w_float = sustain - (sustain/release_sp)*k;
        };
        garray_redraw(a);           // redraw array
        
    }
    
}

/**
 * @brief new envelope
 * @param s array_name
 * @var envelope1_new::x
 * @return void *x
 */
void *envelope1_new(t_symbol *s)
{
    t_envelope1 *x = (t_envelope1 *)pd_new(envelope1_class);
    
    // initializing the parameter
    
    x->x_arrayname = s;
    x->attack=20;
    x->decay=0.5;
    x->sustain=30;
    x->release=600;
    x->exp_setting=0;
    floatinlet_new(&x->x_obj, &x->attack);
    floatinlet_new(&x->x_obj, &x->decay);
    floatinlet_new(&x->x_obj, &x->sustain);
    floatinlet_new(&x->x_obj, &x->release);
    
    floatinlet_new(&x->x_obj, &x->exp_setting);
    
    
 
    
  return (void *)x;
}


/**
 * @brief functions space of the class
 */
void envelope1_setup(void) { //generation of a new class
    envelope1_class = class_new(gensym("envelope1"), /* the object's name is "envelope1", class_new creates new class and returns pointer, name in gensym needs to be the one called in pd */
        (t_newmethod)envelope1_new, /* the object's constructor is "envelope1_new()" */
        0,                          /* no special destructor */
        sizeof(t_envelope1),        /* the size of the data structure */
        CLASS_DEFAULT,              /* a normal pd object, graphical representation of object */
        
        A_DEFSYMBOL,                /* symbolic object argument */
                                    //no arguments need to be passed at creation time
        0);                         /* placeholder for something, zero ends argument list */
    class_addbang(envelope1_class, envelope1_bang); //add method space to class
    
    
}
