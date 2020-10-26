// TODO. Improve the code description (?)
/**
 * include the interface to Pd 
 */
#include "m_pd.h"
#include "string.h"


/**
 * define a new "class" 
 */
static t_class *delayerr_tilde_class;


/**
 * this is the dataspace of our new object
 * the first element is the mandatory "t_object"
 * f_delay is the delay time [ms]
 * f_decay is the decay factor
 * position will be used to cycle through the buffer
 * *f_vec is a pointer to the beginning of the buffer vector
 * "f" is a dummy and is used to be able to send floats AS signals.
 */
typedef struct _delayerr_tilde {
  t_object  x_obj;
  // TODO. I will choose int and float type for this variables, but it may not be right. t_int ?
  int f_delay;
  t_float f_decay;
  int f_position;     
  t_sample *f_vec;
  t_sample f;

  t_inlet *x_in2;
  t_inlet *x_in3;
  t_outlet*x_out;
} t_delayerr_tilde;

// TODO. Is this OK?
#define SR 44.1

/**
 * this is the core of the object
 * this perform-routine is called for each signal block
 * the name of this function is arbitrary and is registered to Pd in the 
 * delayerr_tilde_dsp() function, each time the DSP is turned on
 *
 * the argument to this function is just a pointer within an array
 * we have to know for ourselves how many elements inthis array are
 * reserved for us (hint: we declare the number of used elements in the
 * delayerr_tilde_dsp() at registration
 *
 * since all elements are of type "t_int" we have to cast them to whatever
 * we think is apropriate; "apropriate" is how we registered this function
 * in delayerr_tilde_dsp()
 */
t_int *delayerr_tilde_perform(t_int *w)
{
  /* the first element is a pointer to the dataspace of this object */
  t_delayerr_tilde *x = (t_delayerr_tilde *)(w[1]);
  /* here is a pointer to the t_sample arrays that hold the input signal */
  t_sample  *in =    (t_sample *)(w[2]);
  /* here comes the signalblock that will hold the output signal */
  t_sample  *out =    (t_sample *)(w[3]);
  /* all signalblocks are of the same length */
  int          n =           (int)(w[4]);

 /* get (and clip) the delay time */  
  int f_delay = x->f_delay;
  if (f_delay<0) f_delay = 0;
  
  /* get (and clip) the decay factor */
  t_float f_decay = (x->f_decay<0)?0.0:(x->f_decay>1)?1.0:x->f_decay;


  /* just a counter */
  int i;

  /* save the pointer to the beginning of buffer vector to an intern variable */
  t_sample *mybuffer = x->f_vec;

  /* this is the main routine: 
   * mix the current buffer with the delay-buffer multiplicated by the decay factor,
   * and store the mix in the delay-buffer again.
   */
  for(i=0; i<n; i++)
    {
      // PLAY: Mix sample with the one stored in the buffer at position
      out[i]=in[i] + f_decay*mybuffer[x->f_position];

      // STORE: Record this new value in the buffer at "position"
      mybuffer[x->f_position] = out[i];
      // Increment buffer position wrapping around
      x->f_position = x->f_position + 1;
      // This line means: if(position >= size) position = 0;
      if(x->f_position >= (x->f_delay * SR)) x->f_position = 0;
    }

  /* return a pointer to the dataspace for the next dsp-object */
  return (w+5);
}


/**
 * register a special perform-routine at the dsp-engine
 * this function gets called whenever the DSP is turned ON
 * the name of this function is registered in delayerr_tilde_setup()
 */
void delayerr_tilde_dsp(t_delayerr_tilde *x, t_signal **sp)
{
  /* add delayerr_tilde_perform() to the DSP-tree;
   * the delayerr_tilde_perform() will expect "4" arguments (packed into an
   * t_int-array), which are:
   * the objects data-space, 2 signal vectors (which happen to be
   * 1 input signal and 1 output signal) and the length of the
   * signal vectors (all vectors are of the same length)
   */
   /* TODO. Maybe I should also register the buffer  */
  dsp_add(delayerr_tilde_perform, 4, x,
          sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

/**
 * this is the "destructor" of the class;
 * it allows us to free dynamically allocated ressources
 */
void delayerr_tilde_free(t_delayerr_tilde *x)
{
  /* free any ressources associated with the given inlet */
  inlet_free(x->x_in2);
  inlet_free(x->x_in3);

  /* free any ressources associated with the given outlet */
  outlet_free(x->x_out);

  /* free the */
  freebytes(x->f_vec,
        (x->f_delay * SR) * sizeof(t_sample));
}

/**
 * this is the "constructor" of the class
 * TODO. what happens when no argument is given? I think nothing, but who knows
 * arguments:
 * 1. initial delay time [ms]
 * 2. decay factor
 */
void *delayerr_tilde_new(t_floatarg i_delay, t_floatarg i_decay)
{
  t_delayerr_tilde *x = (t_delayerr_tilde *)pd_new(delayerr_tilde_class);

  /* save the delay and decay in our dataspace */
  x->f_delay = (int) i_delay;
  x->f_decay = i_decay;

  /* initialize f_position */
  x->f_position = 0;

  /* reserve memory for the buffer and set every sample to 0 */
  /* f_delay [ms] has to be converted to samples */
  x->f_vec = getbytes((x->f_delay * SR) * sizeof(t_sample));
  memset(x->f_vec, 0, (x->f_delay * SR) * sizeof(t_sample));

  /* create a new passive inlet for the delay time */
  x->x_in2 = floatinlet_new (&x->x_obj, &x->f_delay);

  /* create a new passive inlet for the decay factor */
  x->x_in3 = floatinlet_new (&x->x_obj, &x->f_decay);

  /* create a new signal-outlet */
  x->x_out = outlet_new(&x->x_obj, &s_signal);

  return (void *)x;
}


/**
 * define the function-space of the class
 * within a single-object external the name of this function is very special
 */
// TODO. I added a second A_DEFFLOAT. I hope it's right.
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