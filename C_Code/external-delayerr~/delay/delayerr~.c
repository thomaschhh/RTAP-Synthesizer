/**
 * include the interface to Pd and the string library. The latter will
 * let us use the "memset" function
 */
#include "m_pd.h"
#include "string.h"

/**
 * define a new class
 */
static t_class *delayerr_tilde_class;

/**
 * this is the dataspace of our new object
 * the first element is the mandatory t_object
 * f_delay is the delay time [ms]
 * f_decay is the decay factor
 * f_position will be used to cycle through the buffer
 * *f_vec is a pointer to the beginning of the buffer vector
 * f is a dummy and is used to be able to send floats AS signals.
 */
typedef struct _delayerr_tilde {
  t_object  x_obj;
  t_float f_delay;
  t_float f_decay;
  t_float f_position;
  t_sample *f_vec;
  t_sample f;

  t_inlet *x_in2;
  t_inlet *x_in3;
  t_outlet*x_out;
} t_delayerr_tilde;

/* define sample rate and maximal delay time*/
#define SR 44.1
#define MAX_DELAY 2000


/**
 * this is the perform routine
 */
t_int *delayerr_tilde_perform(t_int *w)
{
  /* the first element is a pointer to the dataspace of this object */
  t_delayerr_tilde *x = (t_delayerr_tilde *)(w[1]);
  /* here is a pointer to the t_sample arrays that holds the input signal */
  t_sample  *in =    (t_sample *)(w[2]);
  /* here is a pointer to the t_sample arrays that holds the output signal */
  t_sample  *out =    (t_sample *)(w[3]);
  /* the in and out arrays a have the same length */
  int          n =           (int)(w[4]);

 /* get (and clip) the delay time */
  t_float f_delay = (x->f_delay < 0) ? 0 : (x->f_delay > MAX_DELAY) ? MAX_DELAY : x->f_delay;
  
  /* get (and clip) the decay factor */
  t_float f_decay = (x->f_decay<0)?0.0:(x->f_decay>1)?1.0:x->f_decay;

  /* just a counter */
  int i;

  /* save the pointer to the beginning of buffer vector to an intern variable */
  t_sample *mybuffer = x->f_vec;

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
 * this is the DSP method
 * */
void delayerr_tilde_dsp(t_delayerr_tilde *x, t_signal **sp)
{
  /* add delayerr_tilde_perform() to the DSP-tree */
  dsp_add(delayerr_tilde_perform, 4, x,
          sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * this is the "destructor" of the class
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
 * this is the "constructor" of the class
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
 * this is the function-space of the class
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
