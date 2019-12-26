#!/usr/bin/env bash

LOCAL_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"
source $LOCAL_DIR/scripts/set_env.sh

function main() {
  IMG="yifeihuang/cv:${DOCKER_VERSION}"
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
    -v $LOCAL_DIR:$DOCKER_HOME/computer-vision \
    -v $LOCAL_DIR/WORKSPACE:$DOCKER_HOME/WORKSPACE \
    -v $LOCAL_DIR/third_party:$DOCKER_HOME/third_party \
    -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
    -v /media:/media \
    -v /dev/null:/dev/raw1394 \
    -v $HOME/.cache:$DOCKER_HOME/.cache \
    -w $DOCKER_HOME \
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
    docker exec $DOCKER_NAME bash -c "${DOCKER_HOME}/computer-vision/scripts/before_start.sh"
  fi

  echo "Finished setting up cv docker environment. Now you can enter with: bash scripts/docker_into.sh"
  echo "Enjoy!"
}

main
