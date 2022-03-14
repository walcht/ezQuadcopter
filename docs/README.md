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
Two approaches to the source code are provided:
  1. all-in-one-file approach
  2. Object-oriented approach

### all-in-one-file approach
 In case you are in hurry and you are using the exact same components that this project uses,
you can just copy the two source code files in src/all\_in\_one\_file and you are good to go.

It should be noted that in case you want to use a different module, say a different IMU or a different
transceiver module, using the object-oriented approach is much more suitable.

### object-oriented approach
 This approach is much more versatile and organized than that of the all-in-one-file.
The documentation explains:
 - functionalities of each class
 - how to replace a module with another module

## Building a quadcopter from A to Z:

