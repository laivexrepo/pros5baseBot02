# pros5baseBot01
Basic two motor bot

This is a basic two motor based sample project to show how to setup a basic PROS program, this example shows the use of basic include files for general parameter settings.

We are using to includes: portdef.hpp for all V5 brain port definitions and then globals.hpp / globals.cpp to declare all globally available variables and definitions.

This version expands by showing how to include code modules which control specific parts of a robot, in this case drive base movements.  It uses drivebase.cpp to define a function called driveForDistance which takes as input a desired distance to move in cm (if negative it will drive backwards), the second parameter is used to set the speed of the movement.

This code also introduces a global #define DEBUG to allow for more or less debugging related console messages to be displayed, it is set be default to tru, but setting it to false in globals.hpp will turn those messages off.
