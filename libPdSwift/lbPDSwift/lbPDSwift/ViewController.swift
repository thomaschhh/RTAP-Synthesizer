//
//  ViewController.swift
//  lbPDSwift
//
//  Created by Tim-Tarek Grund on 28.09.20.
//  Copyright © 2020 Tim-Tarek Grund. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    var patch:PDPatch?

    override func viewDidLoad() {
        super.viewDidLoad()
        
        patch = PDPatch(file: "sine440.pd")
        // Do any additional setup after loading the view.
    }

    @IBAction func onOffSwitchToggled(sender: UISwitch)
       {   //var sender_is_bool: Bool = sender.isOn
           //var test: Bool = true
           //var sender_is_float: Float = Float(NSNumber(value:test))
           //PdBase.send( Float(truncating: NSNumber(value:sender.isOn)), toReceiver: "onOff")   //works!
           //PdBase.sendFloat( Float(sender.on), toReceiver: "onOff" )             // original
        let onOffSwitch = sender 
        patch?.onOff1(onOffSwitch.isOn)
           /*func boolean2Double(_ booleanValue: Bool) -> Double
           {
               if(booleanValue) {
                   return 1.0 }
               else {
                   return 0.0 }
           }*/
           //PdBase.send(Float(boolean2Double(sender.isOn)), toReceiver: "onOff") //Works too!
        
        
       }
    @IBAction func sliderMoved(sender: UISlider)
        {
            let sliderOne = sender
            patch?.slider1(sliderOne.value)
        }
    
    @IBAction func buttonPressed1(sender: UIButton)
    {
        let freq = Float(500)
        patch?.taste1(freq)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        
    }
       

}

