# CarND-Path-Planning-Project
Self-Driving Car Engineer Nanodegree Program

## Path Generation
Paths are generated in Fernet coordinates. In order to have a smooth path, the function for getting X/Y coordinates uses a spline that goes through all the points in higway_map.csv

Paths are generated in the following classes:

##### LaneKeeper
It is used to keep the car in the same lane. Path generation is done with a constant **d** values and small increments to the **s** value, according to the current_speed.

If the current speed is below the target speed, it is gradually increased on each point. Similarly, if we want to decrease speed, it is gradually decremented on each point

If there are already points generated from a previous iteration, only enough points to bring the total to 100 will be generated

##### LaneChanger
It handles speed the same way as LaneKeeper, however it changes the current lane in accordance with lane_change variable.

For generating a smooth path it uses a spline that is formed with two points from the start lane and two points from the target lane

In order to keep the full path, this class always generated 100 points, even if this brings the total points to more than 100.


##### Behaviour
It generates paths for keeping the same lane, changing left and changing right. After that, the Path class is used to find the cost of each path
and the path with minimum cost is used


## Cost
##### d_cost
Paths with changes in **d** coordinate will have a higher cost. This keeps the car in the same lane

##### obstructed_cost
This cost will be 1.0 if there is a car if front of us. This makes the car switch lanes

##### collision_cost
Returns 1 if the path is very close to traffic
