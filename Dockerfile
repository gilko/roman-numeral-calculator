FROM ubuntu:14.04
MAINTAINER Gabe Ilko <gilko@pillartechnology.com>
RUN apt-get update && apt-get install -y \
  build-essential \
  check \
