FROM gcc:10.1.0
LABEL Theodore Omtzigt (theo@stillwater-sc.com)

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y build-essential autoconf libtool pkg-config git curl cmake

RUN cd /tmp && \
    git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc && \
    cd grpc && \
    git submodule update --init && \
    mkdir -p cmake/build && \
    mkdir -p /opt/grpc && \
    cd cmake/build && \
    cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/opt/grpc ../.. && \
    make -j && \
    make install


