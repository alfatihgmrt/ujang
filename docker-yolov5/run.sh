#!/bin/bash

# Check if Xvfb is already running
#if pgrep -x Xvfb >/dev/null; then
    #echo "Xvfb is already running. Skipping start..."
#else
    # Start Xvfb
    #/usr/bin/Xvfb :1 -screen 0 1024x768x24 &
    #sleep 2 # Give Xvfb some time to start
#fi

#export DISPLAY=:1
# export PYTHONPATH=/weights:$PYTHONPATH
xhost +local:
/usr/bin/sudo /usr/bin/docker run \
       -i \
       --rm \
       --runtime nvidia \
       --network host \
       --device /dev/ttyACM0:/dev/ttyACM0 \
       --device /dev/video0:/dev/video0:mrw \
       -e DISPLAY=$DISPLAY \
       -e LD_PRELOAD=/usr/lib/aarch64-linux-gnu/libgomp.so.1 \
       -v /tmp/.X11-unix/:/tmp/.X11-unix \
       -v /home/alfatih/docker-yolov5:/weights \
       yolov5 python3.8 detect_final_12.py --source 0 --weights /weights/best_new_640.pt
