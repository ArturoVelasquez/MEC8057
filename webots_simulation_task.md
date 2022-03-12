1) Webots Simulation Task (30 marks)
The Webots part of the assignment is as follows. Note that you should write only one program to
complete all the required tasks. You should fully label your code with comments using //.
a) In Webots, create the environment:
 Create a room of size 10m x 10m with a floor tile size of 0.5m x 0.5m. Have the room bounded by
a perimeter wall of height 0.1m. In the centre of the room, create a cylinder of radius 0.05m and
height 0.001m and choose an appropriate colour for this object. Position it to mark the centre of
the room whilst not being an obstacle for the robot.
 Construct a differential drive robot of dimensions (l,w,h) of no greater than 0.25m x 0.25m x
0.3m. You may place any sensors on the robot that you think are suitable to help complete the
following tasks. Place this robot at the centre of the room.
 Construct 6 boxes of various sizes and colours but with dimensions (l,w,h) of at least 0.5m x
0.25m x 0.3m and place these randomly at least 2m from the centre of the room.
 Construct a cube with edges of length 0.1m and place this behind one of the boxes (so it cannot
be seen by the robot). It should be a distinct colour.
b) Perform pre-programmed movement:
 Write a controller to drive the robot along a square trajectory. The square should be of size 1m x
1m and the robot should finish at its starting location at the centre of the room with the same
orientation.
 Once the robot has completed moving in a square, the robot should then complete a figure 8
trajectory (this can be two circular trajectories, one clockwise, one anticlockwise). The radius of
each circle should be 0.5m. Again the robot should finish in the same position and orientation as
the start.
c) Once completing these pre-programmed moves, the robot should immediately move around the
environment and locate the randomly placed cube. You will need to explain the search algorithm
used. The robot should not bump into any objects whilst completing this task thus the robot should
contain appropriate collision avoidance sensors. Once the cube is located, the robot should stop as
closely as possible to it without touching it. Once the robot is stopped you should pause the
simulation.d) With the simulation paused, you should drag the cube on top of the robot and then restart the
simulation. The robot should automatically detect this object on the robot and weigh it (you do not
need to have Webots print out this weight although you should demonstrate that your program is
performing this weighing). The robot should then return to the start point (centre of the room)
whilst carrying this cube. You can use any sensor you wish to perform this ‘return to centre task’ but
an intelligent control algorithm will gain higher marks (for example random walk back to the start is
one solution but is not ideal, what is the quickest / most efficient trajectory back to the start – you
should explain how you have achieved this in your presentation).
