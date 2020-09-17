//
//  ViewController.swift
//  RTAP_Synth
//
//  Created by Thomas Holz on 17.09.20.
//  Copyright © 2020 Thomas Holz. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    var patch:PDPatch?  // reference to the patch of the type PDPatch
    
    @IBAction func onSwitchChange(sender: AnyObject) {
        let onOffSwitch = sender as! UISwitch
        patch?.onOff(onOffSwitch.isOn)  // pass the value to the switch
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        
        patch = PDPatch(file: "sine440.pd")
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
}
