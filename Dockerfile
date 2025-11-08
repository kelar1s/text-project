FROM ubuntu:24.04

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

# Указываем, какой компилятор использовать
ENV CC=gcc-14 CXX=g++-14

# Рабочая папка
WORKDIR /text-project

# Копируем проект
COPY . .

# Открываем bash для разработки
CMD ["bash"]
