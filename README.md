# Shimmer Synth

This synthesizer was created in the 2nd semester of 2020 as a final project in the class [Real-time Audio Programming in C](https://github.com/audio-communication-group/real-time-audio-programming-in-C_SoSe2020.git). The task consisted of creating a Pure Data patch and writing an external for it in C. 

After we had decided to develop a synthesizer and create an app for the iPad, we found the option to use [TouchOSC](https://hexler.net/docs/touchosc-getting-started). 
We implemented our own Pd patch into the already existing [basic.pd](https://hexler.net/pub/touchosc/basic.pd) patch and found out that we had to work with [purr-data](https://agraef.github.io/purr-data/) instead of [Pd Vanilla](http://puredata.info/downloads/pure-data). The reason for this was the fact that we actually needed [Pd-Extended](http://puredata.info/downloads/pd-extended) for OSC to work which is no longer supported.

***

### Steps to Get The Synth Running

- Start **purr-data** and open the file [synth.pd](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/PureData/Synth.pd).

![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/pd_patch.png?raw=true)

- Load and open the **TouchOSC** app on your iPad.
![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/osc_layout.jpg?raw=true)
    - Look for the network settings (*Connections* --> *OSC: HOST IP*).
    - Type in your PC's IP address (*Host*).
    
![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/osc_connections.jpg?raw=true)

- Port 8000 is used in the *dumpOSC* box in Pd. 
- Port 9000 is used int the *connect* box in Pd.
- In the **synth.pd patch**, type in the iPad's IP address (*local IP address*) inside the *connect message box* (**1**).
    - Click the *connect* message box in order to connect to the iPad.
    - Adjust the attack, decay, sustain, release sliders to your liking (**2**).
    - Do the same thing with the Fundamentals (**3**) as well as its Shimmer Strength / Shimmer Frequency (**4**).
    - Select the desired waveform (**5**), adjust the volume (**6**) and turn on the dsp (**7**). 
    - Now you're ready to play. 
    
***
    
### Bugs

- The Pd patch randomly chrashes when adjusting the envelope.
