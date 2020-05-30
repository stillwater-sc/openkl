# OpenKL: Virtual Machine for Cloud-Native Supercomputing

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/28b588921aa34231869a034f6283fdf9)](https://app.codacy.com/gh/stillwater-sc/openkl?utm_source=github.com&utm_medium=referral&utm_content=stillwater-sc/openkl&utm_campaign=Badge_Grade_Dashboard)


Container-based cloud-native supercomputing. The run-time container is a gRPC server that listens to a command set
tailored to the requirements of distributed memory algorithms.

# Architecture

In gRPC, a client application can directly call a method on a server application on a different machine as if it were a local object, making it easier for you to create distributed applications and services. As in many RPC systems, gRPC is based around the idea of defining a service, specifying the methods that can be called remotely with their parameters and return types. On the server side, the server implements this interface and runs a gRPC server to handle client calls. On the client side, the client has a stub (referred to as just a client in some languages) that provides the same methods as the server.

gRPC can use protocol buffers as both its Interface Definition Language (IDL) and as its underlying message interchange format. 

gRPC clients and servers can run and talk to each other in a variety of environments - from servers in the cloud to 
your own desktop - and can be written in any of gRPC’s supported languages. You can create a gRPC server in Java 
with clients in Go, Python, or Ruby. 

Furthermore, the latest Google APIs will have gRPC versions of their interfaces, letting you easily build Google functionality into your applications.
OpenKL will also publish gRPC versions of its interface, so it can be served and called from the widest possible
universe of clouds and clients.

# Installation

## prerequisites

OpenKL cloud-native DMM depends on gRPC. Install the [prerequisites](https://github.com/grpc/grpc/blob/master/BUILDING.md#pre-requisites) first.

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
