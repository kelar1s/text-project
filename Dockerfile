ARG TARGETARCH

FROM --platform=linux/${TARGETARCH} ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN set -e \
   && apt-get update \
   && apt-get install -y --no-install-recommends \
   build-essential \
   git \
   ca-certificates \
   curl \
   wget \
   cmake \
   make \
   gcc-14 g++-14 \
   && apt-get clean \
   && rm -rf /var/lib/apt/lists/*

ENV CC=gcc-14 CXX=g++-14

WORKDIR /text-project

COPY . .

CMD ["bash"]