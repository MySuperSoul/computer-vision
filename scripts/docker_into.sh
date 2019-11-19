xhost +local:root 1>/dev/null 2>&1
docker exec \
  -e COLORTERM=$COLORTERM \
  -e DISPLAY=":0" \
  -u "root" \
  -it "${USER}_cv" \
  /bin/zsh
xhost -local:root 1>/dev/null 2>&1
