"""
Consume LIDAR measurement file and create an image for display.

Adafruit invests time and resources providing this open source code.
Please support Adafruit and open source hardware by purchasing
products from Adafruit!

Written by Dave Astels for Adafruit Industries
Copyright (c) 2019 Adafruit Industries
Licensed under the MIT license.

All text above must be included in any redistribution.
"""

import os
from math import cos, sin, pi, floor
#from rplidar import RPLidarfrom rplidar import RPLidar
from rplidar import RPLidar


# Setup the RPLidar
PORT_NAME = '/dev/ttyUSB0'
#lidar = RPLidar(None, PORT_NAME)
lidar = RPLidar('/dev/ttyUSB0')

# used to scale data to fit on the screen
max_distance = 0

def amand(angle, distance):
    if 200000:
        if angle >= 60 and angle < 120:
            print("in front")
        elif angle >= 155 and angle < 220:
            print("to the left")
        elif angle >= 250 and angle < 290:
            print("behind")
        
        else:
           print("right")

try:
    #print(lidar.info)
    for scan in lidar.iter_scans():
        for (_, angle, distance) in scan:
            amand(angle, distance)


except KeyboardInterrupt:
    print('Stoping.')
lidar.stop()
lidar.disconnect()
