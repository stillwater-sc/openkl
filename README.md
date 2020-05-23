# OpenKL: Virtual Machine for Cloud-Native Supercomputing

Container-based cloud-native supercomputing. The run-time container is a GRPC server that listens to a command set
tailored to the requirements of distributed memory algorithms.

# Architecture


# Installation

## C++ Installation - Windows
If you only need the protoc binary, you can download it from the release page:

https://github.com/protocolbuffers/protobuf/releases/latest

In the downloads section, download the zip file protoc-$VERSION-win32.zip. It contains the protoc binary as well as public proto files of protobuf library.

Protobuf and its dependencies can be installed directly by using vcpkg:

> vcpkg install protobuf protobuf:x64-windows

If zlib support is desired, you'll also need to install the zlib feature:

> vcpkg install protobuf[zlib] protobuf[zlib]:x64-windows

See https://github.com/Microsoft/vcpkg for more information.

To build from source using Microsoft Visual C++, see cmake/README.md.
