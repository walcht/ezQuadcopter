#ezQuadcopter Documentation

###Table of Contents
 - __[Introduction to Drones](#introduction-to-drones)__
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



##Introduction to Drones

###How drones fly
###How each component works
	####Propellers
	####Brushless Motors
	####Electronic Speed Controllers (ESCs)
	####Inertial Measurement Units (IMUs)
		#####Gyroscope Sensor
		#####Accelerometer
		#####magnetometer
	####Radio-frequency Module
	####Flight Controllers
	####LiPo Batteries

###Theoretical concepts
	####Control theory
		The feedback loop is at the heart of control theory. A feedback loop occurs when outputs of a system(or process)
		are transformed into inputs for the same system, thus forming a loop where the current output will be fed in as
		a form of input in the next iteration.
		
		Maybe an anology will make everything clear?
		
		Imagine that while you're riding your bicycle you saw a straight line on the road and, for some reason,
		you decided to follow it. This is an example of a feedback loop, the way you handle the bicycle affects
		your position relative to that line, thus each time you notice that you're deviating from that straight
		line you try to correct the tragectory you're following by changing the way you handle the bicycle. You'll
		keep doing this.

		Thus the goal of control theory is to develop a model that that drives a system's parameter(s) into a desired value.

		
		
	 	
		__Terminology__
		
		_Set Point_ : 
		_Process Variable_:
				
		In our previous anology:
		_Set Point_ : Position of bicycle realative to the straight line _should_ be null
		_Process Variable_: That is 
		
	####Data fusion
	####Gimbal lock and quaternions
###Security concerns

##Code Documentation
##Building a Quadcopter from A to Z
##Useful References
