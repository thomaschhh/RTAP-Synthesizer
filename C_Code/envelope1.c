//
//  envelope1.c
//  envelope1
//
//  Created by Tim-Tarek Grund on 28.08.20.
//  Copyright © 2020 Tim-Tarek Grund. All rights reserved.
// test
/**
 * Detailed DESCRIPTION
 */

/**
 * @file envelope1.c
 * @author Tim-Tarek Grund, Gonzalo Gallo, Thomas Holz
 */

#include <stdio.h>
#include <stdbool.h>
#include "m_pd.h"  //including the inrterface
#include <math.h>

static t_class *envelope1_class; //preparing the class
//envelope1_class is a pointer to the new class

/**
 * @struct _envelope1
 * @brief A structure of _envelope1
 * @var _envelope1::t_float attack
 * @var _envelope1::t_float decay
 * @var _envelope1::t_float sustain
 * @var _envelope1::t_float releae
 * @var _envelope1::t_float mode
 */
typedef struct _envelope1 { //data space definition
    t_object  x_obj;    //necessary variable, needs to be FIRST
    t_float attack;     /**< >0, in ms */
    t_float decay;      // >=0 in ms
    t_float sustain;    // 1-0
    t_float release;    // >0 in ms
    t_float mode;       // 1 = ar, 2 = adsr, 3 = adshr
    t_float exp_setting;// curvature of attack
    t_symbol *x_arrayname;      //arrayname speichern
    t_word *x_vec;              //vector
    
    
    t_inlet *x_in1;
    t_inlet *x_in2;
    t_inlet *x_in3;
    t_inlet *x_in4;
    t_inlet *x_in5;
    t_inlet *x_in6;
    
    
    t_outlet *f_out, *b_out;
} t_envelope1; //structure t_envelope is the data space of the class

//method space
/**
 * @related _envelope1
 * @brief Envelope bang<br>
 * @param x A pointer to the object, input and output vectors. <br>
 */
void envelope1_bang(t_envelope1 *x) //has data space as argument, COULD manipulate dataspace
{
    t_float f1 = x->attack;
    t_float f2 = x->decay;
    t_float f3 = x->sustain;
    t_float f4 = x->release;
    t_float faktor = x->exp_setting;        // faktor = 1 -> linear, faktor > 1 -> exponential
    
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
    
    int vecsize;    //groeße vector oder array
    t_garray *a;    //ein array
    t_word *vec;    //

    if (!(a = (t_garray *)pd_findbyclass(x->x_arrayname, garray_class)))
        pd_error(x, "%s: no such array", x->x_arrayname->s_name); // Fehlermeldung wenn kein array
    else if (!garray_getfloatwords(a, &vecsize, &vec))
        pd_error(x, "%s: bad template for tabwrite", x->x_arrayname->s_name); // Fehlermeldung
    else
    {
        garray_resize(a, length);   // ändert größe des arrays
        
        int n = 0;
        if (faktor < 1){           // wenn exp setting 1 -> linear attack
            for (n = 0; n < a_sp; n++){
                vec[n].w_float = ((1/a_sp) * n) ;
        }
        }else if (faktor > 1){     // wenn exp setting > 1 -> exp attack
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
        garray_redraw(a);           // array neu malen
        
    }
    //outlet_float(x->f_out, length);
    
    
}




void *envelope1_new(t_symbol *s)
{
    t_envelope1 *x = (t_envelope1 *)pd_new(envelope1_class);
    
    // initialisieren der parameter
    
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
        A_DEFSYMBOL,               //symbolic object argument
                              //no arguments need to be passed at creation time
        0);                         //zero ends argument list
    class_addbang(envelope1_class, envelope1_bang); //add method space to class
    //class_addfloat(envelope1_class, (t_method)tabwrite_float); // aus tabwrite
    
}
