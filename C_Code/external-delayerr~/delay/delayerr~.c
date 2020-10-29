/**
 * @file delayerr~.c
 * @brief Source code of the Pd external "delayerr~"
 *
 * This files contains both functions as well as structs.
 *
 * @author Tim-Tarek Grund
 * @author Gonzalo Gallo-Robador
 * @author Thomas Holz
 */

#include "m_pd.h"
#include "string.h"

/**
 * preparing the class
 * delayerr_tilde_class is a pointer to the new class
 */
static t_class *delayerr_tilde_class;

/**
 * @struct _delayerr_tilde
 * @brief A structure of _delayerr_tilde
 * @var _delayerr_tilde::t_object x_obj
 * @var _delayerr_tilde::t_float delay
 * @var _delayerr_tilde::t_float decay
 * @var _delayerr_tilde::t_float f_position
 * @var _delayerr_tilde::t_sample *f_vec
 * @var _delayerr_tilde::t_sample f
 * @var _delayerr_tilde::t_inlet *x_in2
 * @var _delayerr_tilde::t_inlet *x_in3
 * @var _delayerr_tilde::t_outlet *x_out
 * @var _delayerr_tilde::t_delayerr_tilde
 */
typedef struct _delayerr_tilde {
  t_object  x_obj;      /**< is used to store internal object-properties (mandatory)*/
  t_float f_delay;      /**< delay time in ms */
  t_float f_decay;      /**< decay factor */
  t_float f_position;   /**< used to cycle through the buffer */
  t_sample *f_vec;      /**< pointer to the beginning of the buffer vector */
  t_sample f;           /**< a dummy and is used to be able to send floats as signals */

  t_inlet *x_in2;       /**< pointer for storing handles to the extra inlet 2 */
  t_inlet *x_in3;       /**< pointer for storing handles to the extra inlet 3 */
  t_outlet*x_out;       /**< pointer for storing handles to the outlet */
} t_delayerr_tilde;     /**< structure t_delayerr_tilde is the data space of the class */

#define SR 44.1         // sample rate
#define MAX_DELAY 2000  // max delay time

/**
 * @brief delayerr perform method <br>
 * @param w integer array with that contains pointers to each signal in the signal array
 * @var delayerr_tilde_perform::t_delayerr_tilde *x
 * @var delayerr_tilde_perform::t_sample *in
 * @var delayerr_tilde_perform::t_sample *out
 * @var delayerr_tilde_perform::t_float f_delay
 * @var delayerr_tilde_perform::t_sample *mybuffer
 */
t_int *delayerr_tilde_perform(t_int *w)
{
  t_delayerr_tilde *x = (t_delayerr_tilde *)(w[1]);  /**< pointer to the dataspace of this object */
  t_sample *in  =    (t_sample *)(w[2]);             /**< pointer to the t_sample array that holds the input signal */
  t_sample *out =    (t_sample *)(w[3]);             /**< pointer to the t_sample array that holds the output signal */
  int      n    =    (int)(w[4]);                    /**< variable for getting the array length of the in and out arrays */
  t_float f_delay = (x->f_delay < 0) ? 0 : (x->f_delay > MAX_DELAY) ? MAX_DELAY : x->f_delay;  /**< variable for getting (and clipping) the delay time */
  t_float f_decay = (x->f_decay<0)?0.0:(x->f_decay>1)?1.0:x->f_decay;   /**< variable for getting (and clipping) the decay factor */

  int i;  /* a counter */

  t_sample *mybuffer = x->f_vec;    /**< variable for getting the pointer to the beginning of the buffer array */

  /* this is the main routine */
  for(i=0; i<n; i++)
    {
      // STORE-TO-PLAY: Mix sample with the one stored in the buffer at f_position
      out[i]=in[i] + f_decay*mybuffer[(int) x->f_position];
        
      // STORE-TO-BUFFER: Record this new value in the buffer at f_position
      mybuffer[(int) x->f_position] = out[i];
        
      // Increment buffer position wrapping around
      x->f_position = x->f_position + 1;
        
      // If f_position reaches the top of the buffer, we set it back to 0 again
      if(x->f_position >= (f_delay * SR)) x->f_position = 0;
    }

  /* return a pointer to the dataspace for the next dsp-object */
  return (w+5);
}


/**
 * @brief DSP method
 * @param x pointer to the class-data space
 * @param sp pointer to the signal array
 */
void delayerr_tilde_dsp(t_delayerr_tilde *x, t_signal **sp)
{
  /* add delayerr_tilde_perform() to the DSP-tree */
  dsp_add(delayerr_tilde_perform, 4, x,
          sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * @brief destructor of delayerr~
 * @var delayerr_tilde_free::x
 */
void delayerr_tilde_free(t_delayerr_tilde *x)
{
  /* free any ressources associated with the given inlet */
  inlet_free(x->x_in2);
  inlet_free(x->x_in3);

  /* free any ressources associated with the given outlet */
  outlet_free(x->x_out);

  /* free the allocated memory for the buffer*/
  freebytes(x->f_vec,
        (MAX_DELAY * SR) * sizeof(t_sample));
}

/**
 * @brief constructor of delayerr~
 * @param i_delay variable for the constructor-argument of the delay time
 * @param i_decay variable for the constructor-argument of the decay factor
 * @var delayerr_tilde_new::x
 * @return void *x
 */
void *delayerr_tilde_new(t_floatarg i_delay, t_floatarg i_decay)
{
  t_delayerr_tilde *x = (t_delayerr_tilde *)pd_new(delayerr_tilde_class);

  /* save the delay and decay in our dataspace */
  x->f_delay = i_delay;
  x->f_decay = i_decay;

  /* initialize f_position */
  x->f_position = 0;

  /* reserve memory for the buffer */
  x->f_vec = getbytes((MAX_DELAY * SR) * sizeof(t_sample));  // the delay time [ms] has to be converted to samples
  /* set every sample to 0 */
  memset(x->f_vec, 0, (MAX_DELAY * SR) * sizeof(t_sample));

  /* create a new passive inlet for the delay time */
  x->x_in2 = floatinlet_new (&x->x_obj, &x->f_delay);

  /* create a new passive inlet for the decay factor */
  x->x_in3 = floatinlet_new (&x->x_obj, &x->f_decay);

  /* create a new signal outlet */
  x->x_out = outlet_new(&x->x_obj, &s_signal);

  return (void *)x;
}


/**
 * @brief function space of the class
 */
void delayerr_tilde_setup(void) {
  delayerr_tilde_class = class_new(gensym("delayerr~"),
        (t_newmethod)delayerr_tilde_new,
        (t_method)delayerr_tilde_free,
    sizeof(t_delayerr_tilde),
        CLASS_DEFAULT,
        A_DEFFLOAT, A_DEFFLOAT, 0);

  /* whenever the audio-engine is turned on, the "delayerr_tilde_dsp()"
   * function will get called
   */
  class_addmethod(delayerr_tilde_class,
        (t_method)delayerr_tilde_dsp, gensym("dsp"), 0);
  /* if no signal is connected to the first inlet, we can as well
   * connect a number box to it and use it as "signal"
   */
  CLASS_MAINSIGNALIN(delayerr_tilde_class, t_delayerr_tilde, f);
}
