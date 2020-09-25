/**
 * @file envelope1.c
 * @brief Source code of the Pd external "envelope1"
 *
 * This files contains both functions as well as structs.
 *
 * @author Tim-Tarek Grund
 * @author Gonzalo Gallo
 * @author Thomas Holz
 * @bug No known bugs.
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
 * @var _envelope1::t_float releae
 * @var _envelope1::t_float mode
 * @var _envelope1::t_float exp_setting
 * @var _envelope1::t_symbol *x_arrayname
 * @var _envelope1::t_word *x_vec
 * @var _envelope1::t_inlet *x_in1
 * @var _envelope1::t_inlet *x_in2
 * @var _envelope1::t_inlet *x_in3
 * @var _envelope1::t_inlet *x_in4
 * @var _envelope1::t_inlet *x_in5
 * @var _envelope1::t_inlet *x_in6
 * @var _envelope1::t_outlet *f_out
 * @var _envelope1::t_envelope1
 */
typedef struct _envelope1 { //data space definition
    t_object  x_obj;    /**< necessary variable, needs to be FIRST */
    t_float attack;     /**< >0 in ms */
    t_float decay;      /**< >=0 in ms */
    t_float sustain;    /**< 1 - 0 */
    t_float release;    /**< >0 in ms*/
    t_float mode;       /**<  1 = ar, 2 = adsr, 3 = adshr*/
    t_float exp_setting;/**<  curvature of attack*/
    t_symbol *x_arrayname;      /**< save array name*/
    t_word *x_vec;              /**< vector*/
    
    t_inlet *x_in1;     /**< XXXXXX */
    t_inlet *x_in2;     /**< XXXXXX */
    t_inlet *x_in3;     /**< XXXXXX */
    t_inlet *x_in4;     /**< XXXXXX */
    t_inlet *x_in5;     /**< XXXXXX */
    t_inlet *x_in6;     /**< XXXXXX */
    
    t_outlet *f_out, *b_out;    /**< XXXXXX f_out comment is missing*/
    
} t_envelope1; /**< structure t_envelope is the data space of the class */

//method space
/**
 * @brief Envelope bang<br>
 * @param x data space as argument, COULD manipulate dataspace
 * @var envelope1_bang::t_float f1
 * @var envelope1_bang::t_float f2
 * @var envelope1_bang::t_float f3
 * @var envelope1_bang::t_float f4
 * @var envelope1_bang::t_float faktor
 */
void envelope1_bang(t_envelope1 *x) //has data space as argument, COULD manipulate dataspace
{
    t_float f1 = x->attack;     /**< XXXXXX */
    t_float f2 = x->decay;      /**< XXXXXX */
    t_float f3 = x->sustain;    /**< XXXXXX */
    t_float f4 = x->release;    /**< XXXXXX */
    t_float faktor = x->exp_setting;      /**< faktor = 1 -> linear, faktor > 1 -> exponential */
    
    // cutting off a higher sustain than 1
    if (f3 >1){
        f3 = 1;
    }else if (f3<0){
        f3 = 0;
    };
    
    //post(" T15: A = %f, D = %f, S = %f, R = %f, E = %f ", f1, f2, f3, f4, f5);
    
    t_float sr = 10000; //samplerate
    t_float a_sp = sr/1000 * f1;
    t_float d_sp = sr/1000 * f2;
    t_float r_sp = sr/1000 * f4;
    t_float length = a_sp + d_sp + r_sp;
    
    int vecsize;    // size of vector or array
    t_garray *a;    // an array
    t_word *vec;    //

    if (!(a = (t_garray *)pd_findbyclass(x->x_arrayname, garray_class)))
        pd_error(x, "%s: no such array", x->x_arrayname->s_name); // error if no array
    else if (!garray_getfloatwords(a, &vecsize, &vec))
        pd_error(x, "%s: bad template for tabwrite", x->x_arrayname->s_name); // error
    else
    {
        garray_resize(a, length);   // changes the size of the arrays
        
        int n = 0;
        if (faktor < 1){           // if exp setting 1 -> linear attack
            for (n = 0; n < a_sp; n++){
                vec[n].w_float = ((1/a_sp) * n) ;
        }
        }else if (faktor > 1){     // if exp setting > 1 -> exp attack
            for (n = 0; n < a_sp; n++){
                    vec[n].w_float = (pow(faktor,((2/a_sp)*n))-1)/(pow(faktor,2)-1);
            }
        };
        for (n = a_sp; n < a_sp + d_sp; n++){ // modelling the decay
        
            int j = n - a_sp;
            vec[n].w_float = 1-((1-f3)/d_sp)*j;
        };
        for (n = a_sp + d_sp; n < length; n++){ // modelling the release
        
            int k = n - a_sp - d_sp;
            vec[n].w_float = f3 - (f3/r_sp)*k;
        };
        garray_redraw(a);           // redraw array
    }
    //outlet_float(x->f_out, length);
}

/**
 * @brief new envelope
 * @param s XXXX
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
    floatinlet_new(&x->x_obj, &x->mode);
    floatinlet_new(&x->x_obj, &x->exp_setting);
    
    x->f_out = outlet_new(&x->x_obj, &s_float);
    x->b_out = outlet_new(&x->x_obj, &s_bang);
    
  return (void *)x;
}



void envelope1_setup(void) { //generation of a new class
    envelope1_class = class_new(gensym("envelope1"), //class_new creates new class and returns pointer, name in gensym needs to be the one called in pd
        (t_newmethod)envelope1_new, //constructor
        0,                          //empty destructor
        sizeof(t_envelope1),        //pass the size of datastructure
        CLASS_DEFAULT,              //graphical representation of object
        //A_DEFFLOAT,               //numeric object argument
        A_DEFSYMBOL,                //symbolic object argument
                                    //no arguments need to be passed at creation time
        0);                         //zero ends argument list
    class_addbang(envelope1_class, envelope1_bang); //add method space to class
    //class_addfloat(envelope1_class, (t_method)tabwrite_float); // aus tabwrite
    
}
