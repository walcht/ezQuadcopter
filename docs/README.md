# Check [official documentation link]() for all documentation

## Documentation is split into four sections:
 - __[Introduction to drones](#introduction-to-drones)__
 - __[Code documentaion](#code-documentation)__
 - __[Building a quadcopter from A to Z](#building-a-quadcopter-from-a-to-z)__
 - __[Useful references](#useful-references)__

## Introduction to drones:
 This is where drone-related concepts are explained:
 - __How drones fly__
 - __Why is each component needed__
 - __How each componenent works__
 - __Theoretical concepts__
  - __Control theory__
  - __Data fusion__
  - __Gimbal lock and quaternions__
 - __Security concerns__

## Code documentation:
 - This is where flight controller and transmitter code is explained.
Two approaches to how the source code is designed are provided:
  1. __all-in-one-file approach__
  2. __Object-oriented approach__

 - The documentation explains _common code_ (code that reamains the same in these two approaches) only in __all-in-one-file__ approach.

### all-in-one-file approach
- In case you are in hurry and you are using the exact same components that this project uses,
you can just copy the two source code files in src/all\_in\_one\_file and you are good to go.

- It should be noted that in case you want to use a different module, say a different IMU or a different
transceiver module, using the object-oriented approach is much more suitable.

- The documentation explains:
  - __how to setup the source files for your project__
  - __how to debug (with _fency_ printing methods)__
  - __overall functions__
    - __PID function__
    - __IMU function__
    - __EEPROM function__
    - __transmitter function__
    - __receiver function__
    - __calibration function__
    - __security-related functions__

### object-oriented approach
- This approach is much more versatile and organized than that of the all-in-one-file.
- In case you want to replace a componenent, all you have to is:
  - Create a class that inherits from a

- The documentation explains:
  - __how to setup the source files for your project__
  - __how to debug (with _fency_ printing methods)__
  - __classes__
    - __UML diagram__
    - __classes documentation__
  - __how to replace a module__
  - __how to add extra functionalities__
  

## Building a quadcopter from A to Z:
 -  This section provides a thorough guide on how to build a quadcopter using easy-to-find and cheap components.

 - Even if you're using different components, you can still follow this guide as it provides generic
insights (aren't vendor specific) on how to build and get your quadcopter flying.

## Useful references
 - This is where you can find plenty of references to helpful resources.
 - This includes but not limited to:
   - references to BLDC Motor + propeller data
   - references to calibration processes
   - references to guides on LiPo batteries
   - references to other useful articles
