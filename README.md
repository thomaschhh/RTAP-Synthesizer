# Shimmer Synth

This synthesizer was created in the 2nd semester of 2020 in the class [Real-time Audio Programming in C](https://github.com/audio-communication-group/real-time-audio-programming-in-C_SoSe2020.git).

The task consisted of creating a Pure Data patch and writing an external for it in C. 

After we had decided to develop a synthesizer and create an app for the iPad, we found the option to use [TouchOSC](https://hexler.net/docs/touchosc-getting-started). 
We implemented our own Pd patch into the already existing [basic.pd](https://hexler.net/pub/touchosc/basic.pd) patch and found out that we had to work with [purr-data](https://agraef.github.io/purr-data/) instead of [Pd Vanilla](http://puredata.info/downloads/pure-data). The reason for this was the fact we actually needed [Pd-Extended](http://puredata.info/downloads/pd-extended) for OSC to work which is no longer supported.

## Course Material

Here you can find all the materials related to the [class](https://github.com/audio-communication-group/real-time-audio-programming-in-C_SoSe2020.git).

