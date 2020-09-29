import UIKit

class ViewController: UIViewController {
    
    var patch:PDPatch?

    override func viewDidLoad() {
        super.viewDidLoad()
        
        patch = PDPatch(file: "synth_swift.pd")
        // Do any additional setup after loading the view.
    }
    
    /*--- Switch Section ---*/
    /* Example Code */
    //@IBAction func onOffSwitchToggled(sender: UISwitch)
       //{   //var sender_is_bool: Bool = sender.isOn
           //var test: Bool = true
           //var sender_is_float: Float = Float(NSNumber(value:test))
           //PdBase.send( Float(truncating: NSNumber(value:sender.isOn)), toReceiver: "onOff")   //works!
           //PdBase.sendFloat( Float(sender.on), toReceiver: "onOff" )             // original
        //let onOffSwitch = sender
        //patch?.onOff1(onOffSwitch.isOn)  // Pd onOff1
           /*func boolean2Double(_ booleanValue: Bool) -> Double
           {
               if(booleanValue) {
                   return 1.0 }
               else {
                   return 0.0 }
           }*/
           //PdBase.send(Float(boolean2Double(sender.isOn)), toReceiver: "onOff") //Works too!
       //}
    
    /*--- Slider Section ---*/
    /* Fundamentals */
    @IBAction func slider_fund1(sender: UISlider){
            let Fund1 = sender
            patch?.slider_fund1(Fund1.value)
    }
    @IBAction func slider_fund2(sender: UISlider){
            let Fund2 = sender
            patch?.slider_fund2(Fund2.value)
    }
    @IBAction func slider_fund3(sender: UISlider){
        let Fund3 = sender
        patch?.slider_fund3(Fund3.value)
    }
    @IBAction func slider_fund4(sender: UISlider){
         let Fund4 = sender
         patch?.slider_fund4(Fund4.value)
    }
    @IBAction func slider_fund5(sender: UISlider){
        let Fund5 = sender
        patch?.slider_fund4(Fund5.value)
    }
    
    /* Frequency Modulation */
    @IBAction func slider_ShimF1(sender: UISlider){
        let ShimF1 = sender
        patch?.slider_shimFreq1(ShimF1.value)
    }
    @IBAction func slider_ShimF2(sender: UISlider){
        let ShimF2 = sender
        patch?.slider_shimFreq2(ShimF2.value)
    }
    @IBAction func slider_ShimF3(sender: UISlider){
        let ShimF3 = sender
        patch?.slider_shimFreq3(ShimF3.value)
    }
    @IBAction func slider_ShimF4(sender: UISlider){
        let ShimF4 = sender
        patch?.slider_shimFreq4(ShimF4.value)
    }
    
    /* Modulation Strength */
    @IBAction func slider_ShimS1(sender: UISlider){
        let ShimS1 = sender
        patch?.slider_shimStrg1(ShimS1.value)
    }
    @IBAction func slider_ShimS2(sender: UISlider){
        let ShimS2 = sender
        patch?.slider_shimStrg2(ShimS2.value)
    }
    @IBAction func slider_ShimS3(sender: UISlider){
        let ShimS3 = sender
        patch?.slider_shimStrg3(ShimS3.value)
    }
    @IBAction func slider_ShimS41(sender: UISlider){
        let ShimS4 = sender
        patch?.slider_shimStrg4(ShimS4.value)
    }
            
    /* Envelope */
    @IBAction func slider_attack(sender: UISlider){
        let attack = sender
        patch?.slider_attack(attack.value)
    }
    @IBAction func slider_decay(sender: UISlider){
        let decay = sender
        patch?.slider_decay(decay.value)
    }
    @IBAction func slider_sustain(sender: UISlider){
        let sustain = sender
        patch?.slider_sustain(sustain.value)
    }
    @IBAction func slider_release(sender: UISlider){
        let release = sender
        patch?.slider_release(release.value)
    }
    @IBAction func slider_exp(sender: UISlider){
        let expo = sender
        patch?.slider_exp(expo.value)
    }
            
