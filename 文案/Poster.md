## Poster


### Problem Statement

In the era of Mars colonization, people will need all kinds of machines for all kinds of  purposes. However, it is a waste of material and money to build all the machines separately on Mars even if they share some same functions. When a complex task is demanded, the waste may be even higher.

### Needs

The modularization idea, “one platform +  function modules + an optional chassis”, has been used in our Mars explorer to achieve all the demands.

  - The platform supports the modules and mange the power and I/O of the whole system. 
  - Different modules are dedicated for different needs. By combining several modules, the machine can accomplish complex tasks.
  - The optional chassis enable the machine to be an all terrain vehicle.



### Design Description

As mentioned above, our mars explorer consists of one platform, multiple function modules and an optional chassis.

The platform is the center of our car. It has 3 module slots with power supply and I/O connection, an Arduino Mega board plus an ESP32 board as the controller, 3 L298N DC Motor Driver modules to  power and control up to six wheels from the chassis separately. 

Modules:

- Robotic Arm: It is a 6 degrees of freedoms (DoF) robotic arm....

- Camera Module: It is a combination of ESP32-Camera chip and a 2 DoF camera pan, which enables the user to both receive smooth video streaming and adjust the position of the camera.
- Solar Panel:
- Karaoke:

Chassis: ...

### Significance of Solution

- Platform

  ...

- Universal Plug

  ...

- Interface

  The interfaces are built upon the ESP32 chip and can be accessed through any web browser. All the control interfaces are digital, making it easy to be modified and upgraded.

  

### Validation

Validation Process:       
To test the stability of connection between the universal plug and the platform, we use all the modules to do verification tests.
For the chasis and platform, the speed and stability of motion are tested. 
The function of all the modules are also tested.
Validation Results:
According to validation part, most specifications can be met.

The connection between the universal plugs and the platform is stable.
The average speed of walking is 10m/s.
The movement is relatively stable. 
All the modules work properly.
The cooperation between the two modules is implementable. 

### Conclusion

Our Mars Explorer realizes modular design well.

The four finished modules, the robotic arm, the camera, the solar panel and the karaoke can independently perform its task as well as cooperate  to perform complex tasks.

What's more, the design of universal plug not only makes the switch, repair and upgrade of modules easy, but also make the development of new modules much simpler.

Finnally, the optional, replaceable chassis provides the car the mobility in Mar's complex environment.

