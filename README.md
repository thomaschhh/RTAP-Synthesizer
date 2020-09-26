# Shimmer Synth

This synthesizer was created in the 2nd semester of 2020 as a final project in the class [Real-time Audio Programming in C](https://github.com/audio-communication-group/real-time-audio-programming-in-C_SoSe2020.git). The task consisted of creating a Pure Data patch and writing an external for it in C. 

After we had decided to develop a synthesizer and create an app for the iPad, we found the option to use [TouchOSC](https://hexler.net/docs/touchosc-getting-started). 
We implemented our own Pd patch into the already existing [basic.pd](https://hexler.net/pub/touchosc/basic.pd) patch and found out that we had to work with [purr-data](https://agraef.github.io/purr-data/) instead of [Pd Vanilla](http://puredata.info/downloads/pure-data). The reason for this was the fact we actually needed [Pd-Extended](http://puredata.info/downloads/pd-extended) for OSC to work which is no longer supported.

![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/pd_patch.png?raw=true)

***

### Steps to Get The Synth Running

- Start purr-data and open the file [synth.pd](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/PureData/Synth.pd).
- Load and open the TouchOSC app on your iPad.
    - Look for the network settings.
    - Type in your PC's IP-address.
    ![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/osc_connections.png?raw=true)
- In the synth.pd patch, type in the iPad's IP-address.
    - Click the connect message box.
    - Adjust the attack, decay, sustain, release sliders to your liking.
    ![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/envelope.png?raw=true)
    - Do the same thing with the fundamentals, its Shimmer Strength, Shimmer Frequency as well as the master (gain)
    - Finally, turn on the dsp. Now you're ready to play. 
