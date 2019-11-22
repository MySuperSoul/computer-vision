#!/usr/bin/env bash

LOCAL_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

function main() {
  IMG="yifeihuang/cv:latest"
  DOCKER_NAME="${USER}_cv"

  docker ps -a --format "{{.Names}}" | grep "$DOCKER_NAME" 1>/dev/null
  if [ $? == 0 ]; then
      if [[ "$(docker inspect --format='{{.Config.Image}}' $DOCKER_NAME 2> /dev/null)" != "$IMG" ]]; then
          rm -rf $HOME/.cache/bazel/*
      fi
      docker stop $DOCKER_NAME 1>/dev/null
      docker rm -v -f $DOCKER_NAME 1>/dev/null
  fi

  local display=""
  if [[ -z ${DISPLAY} ]];then
      display=":0"
  else
      display="${DISPLAY}"
  fi

  USER_ID=$(id -u)
  GRP=$(id -g -n)
  GRP_ID=$(id -g)
  LOCAL_HOST=`hostname`
  DOCKER_HOME="/home/$USER"
  if [ "$USER" == "root" ];then
      DOCKER_HOME="/root"
  fi
  if [ ! -d "$HOME/.cache" ];then
      mkdir "$HOME/.cache"
  fi

  eval docker run -it -d \
    --name $DOCKER_NAME \
    -e DISPLAY=$display \
    -e DOCKER_USER=${USER} \
    -e USER=${USER} \
    -e DOCKER_USER_ID=$USER_ID \
    -e DOCKER_GRP=$GRP \
    -e DOCKER_GRP_ID=$GRP_ID \
    -e DOCKER_HOME=$DOCKER_HOME \
    -e DOCKER_IMG=$IMG \
    -v $LOCAL_DIR:/computer-vision \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    -v /media:/media \
    -v /dev/null:/dev/raw1394 \
    -w /computer-vision \
    --dns=114.114.114.114 \
    --add-host in_docker:127.0.0.1 \
    --hostname in_docker \
    --shm-size 2G \
    $IMG \
    /bin/bash

  if [ $? -ne 0 ];then
    error "Failed to start docker container \"${DOCKER_NAME}\" based on image: $IMG"
    exit 1
  fi

  if [ "${USER}" != "root" ]; then
    docker exec $DOCKER_NAME bash -c '/computer-vision/scripts/before_start.sh'
  fi

  echo "Finished setting up cv docker environment. Now you can enter with: bash scripts/docker_into.sh"
  echo "Enjoy!"
}

main
