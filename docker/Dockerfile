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
