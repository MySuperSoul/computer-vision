xhost +local:root 1>/dev/null 2>&1
docker exec \
  -e COLORTERM=$COLORTERM \
  -u ${USER} \
  -it "${USER}_cv" \
  /bin/bash
xhost -local:root 1>/dev/null 2>&1
