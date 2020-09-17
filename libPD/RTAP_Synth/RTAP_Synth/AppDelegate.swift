//
//  AppDelegate.swift
//  RTAP_Synth
//
//  Created by Thomas Holz on 10.09.20.
//  Copyright © 2020 Thomas Holz. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow? // this wasn't here before  # Thomas
    var pd:PdAudioController? // initialize the PD audio controller # Thomas

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        // Create an instance of the PdAudioController # Thomas
        pd = PdAudioController()
        
        // Start the pd instance and get a status update # Thomas
        let pdInit = pd?.configureAmbient(withSampleRate: 44100, numberChannels: 2, mixingEnabled: true)
        
        if pdInit == PdAudioOK{
            print("Pd is ready to go.")
        } else {
            print("Something might be wrong with PD.")
        }
        return true
    }
    
    func applicationWillResignActive(_ application: UIApplication) {
        // Stop the pd engine when the app closes # Thomas
        pd?.isActive = false
    }
    
    func applicationDidBecomeActive(_ application: UIApplication) {
        // Start the pd engine when the app opens again # Thomas
        pd?.isActive = true
    }
    
    // MARK: UISceneSession Lifecycle

    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        // Called when a new scene session is being created.
        // Use this method to select a configuration to create the new scene with.
        
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }

    func application(_ application: UIApplication, didDiscardSceneSessions sceneSessions: Set<UISceneSession>) {
        // Called when the user discards a scene session.
        // If any sessions were discarded while the application was not running, this will be called shortly after application:didFinishLaunchingWithOptions.
        // Use this method to release any resources that were specific to the discarded scenes, as they will not return.
        }
}

