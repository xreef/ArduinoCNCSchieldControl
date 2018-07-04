# ArduinoCNCSchieldControl
A simple program to control CNC Shield to calculate step per millimeter and move/test on axis.

```
<axis> 		= x, y, z
<status> 	= 1 (activate), 0 (deactivate)
<direction> 	= 1 (invert direction), 0 (normal direction)
<speed> 		= impulse delay in microsenconds
```

Commands:
```
g,<axis>,<status> 		--> Example: g,x,1 (start x movement)
d,<axis>,<direction> 	--> Example: d,x,1 (set direction to inverse)
v,<axis>,<speed> 		--> Example: v,x,2000000 (set delay step to 2000000 microseconds)
```

Usage, 
 - position the spindle to the edge (<g,x,1>, when you are near the edge <g,x,0>) 
 - then copy step number (ES: 2345678) and mark the position of splindle (ES: 23mm from edge)
 - start splindle movement to the other edge of axis (<d,x,1> change direction <g,x,1> start movement) 
 - stop near the other edge 
 - then copy step number (ES: 2654678) and mark the position of splindle (ES: 166mm from the first edge)
 - calculate total step (ES: 2654678 - 2345678 = 309000 total step) then calculate distance traveled (ES: 166mm - 23mm = 143mm)
 - calculate step/mm (ES: 309000/143=2160,839160839161)
 
More distance traveled more precision you can obtain.