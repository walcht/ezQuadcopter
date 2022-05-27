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
- Inertial measurement unit is an electronic sensor that measures the orientation of the object it is attached to.
The orientation of an object is determined by essentially three values: **Pitch**, **Roll** and **Yaw**.
Here is a picture that you should never forget (because we'll use these terms a lot!)
![orientation_terms][orientation_terms]
we'll discuss IMUs as in their use in flight controllers for drones.
- IMUs usually use a combination of **accelerometers**, **gyroscopes** and **magnetometers**.
  - __Accelerometers__ can, to some extent, measure earth's gravitational field at a particular point.
(This is oversimplified of course, check this [Wikipedia link](https://en.wikipedia.org/wiki/Accelerometer) for further details.)
  - __Gyroscopes__ measure the rate of rotation along the three axis. Gyroscopes are needed because
  accelerometer suffer from *drift*; essentially, accelerometers become less accurate overtime.
  - __Magnetometers__ can, to some extent, measure earth's magnetic field. This is important to determine yaw rotation values.

We'll dive deeper into each component in the sections below.

##### Accelerometer
![ACCELEROMETER AXIS][accelerometer_axis]

##### Gyroscope Sensor

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
		
- _**Set Point**_ : is the desired value for the parameter(s) the system controls
- _**Process Variable**_: is the measured value for the parameter(s) the system controls
- _**Error**_: is the difference between a set point and a measured process variable
			
In our previous anology:
- _Set Point_ : speed of the car = 90 km\h
- _Process Variable_: That is the speed of the car measured through the speedometer
- _Error_: That is the difference between 90 km\h and the speed on the speedometer

__Okay, but what does this have to do with drones?__
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
 
- These are either provided by the user through the remote-controller, or are set to a _default_
value when the drones receives no input from the user.
For instance, when the drone is IDLE (no input from the user), we want it to **stabilize** around these values:
  - 0 for Pitch
  - 0 for Roll
  - 0 for Yaw

- For more complex drones, added to the orientation values, one might add:
  - Speed
  - Altitude
  - Position
  - etc...

- All of these parameters are measured by sensors. Some parameters could be even 'measured' by a camera.

__PID CONTROLLER__
- **P**roportional–**I**ntegral–**D**erivative controller is a simple feedback loop mechanism that **contineously**
calculates the *Error* and applies a *correction* based on **proportional**, **integral** and **derivative** terms
of the error.

![PID CONTROLLER DIAGRAM][pid_controller]

- It should be noted that **PI** and **PD** are also widely used controllers.

![PID CONTROLLER FORMULA][pid_controller_formula]

__Okay... Maybe an example would be helpful?__
- __Proportional correction__: Applies an output(in other terms correction) **proportional** to the error

```
Let's go back to the car example, each time you measure the error, that is the difference between the set point (90 km\h) and 
the speed measured from the speedometer, you apply a proportional force to the throttle pedal. For instance, you notice that 
the error is 20 km\h thus you push somewhat hardly on the pedal. You notice the error is 4 km\h thus you slightly push the pedal.
```

- __Derivative correction__: Applies an output proportional to the **rate of change** of the error
The derivative term is used to avoid **overshooting** the set point.
```
In the same example, you realize the error is 30 km\h, that is a significant error thus you apply a proportional correction by
flooring the peddal! After some time, the error is 25 km\h but you realize that you are rapidly approaching 90 km\h and that
there is a risk that you will surpass that value (overshoot) that you decide to reduce the force by which you step on the pedal.
```

- __Integral correction__: Applies an output proportional to the **accumulated** error
You can think of the intergral term as an offset that compensates for a steady-state error that is present in your system.

```
Up to this point, we assumed that the output of the PID controller is the change in force applied to the pedal thus when we reach
the desired speed,the output would be zero (that is no change in force applied to the peddal). But what if we want the output
to be an angle (see picture). In this case, even if you've reached the desired speed, the output of the PID shouldn't be
zero! Without the integral part, the output would be zero, that is a 0 angle which is wrong.
```
![PEDAL ANGLE][pedal_angle]
- Now, hopefully, you've got an indea about control theory and PID controllers in particular.
You can check

#### Data fusion
#### Gimbal lock and quaternions

___
### Security concerns

## Code Documentation
## Building a Quadcopter from A to Z
## Useful References


[accelerometer_axis]: images/accelerometer_axis.png
[pid_controller]: images/pid_controller.png
[pid_controller_formula]: images/pid_controller_formula.png
[pedal_angle]: images/pedal_angle.png
[orientation_terms]: images/orientation_terms.png