    /* Spacer / Gain */
    @IBAction func slider_spacer(sender: UISlider){
        let spacer = sender
        patch?.slider_spacer(spacer.value)
    }
    @IBAction func slider_gain(sender: UISlider){
        let gain = sender
        patch?.slider_gain(gain.value)
    }
   
    /*--- Button Section ---*/
    /* Wavevorms */
    @IBAction func buttonSine(sender: UIButton){
        let sel_sine = Float(1)
        patch?.button_sine(sel_sine)
    }
    @IBAction func buttonSaw(sender: UIButton){
        let sel_saw = Float(1)
        patch?.button_sawtooth(sel_saw)
    }
    @IBAction func buttonTri(sender: UIButton){
        let sel_tri = Float(1)
        patch?.button_triangle(sel_tri)
    }
    @IBAction func buttonSqr(sender: UIButton){
        let sel_sqr = Float(1)
        patch?.button_square(sel_sqr)
    }
    
    /* Keyboard Press Down */
    @IBAction func buttonDowNote1(sender: UIButton){
        let note1 = Float(48)  // Corresponding MIDI note
        patch?.button_note1(note1)
    }
    @IBAction func buttonDowNote2(sender: UIButton){
        let note2 = Float(49)
        patch?.button_note2(note2)
    }
    @IBAction func buttonDowNote3(sender: UIButton){
        let note3 = Float(50)
        patch?.button_note3(note3)
    }
    @IBAction func buttonDowNote4(sender: UIButton){
        let note4 = Float(51)
        patch?.button_note4(note4)
    }
    @IBAction func buttonDowNote5(sender: UIButton){
        let note5 = Float(52)
        patch?.button_note5(note5)
    }
    @IBAction func buttonDowNote6(sender: UIButton){
        let note6 = Float(53)
        patch?.button_note6(note6)
    }
    @IBAction func buttonDowNote7(sender: UIButton){
        let note7 = Float(54)
        patch?.button_note7(note7)
    }
    @IBAction func buttonDowNote8(sender: UIButton){
        let note8 = Float(55)
        patch?.button_note8(note8)
    }
    @IBAction func buttonDowNote9(sender: UIButton){
        let note9 = Float(56)
        patch?.button_note9(note9)
    }
    @IBAction func buttonDowNote10(sender: UIButton){
        let note10 = Float(57)
        patch?.button_note10(note10)
    }
    @IBAction func buttonDowNote11(sender: UIButton){
        let note11 = Float(58)
        patch?.button_note11(note11)
    }
    @IBAction func buttonDowNote12(sender: UIButton){
        let note12 = Float(59)
        patch?.button_note12(note12)
    }
    @IBAction func buttonDowNote13(sender: UIButton){
        let note13 = Float(60)
        patch?.button_note13(note13)
    }
    @IBAction func buttonDowNote14(sender: UIButton){
        let note14 = Float(61)
        patch?.button_note14(note14)
    }
    @IBAction func buttonDowNote15(sender: UIButton){
        let note15 = Float(62)
        patch?.button_note15(note15)
    }
    @IBAction func buttonDowNote16(sender: UIButton){
        let note16 = Float(63)
        patch?.button_note16(note16)
    }
    @IBAction func buttonDowNote17(sender: UIButton){
        let note17 = Float(64)
        patch?.button_note17(note17)
    }
    @IBAction func buttonDowNote18(sender: UIButton){
        let note18 = Float(65)
        patch?.button_note18(note18)
    }
    @IBAction func buttonDowNote19(sender: UIButton){
        let note19 = Float(66)
        patch?.button_note19(note19)
    }
    @IBAction func buttonDowNote20(sender: UIButton){
        let note20 = Float(67)
        patch?.button_note20(note20)
    }
    @IBAction func buttonDowNote21(sender: UIButton){
        let note21 = Float(68)
        patch?.button_note21(note21)
    }
    @IBAction func buttonDowNote22(sender: UIButton){
        let note22 = Float(69)
        patch?.button_note22(note22)
    }
    @IBAction func buttonDowNote23(sender: UIButton){
        let note23 = Float(70)
        patch?.button_note23(note23)
    }
    @IBAction func buttonDowNote24(sender: UIButton){
        let note24 = Float(71)
        patch?.button_note24(note24)
    }
    @IBAction func buttonDowNote25(sender: UIButton){
        let note25 = Float(72)
        patch?.button_note25(note25)
    }
    
