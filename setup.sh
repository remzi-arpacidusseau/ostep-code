#!/bin/bash

export DEBIAN_FRONTEND=noninteractive

# wget -O - https://ppa.bitanical.com/pward8@gatech.edu.gpg.key|apt-key add - && \
#    echo "deb https://ppa.bitanical.com/apt/debian bionic main" >> /etc/apt/sources.list.d/ppa.bitanical.list

apt-get update && apt-get install -y \
    libgmp-dev \
    gcc-multilib \
    valgrind \
    portmap \
    rpcbind \
    libcurl4-openssl-dev \
    bzip2 \
    imagemagick \
    libmagickcore-dev \
    libssl-dev \
    llvm \
    net-tools \
    libtool \
    pkg-config

# apt-get install -y --no-check-certificate \
#    grpc-cs6200 \
#    protobuf-cs6200

python3 -m pip install --upgrade pip

python3 -m pip install --upgrade \
    future \
    cryptography \
    pyopenssl \
    ndg-httpsclient \
    pyasn1

mkdir -p /autograder/source


if [ -f "deploykey" ]; then
    mkdir -p /root/.ssh
    cp ssh_config /root/.ssh/config
    cp deploykey /root/.ssh/deploykey
    chmod 0600 /root/.ssh/deploykey
    ssh-add deploykey
    ssh-keyscan -H github.com >> /etc/ssh/ssh_known_hosts

    cd /autograder/source
    git clone git@github.com:gt-cs6200/gt-cs6200-graders.git

    # Add a non-sudo user and switch to it
    adduser --disabled-password --gecos "" gradeuser
    su gradeuser

    # At this point we should be ready to start up the tests (or use the
    # container)
fi






