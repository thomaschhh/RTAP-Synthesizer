# Read Me

This synthesizer was created in the 2nd in the class Real-time Audio Programming in C. 

The task consisted of creating a PD patch and writing an external for it in C. 

After we had decided to develop a synthesizer and create an app for the iPad, we found the option to use [TouchOSC](https://hexler.net/docs/touchosc-getting-started). 
We implemented our own PD patch into an already existing [basic.pd](https://hexler.net/pub/touchosc/basic.pd) and found out that we had to work with [purr-data](https://agraef.github.io/purr-data/) instead of PureData Vanilla. The reason for this is the fact we actually needed Pd-extended for OSC to work but that is no longer supported.

## Course Material

Here you can find all the materials related to the class: [class git](https://github.com/audio-communication-group/real-time-audio-programming-in-C_SoSe2020.git).