    /* Keyboard Lift Up*/
    @IBAction func buttonUpNote1(sender: UIButton){
        let note1 = Float(0)  // Corresponding MIDI note
        patch?.button_note1(note1)
    }
    @IBAction func buttonUpNote2(sender: UIButton){
        let note2 = Float(0)
        patch?.button_note2(note2)
    }
    @IBAction func buttonUpNote3(sender: UIButton){
        let note3 = Float(0)
        patch?.button_note3(note3)
    }
    @IBAction func buttonUpNote4(sender: UIButton){
        let note4 = Float(0)
        patch?.button_note4(note4)
    }
    @IBAction func buttonUpNote5(sender: UIButton){
        let note5 = Float(0)
        patch?.button_note5(note5)
    }
    @IBAction func buttonUpNote6(sender: UIButton){
        let note6 = Float(0)
        patch?.button_note6(note6)
    }
    @IBAction func buttonUpNote7(sender: UIButton){
        let note7 = Float(0)
        patch?.button_note7(note7)
    }
    @IBAction func buttonUpNote8(sender: UIButton){
        let note8 = Float(0)
        patch?.button_note8(note8)
    }
    @IBAction func buttonUpNote9(sender: UIButton){
        let note9 = Float(0)
        patch?.button_note9(note9)
    }
    @IBAction func buttonUpNote10(sender: UIButton){
        let note10 = Float(0)
        patch?.button_note10(note10)
    }
    @IBAction func buttonUpNote11(sender: UIButton){
        let note11 = Float(0)
        patch?.button_note11(note11)
    }
    @IBAction func buttonUpNote12(sender: UIButton){
        let note12 = Float(0)
        patch?.button_note12(note12)
    }
    @IBAction func buttonUpNote13(sender: UIButton){
        let note13 = Float(0)
        patch?.button_note13(note13)
    }
    @IBAction func buttonUpNote14(sender: UIButton){
        let note14 = Float(0)
        patch?.button_note14(note14)
    }
    @IBAction func buttonUpNote15(sender: UIButton){
        let note15 = Float(0)
        patch?.button_note15(note15)
    }
    @IBAction func buttonUpNote16(sender: UIButton){
        let note16 = Float(0)
        patch?.button_note16(note16)
    }
    @IBAction func buttonUpNote17(sender: UIButton){
        let note17 = Float(0)
        patch?.button_note17(note17)
    }
    @IBAction func buttonUpNote18(sender: UIButton){
        let note18 = Float(0)
        patch?.button_note18(note18)
    }
    @IBAction func buttonUpNote19(sender: UIButton){
        let note19 = Float(0)
        patch?.button_note19(note19)
    }
    @IBAction func buttonUpNote20(sender: UIButton){
        let note20 = Float(0)
        patch?.button_note20(note20)
    }
    @IBAction func buttonUpNote21(sender: UIButton){
        let note21 = Float(0)
        patch?.button_note21(note21)
    }
    @IBAction func buttonUpNote22(sender: UIButton){
        let note22 = Float(0)
        patch?.button_note22(note22)
    }
    @IBAction func buttonUpNote23(sender: UIButton){
        let note23 = Float(0)
        patch?.button_note23(note23)
    }
    @IBAction func buttonUpNote24(sender: UIButton){
        let note24 = Float(0)
        patch?.button_note24(note24)
    }
    @IBAction func buttonUpNote25(sender: UIButton){
        let note25 = Float(0)
        patch?.button_note25(note25)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}

