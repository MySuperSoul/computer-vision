#!/usr/bin/env bash

LOCAL_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

IN_DOCKER_USER="root"

eval docker create -it \
  --name "${USER}_cv" \
  -e DISPLAY=":0" \
  -e DOCKER_USER=$IN_DOCKER_USER \
  -e USER=$IN_DOCKER_USER \
  -e DOCKER_USER_ID=$(id -u) \
  -e DOCKER_GRP=$(id -g -n) \
  -e DOCKER_GPR_ID=$(id -g) \
  -e DOCKER_HOME="/home/${IN_DOCKER_USER}" \
  -v $LOCAL_DIR:/cv_projects \
  -v /tmp/.X11-unix/X0:/tmp/.X11-unix/X0:rw \
  -v /media:/media \
  -w /cv_projects \
  --dns=114.114.114.114 \
  --add-host in_docker:127.0.0.1 \
  --hostname in_docker \
  --shm-size 2G \
  cv:0.1

docker start "${USER}_cv"
