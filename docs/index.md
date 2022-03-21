# ezQuadcopter Documentation

### Table of Contents
 - [__Introduction to Drones__](#introduction-to-drones)
 	- [__How drones fly__](#how-drones-fly)
 	- [__How each componenent works__](#how-each-component-works)
		- [__Propellers__](#propellers)
		- [__Brushless Motors__](#brushless-motors)
		- [__Electronic Speed Controllers (ESCs)__](#electronic-speed-controllers-(escs))
		- [__Inertial Measurement Units (IMUs)__](#inertial-measurement-unit-(imus))
			- [__Gyroscope Sensor__](#gyroscope-sensor)
			- [__Accelerometer__](#accelerometer)
			- [__magnetometer__](#magnetometer)
		- [__Radio-frequency Module__](#radio-frequency-module)
		- [__Flight Controllers__](#flight-controllers)
		- [__LiPo Batteries__](#lipo-batteries)
 	- [__Theoretical concepts__](#theoretical-concepts)
  		- [__Control theory__](#control-theory)
  		- [__Data fusion__](#data-fusion)
  		- [__Gimbal lock and quaternions__](#gimbal-lock-and-quaternions)
 	- [__Security concerns__](#security-concerns)
 - __[Code Documentation](#code-documentation)__
 - __[Building a Quadcopter from A to Z](#building-a-quadcopter-from-a-to-z)__
 - __[Useful References](#useful-references)__



## Introduction to Drones

### How drones fly
___
### How each component works
 #### Propellers
  #### Brushless Motors
  #### Electronic Speed Controllers (ESCs)
  #### Inertial Measurement Units (IMUs)
  ##### Gyroscope Sensor
  ##### Accelerometer
  ##### magnetometer
  #### Radio-frequency Module
#### Flight Controllers
#### LiPo Batteries
___
### Theoretical concepts
  #### Control theory
The feedback loop is at the heart of control theory. A feedback loop occurs when outputs of a system(or process)
are transformed into inputs for the same system, thus forming a loop where the current output will be fed in as
a form of input in the next iteration.
		
Maybe an example will make everything clear:

```
While you're driving your car in the highway, you decided to keep your speed constant at, let's say, 90 km\h.
You look to the speedometer you realize you're going 80 km\h, you realize that the difference between the current
speed and the desired speed isn't that high thus you slowly push the throttle. You keep looking at the speedometer,
you realize you're getting closer to the desired speed, it's 84 km\h, thus you slightly push the throttle. You keep
executing this loop during the whole journey until you reach your destination. Each time you measure
the output of your input (stepping on the throttle) by looking at the speedometer and you determine your _new_ input
from the measured speed value.
```

The goal of control theory is to develop a model that drives a system's parameter(s) into a desired value.

__Terminology__
		
- _Set Point_ : is the desired value for the parameter(s) the system controls
- _Process Variable_: is the measured value for the parameter(s) the system controls
				
In our previous anology:
- _Set Point_ : speed of the car = 90 km\h
- _Process Variable_: That is the speed of the car

__What does this have to do with drones?__
- Drones aren't stable, even if you apply the exact same throttle to all the motors, chances it will crash immediatly.
No, this has nothing to do with your piloting skills, it is due to the fact that it is impossible to build a perfect drone
where the center of gravity is perfectly placed, where the motors rotate at the exact same speed, where the propellers are
perfectly made, where ...

- And even if that was the case, what if a burst of wind destabilizes your drone while you're not paying attention?

That is why we need __control theory__ to __guide__ the drone into the _desired values_.

__What are those _desired_ values?__
- For a simple drone, those are the _orientation values_ that the drone must target.
These values are:
 - Pitch
 - Roll
 - Yaw
These are either provided by the user through the remote-controller, or are set to a _default_
value when the drones receives no input from the user.

- For more complex drones, added to the orientation values, one might add:
 - Speed
 - Altitude
 - Position
 - etc...

__PID CONTROL__
		
#### Data fusion
#### Gimbal lock and quaternions

___
### Security concerns

## Code Documentation
## Building a Quadcopter from A to Z
## Useful References
