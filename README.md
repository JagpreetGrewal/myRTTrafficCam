# myRTTrafficCam
A primitive application to pull data from a live youtube stream and process it.

Note: Features are currently in development. Before compiling, make sure OpenCV 4.5.1 and GStreamer 1.18.4 are installed (more package details will be provided later).

## Compiling
Input the following commands to compile:
```bash
mkdir -p build
mkdir -p bin
cd build && cmake ..
make -jN
```

## Running
Input the following commands to run the program:
```bash
cd script
./startStream.sh
```
Please ignore the other script, it is used by this one.
If you wish to modify parameters like the url, start time, or end time, then modify the startStream.sh script.
For livestreams, start close to 0:00:0 for live footage.
Starting directly at 0:00:0 may cause issues with downloading the video.