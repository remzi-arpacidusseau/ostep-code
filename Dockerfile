FROM gradescope/auto-builds:ubuntu-20.04
LABEL maintainer="fsgeek@gatech.edu"

ENV DEBIAN_FRONTEND=noninteractive
COPY setup.sh /root/setup.sh
WORKDIR /root
RUN /bin/bash setup.sh
RUN rm /root/setup.sh

RUN unset DEBIAN_FRONTEND

CMD /bin/bash
