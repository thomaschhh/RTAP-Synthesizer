# Shimmer Synth 
![Logo](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/projectlogo.jpg?raw=true)

This synthesizer was created during the 2nd semester in our Audio Communication and Technology studies in 2020 as a final project in the class Real-Time Audio Programming. The task consisted of creating a Pure Data patch and writing an external for it in C. 

After we had decided to develop a synthesizer and create an app for the iPad, we found the option to use [TouchOSC](https://hexler.net/docs/touchosc-getting-started). 
We implemented our own Pd patch [synth_osc.pd](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/PureData/synth_osc.pd) into the already existing [basic.pd](https://hexler.net/pub/touchosc/basic.pd) patch and found out that we had to work with [purr-data](https://agraef.github.io/purr-data/) instead of [Pd Vanilla](http://puredata.info/downloads/pure-data). The reason for this was the fact that we actually needed [Pd-Extended](http://puredata.info/downloads/pd-extended) for OSC to work which is no longer supported.

For the iPad app, we adjusted the [swift patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/PureData/synth_swift.pd) a little bit for it to work with Swift.
As of today, the xy-pad that's implemented in the TouchOSC app is not yet implemented in the iPad app.

***

### Steps to Get The Synth Running

- Start **purr-data** and open the file [synth_osc.pd](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/PureData/synth_osc.pd).

![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/pd_patch.png?raw=true)

- Load and open the **TouchOSC** app on your iPad.
![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/osc_layout.jpg?raw=true)
    - Look for the network settings (*Connections* --> *OSC: HOST IP*).
    - Type in your PC's IP address (*Host*).
    
![Entire Pd Patch](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/osc_connections.jpg?raw=true)

- Port 8000 is used in the *dumpOSC* box in Pd. 
- Port 9000 is used int the *connect* box in Pd.
- Inside the **synth_osc.pd** patch, type in the iPad's IP address (*local IP address*) inside the *connect message box* (**1**).
    - Click the *connect* message box in order to connect to the iPad.
    - Adjust the attack, decay, sustain, release sliders to your liking (**2**).
    - Do the same thing with the Fundamentals (**3**) as well as its Shimmer Strength / Shimmer Frequency (**4**).
    - Select the desired waveform (**5**), determine to what extend the notes should be spaced between left and right (**6**) adjust the the amount of reverb (**7**)  and delay (**8**), turn up the volume (**9**) and turn on the dsp (**10**). 
    - Now you're ready to play. 
    
![iPad App](https://github.com/thomaschhh/RTAP-Synthesizer/blob/master/Images/ipad.png?raw=true)

***
    
