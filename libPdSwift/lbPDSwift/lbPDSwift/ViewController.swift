import UIKit

class ViewController: UIViewController {
    
    var patch:PDPatch?

    override func viewDidLoad() {
        super.viewDidLoad()
        
        patch = PDPatch(file: "sine440.pd")
        // Do any additional setup after loading the view.
    }
    
    /*--- Switch Section ---*/
    /* Example Code */
    @IBAction func onOffSwitchToggled(sender: UISwitch)
       {   //var sender_is_bool: Bool = sender.isOn
           //var test: Bool = true
           //var sender_is_float: Float = Float(NSNumber(value:test))
           //PdBase.send( Float(truncating: NSNumber(value:sender.isOn)), toReceiver: "onOff")   //works!
           //PdBase.sendFloat( Float(sender.on), toReceiver: "onOff" )             // original
        let onOffSwitch = sender 
        patch?.onOff1(onOffSwitch.isOn)  // Pd onOff1
           /*func boolean2Double(_ booleanValue: Bool) -> Double
           {
               if(booleanValue) {
                   return 1.0 }
               else {
                   return 0.0 }
           }*/
           //PdBase.send(Float(boolean2Double(sender.isOn)), toReceiver: "onOff") //Works too!
       }
    
    /*--- Slider Section ---*/
    /* Example Code */
    @IBAction func sliderMoved(sender: UISlider)
        {
            /* Fundamentals */
            let Fund1 = sender
            patch?.slider_fund1(Fund1.value)
            let Fund2 = sender
            patch?.slider_fund2(Fund2.value)
            let Fund3 = sender
            patch?.slider_fund3(Fund3.value)
            let Fund4 = sender
            patch?.slider_fund4(Fund4.value)
            let Fund5 = sender
            patch?.slider_fund4(Fund5.value)
            
            /* Frequency Modulation */
            let ShimF1 = sender
            patch?.slider_shimFreq1(ShimF1.value)
            let ShimF2 = sender
            patch?.slider_shimFreq2(ShimF2.value)
            let ShimF3 = sender
            patch?.slider_shimFreq3(ShimF3.value)
            let ShimF4 = sender
            patch?.slider_shimFreq4(ShimF4.value)
            
            /* Modulation Strength */
            let ShimS1 = sender
            patch?.slider_shimStrg1(ShimS1.value)
            let ShimS2 = sender
            patch?.slider_shimStrg2(ShimS2.value)
            let ShimS3 = sender
            patch?.slider_shimStrg3(ShimS3.value)
            let ShimS4 = sender
            patch?.slider_shimStrg4(ShimS4.value)
            
            /* Envelope */
            let attack = sender
            patch?.slider_attack(attack.value)
            let decay = sender
            patch?.slider_decay(decay.value)
            let sustain = sender
            patch?.slider_sustain(sustain.value)
            let release = sender
            patch?.slider_release(release.value)
            let expo = sender
            patch?.slider_exp(expo.value)
            
            /* Spacer / Gain */
            let spacer = sender
            patch?.slider_spacer(spacer.value)
            let gain = sender
            patch?.slider_gain(gain.value)
            
            /* Example Code */
            let sliderOne = sender
            patch?.slider1(sliderOne.value)  // Pd slider1
        }
    /*--- Button Section ---*/
    /* Example Code */
    @IBAction func buttonPressed1(sender: UIButton)
    {
        /* Wavevorms */
        let sel_sine = Float(500)  // 1/0
        patch?.button_sine(sel_sine)
        let sel_saw = Float(500)  // 1/0
        patch?.button_sine(sel_saw)
        let sel_tri = Float(500)  // 1/0
        patch?.button_sine(sel_tri)
        let sel_sqr = Float(500)  // 1/0
        patch?.button_sine(sel_sqr)
        
        /* Keyboard */
        let note1 = Float(48)  // Corresponding MIDI note
        patch?.button_note1(note1)
        let note2 = Float(49)
        patch?.button_note2(note2)
        let note3 = Float(50)
        patch?.button_note3(note3)
        let note4 = Float(51)
        patch?.button_note4(note4)
        let note5 = Float(52)
        patch?.button_note5(note5)
        let note6 = Float(53)
        patch?.button_note6(note6)
        let note7 = Float(54)
        patch?.button_note7(note7)
        let note8 = Float(55)
        patch?.button_note8(note8)
        let note9 = Float(56)
        patch?.button_note9(note9)
        let note10 = Float(57)
        patch?.button_note10(note10)
        let note11 = Float(58)
        patch?.button_note11(note11)
        let note12 = Float(59)
        patch?.button_note12(note12)
        let note13 = Float(60)
        patch?.button_note13(note13)
        let note14 = Float(61)
        patch?.button_note14(note14)
        let note15 = Float(62)
        patch?.button_note15(note15)
        let note16 = Float(63)
        patch?.button_note16(note16)
        let note17 = Float(64)
        patch?.button_note17(note17)
        let note18 = Float(65)
        patch?.button_note18(note18)
        let note19 = Float(66)
        patch?.button_note19(note19)
        let note20 = Float(67)
        patch?.button_note20(note20)
        let note21 = Float(68)
        patch?.button_note21(note21)
        let note22 = Float(69)
        patch?.button_note22(note22)
        let note23 = Float(70)
        patch?.button_note23(note23)
        let note24 = Float(71)
        patch?.button_note24(note24)
        let note25 = Float(72)
        patch?.button_note25(note25)
        
        /* Example Code */
        let freq = Float(500)
        patch?.taste1(freq)  // PD taste1
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        
    }
       

}

