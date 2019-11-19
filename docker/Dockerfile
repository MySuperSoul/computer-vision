FROM ubuntu:16.04

ENV DEBIAN_FRONTEND=noninteractive

# change apt source to tsinghua.edu.cn
RUN apt-get update -y && apt-get install -y apt-transport-https
COPY sources.list /etc/apt/sources.list

# update apt and install some packages
RUN apt-get update -y && apt-get install -y \
  git \
  gdb \
  cmake \
  curl \
  htop \
  zip \
  unzip \
  bc \
  g++ \
  pkg-config \
  zlib1g-dev \
  python3 \
  python3-dev \
  python \
  python-pip \
  python-dev \
  vim \
  wget \
  uuid-dev \
  build-essential \
  zsh \
  ssh \
  tmux \
  net-tools \
  sudo \
  htop \
  openjdk-8-jdk \
  libeigen3-dev \
  libtbb2 \
  libtbb-dev \
  libjpeg-dev \
  libpng-dev \
  libtiff-dev \
  libjasper-dev \
  libdc1394-22-dev \
  libgtk2.0-dev \
  libavcodec-dev \
  libavformat-dev \
  libswscale-dev \
  python-numpy && \
  apt-get clean autoclean && \
  rm -rf /var/lib/apt/lists/*


# install gcc8
RUN apt-get update && apt-get install -y gcc-5 g++-5 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 60 \
                        --slave /usr/bin/g++ g++ /usr/bin/g++-5 \
                        --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-5 \
                        --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-5 \
                        --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-5 \
                        --slave /usr/bin/gcov gcov /usr/bin/gcov-5 && \
                        apt-get clean autoclean && rm -rf /var/lib/apt/lists/*


# install bazel
WORKDIR /tmp
RUN wget http://release.fabu.ai/deps/bazel-0.17.1-installer-linux-x86_64.sh && \
  chmod +x bazel-0.17.1-installer-linux-x86_64.sh && \
  ./bazel-0.17.1-installer-linux-x86_64.sh --prefix=/usr && \
  cd / && rm -rf /tmp/*

# install opencv-3.3.1
WORKDIR /tmp
RUN wget http://release.fabu.ai/deps/opencv-3.3.1.download.tar.gz && \
  tar -zxvf opencv-3.3.1.download.tar.gz && \
  mkdir -p opencv-3.3.1/build && \
  cd opencv-3.3.1/build && \
  cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local/opencv-3.3.1 \
    .. && \
  make -j"$(nproc)" && \
  make install -j"$(nproc)" && \
  cd / && rm -rf /tmp/*
# RUN mkdir -p /usr/local/opencv-3.3.1 && wget -O- http://release.fabu.ai/deps/opencv-3.3.1.tar.gz | tar -zxvf - --strip-components=1 -C /usr/local/opencv-3.3.1 && echo /usr/local/opencv-3.3.1/lib > /etc/ld.so.conf.d/opencv-3.3.1.conf && ldconfig
