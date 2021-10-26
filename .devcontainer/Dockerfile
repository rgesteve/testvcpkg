FROM ubuntu:latest

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt upgrade \
    && apt-get install -y --no-install-recommends \
    ninja-build \
    cmake \
#    clang-11 \
#    clang-tidy-11 \
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
#   Don't need f# or VisualBasic for the moment.. not sure if mono-devel is needed either.
#   fsharp mono-vbnc 
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/
