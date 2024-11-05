- `Dockerfile` (erased .txt): contains dependencies
- `build.sh`: builds docker container
- `run.sh`: run program in the container

# Code explanation (IMPORTANT)
## `run.sh`
This file compiles the necessary commands to __run the object detection program in Docker RIGHT AFTER booting up__, including the arguments.<br>
Why? it simplifies the program execution (imagine having to type the long ahh commands in the terminal, we are way too lazy). 
More: https://docs.docker.com/reference/cli/docker/container/run/

- `#!/bin/bash` : let it be
- `#export DISPLAY=:1` : activate the virtual display
- `--i` : keep STDIN (one of the standard streams) open even if not attached
- `--rm` : automatically remove the container and its associated anonymous volumes when it exits
- `--runtime nivdia` : NVIDIA is used as the runtime
- `--network host` : connect to host network
- `--device /dev/ttyACM0:/dev/ttyACM0` : add host's /dev/ttyACM0 port into the Docker container (__for the Serial communication to Teensy__)
- `--device /dev/video0:/dev/video0:mrw`: almost same as above (__for the camera__)
- `-e DISPLAY=$DISPLAY` : set environment variable for the display
- `-e LD_PRELOAD=/usr/lib/aarch64-linux-gnu/libgomp.so.1` : almost same as above
- `-v /tmp/.X11-unix/:/tmp/.X11-unix` : mounts the current directory into the container at the /tmp/.X11-unix/, sets it as the working directory
- `-v /home/alfatih/docker-yolov5:/weights` : almost same as above (__to access the model's weights__)
- the rest is just YOLOv5's command to run the detection program

```
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
```
