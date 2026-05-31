FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    curl \
    wget \
    gnupg \
    lsb-release \
    software-properties-common \
    build-essential \
    cmake \
    git \
    nano \
    vim \
    iputils-ping \
    net-tools

RUN wget https://packages.osrfoundation.org/gazebo.gpg -O /tmp/gazebo.gpg && \
    gpg --dearmor /tmp/gazebo.gpg && \
    mv /tmp/gazebo.gpg.gpg /usr/share/keyrings/pkgs-osrf-archive-keyring.gpg

RUN echo "deb [signed-by=/usr/share/keyrings/pkgs-osrf-archive-keyring.gpg] \
http://packages.osrfoundation.org/gazebo/ubuntu-stable noble main" \
> /etc/apt/sources.list.d/gazebo-stable.list

RUN apt-get update && \
    apt-get install -y gz-harmonic

RUN echo "source /usr/share/gz/setup.sh" >> /root/.bashrc

WORKDIR /workspace

CMD ["/bin/bash"]
