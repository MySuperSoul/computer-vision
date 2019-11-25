### computer-vision

- OS: ubuntu-16.04
- Dependency: docker
- Usage: 

```bash
git clone https://github.com/MySuperSoul/computer-vision.git

docker pull yifeihuang/cv:latest

cd computer-vision && bash scripts/docker_start.sh

bash scripts/docker_into.sh

# now you are in docker env
bazel build computer-vision/assignments/assignment{num}:all
```