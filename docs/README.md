# Check [official documentation link]() for all documentation

## Documentation is split into three sections:
 - __Introduction to drones__
 - __Code documentaion__
 - __Building a quadcopter from A to Z__

## Introduction to drones:
 This is where drone-related concepts are explained:
 - How drones fly
 - Why is each component needed
 - How each componenent works
 - Theoretical concepts
  - Control theory
  - Data fusion
  - Gimbal lock and quaternions
 - Security concerns

## Code documentation:
 This is where flight controller and transmitter code is explained.
Two approaches to how the source code is written\designed are provided:
  1. __all-in-one-file approach__
  2. __Object-oriented approach__

### all-in-one-file approach
- In case you are in hurry and you are using the exact same components that this project uses,
you can just copy the two source code files in src/all\_in\_one\_file and you are good to go.

- It should be noted that in case you want to use a different module, say a different IMU or a different
transceiver module, using the object-oriented approach is much more suitable.

### object-oriented approach
 This approach is much more versatile and organized than that of the all-in-one-file.
The documentation explains:
 - functionalities of each class
 - how to replace a module

## Building a quadcopter from A to Z:
 -  This section provides a thorough guide on how to build a quadcopter using _common components_.

 - Even if you're using different components, you can still follow this guide as it provides generic
insights (aren't vendor specific) on how to build and get your quadcopter flying.

