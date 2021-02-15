#!/bin/bash

xhost +si:localuser:root

sudo docker run --net=host --env="DISPLAY" --volume="$HOME/.Xauthority:/root/.Xauthority:rw" app:latest
