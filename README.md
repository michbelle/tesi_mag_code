### how to compile

to compile the code mkdir build directory / cmake .. from there and then make


### add to easy compile using make
dove aggiungere il nome del world per poterlo lanciare con make

make sitl_px4 gazebo__tesi_concatenaria

/src/PX4-Autopilot/platforms/posix/cmake/sitl_target.cmake


plugin world destroy when launched with  
Tools/gazebo_sitl_multiple_run.sh -m iris -n 2 -w tesi_concatenaria.world

find another way

### the solution of the problem above

the another way is to use the launch
i hoped to use before the bare metal but becouse gives so much error we will skip that and go dircetly to ros

launch using this command

```
roslaunch launch/multi_uav_mavros_sitl.launch 
```