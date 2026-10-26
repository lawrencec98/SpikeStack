# Event Generator module

This module generates event data from frame-based videos.

There are two main challenges in turning frame-based videos into DVS-like event streams.
1. Temporal interpolation - frame-based videos have low temporal resolution but event sensors have high temporal resolution.
A challenge is filling in the gaps between frames with interpolated event data.
2. Pixel brightness change thresholding - how to keep track of pixel brightness changes and determine whether an event should fire.


# Notes
* Video to be ingested by gstreamer.
    ** chose gstreamer because it is better than OpenCV for low latency and real-time video streaming.
    ** potential to also add network sources.


# Dependencies
* gstreamer (https://gstreamer.freedesktop.org/documentation/installing/on-linux.html?gi-language=c)
