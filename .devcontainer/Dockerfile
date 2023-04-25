FROM ubuntu:latest

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt upgrade -y \
    && apt-get install -y --no-install-recommends \
    ninja-build \
    cmake \
    clang-11 \
    # clang-tidy-11 \
    lldb-11 \
    build-essential \
    git \
    # for vcpkg
     curl zip unzip tar \    
     # for fmt build
     pkg-config    \
     dirmngr gnupg apt-transport-https ca-certificates \
     && apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF \
     && sh -c 'echo "deb https://download.mono-project.com/repo/ubuntu stable-bionic main" > /etc/apt/sources.list.d/mono-official-stable.list' \
     #  && export GNUPGHOME="$(mktemp -d)" \
     #  && gpg --batch --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF \
     #  && gpg --batch --export --armor 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF > /etc/apt/trusted.gpg.d/mono.gpg.asc \
     #  && gpgconf --kill all \
     #  && rm -rf "$GNUPGHOME" \
     #  && apt-key list | grep Xamarin \
     #  && apt-get purge -y --auto-remove gnupg dirmngr
     && apt update \
     && apt install -y mono-runtime \
     binutils curl mono-devel ca-certificates-mono nuget referenceassemblies-pcl \
     flex bison \
 #   Don't need f# or VisualBasic for the moment.. not sure if mono-devel is needed either.
 #   fsharp mono-vbnc 
     && apt-get clean \
     && rm -rf /var/lib/apt/lists/

# from https://github.com/getumen/go-xgboost/blob/ac1f86c123a7af537fc3b86c906d066b1ebed2e9/.devcontainer/Dockerfile#L23
RUN cd /tmp/ && git clone --branch v1.7.5 --recursive https://github.com/dmlc/xgboost.git \
    && cd xgboost \
    && mkdir build \
    && cmake -S . -B build \
    && cmake --build build  \
    && cmake --install build  \
    && rm -r /tmp/xgboost