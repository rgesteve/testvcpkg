FROM ubuntu:latest

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
    ninja-build \
    cmake \
#    clang-11 \
#    clang-tidy-11 \
    build-essential \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/
