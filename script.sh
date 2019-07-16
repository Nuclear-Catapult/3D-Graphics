#!/bin/bash
./run
rm video.mp4
ffmpeg -r 30 -f image2 -s 500x500 -i pic%04d.png -vcodec libx264 -crf 25 -pix_fmt yuv420p video.mp4
rm *.png
