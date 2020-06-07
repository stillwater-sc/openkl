# Clone the repository (including submodules)
Before building, you need to clone the gRPC github repository and download submodules containing source code for gRPC's dependencies (that's done by the submodule command or --recursive flag). Use following commands to clone the gRPC repository at the latest stable release tag

## Unix
 $ git clone -b RELEASE_TAG_HERE https://github.com/grpc/grpc
 $ cd grpc
 $ git submodule update --init
## Windows
> git clone -b RELEASE_TAG_HERE https://github.com/grpc/grpc
> cd grpc
> git submodule update --init
NOTE: The bazel build tool uses a different model for dependencies. You only need to worry about downloading submodules if you're building with something else than bazel (e.g. cmake).


# Building with CMake
## Linux/Unix, Using Make
Run from grpc directory after cloning the repo with --recursive or updating submodules.

$ mkdir -p cmake/build
$ cd cmake/build
$ cmake ../..
$ make
If you want to build shared libraries (.so files), run cmake with -DBUILD_SHARED_LIBS=ON.

## Windows, Using Visual Studio 2015 or 2017
When using the "Visual Studio" generator, cmake will generate a solution (grpc.sln) that contains a VS project for every target defined in CMakeLists.txt (+ few extra convenience projects added automatically by cmake). After opening the solution with Visual Studio you will be able to browse and build the code.

> @rem Run from grpc directory after cloning the repo with --recursive or updating submodules.
> md build
> cd build
> cmake .. -G "Visual Studio 15 2017 Win64"
> cmake --build . --config Release
> cmake --install . --config Release    # needs admin privilege

# Install after build
Perform the following steps to install gRPC using CMake.

 * Set -DgRPC_INSTALL=ON
 * Build the install target

The install destination is controlled by the CMAKE_INSTALL_PREFIX variable.

If you are running CMake v3.13 or newer you can build gRPC's dependencies in "module" mode and install them alongside gRPC in a single step. 
Example

> @rem inside cmake/build
> cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DgRPC_INSTALL=ON \
  -DgRPC_BUILD_TESTS=OFF \
  -DgRPC_SSL_PROVIDER=package \
  ../..



-------------------
#!/bin/bash
# Copyright 2017 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -ex

cd "$(dirname "$0")/../../.."

# Install openssl (to use instead of boringssl)
apt-get update && apt-get install -y libssl-dev

# Install CMake 3.16
apt-get update && apt-get install -y wget
wget -q -O cmake-linux.sh https://github.com/Kitware/CMake/releases/download/v3.16.1/cmake-3.16.1-Linux-x86_64.sh
sh cmake-linux.sh -- --skip-license --prefix=/usr
rm cmake-linux.sh

# Install gRPC and its dependencies
mkdir -p "cmake/build"
pushd "cmake/build"
cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DgRPC_INSTALL=ON \
  -DgRPC_BUILD_TESTS=OFF \
  -DgRPC_SSL_PROVIDER=package \
  ../..
make -j4 install
popd

# Build helloworld example using cmake
mkdir -p "examples/cpp/helloworld/cmake/build"
pushd "examples/cpp/helloworld/cmake/build"
cmake ../..
make
popd


output of cmake --install .
```
C:\Users\tomtz\Documents\dev\clones\grpc\cmake\build>cmake --install . --config Release
-- Installing: C:/Program Files/grpc/lib/absl_bad_optional_access.lib
-- Installing: C:/Program Files/grpc/lib/absl_base.lib
-- Installing: C:/Program Files/grpc/lib/absl_civil_time.lib
-- Installing: C:/Program Files/grpc/lib/absl_dynamic_annotations.lib
-- Installing: C:/Program Files/grpc/lib/absl_int128.lib
-- Installing: C:/Program Files/grpc/lib/absl_log_severity.lib
-- Installing: C:/Program Files/grpc/lib/absl_raw_logging_internal.lib
-- Installing: C:/Program Files/grpc/lib/absl_spinlock_wait.lib
-- Installing: C:/Program Files/grpc/lib/absl_str_format_internal.lib
-- Installing: C:/Program Files/grpc/lib/absl_strings.lib
-- Installing: C:/Program Files/grpc/lib/absl_strings_internal.lib
-- Installing: C:/Program Files/grpc/lib/absl_throw_delegate.lib
-- Installing: C:/Program Files/grpc/lib/absl_time.lib
-- Installing: C:/Program Files/grpc/lib/absl_time_zone.lib
-- Installing: C:/Program Files/grpc/lib/cares.lib
-- Installing: C:/Program Files/grpc/lib/ssl.lib
-- Installing: C:/Program Files/grpc/lib/crypto.lib
-- Installing: C:/Program Files/grpc/lib/zlibstatic.lib
-- Installing: C:/Program Files/grpc/lib/address_sorting.lib
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/atm.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/atm_gcc_atomic.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/atm_gcc_sync.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/atm_windows.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/byte_buffer.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/byte_buffer_reader.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/compression_types.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/connectivity_state.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/fork.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/gpr_slice.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/gpr_types.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/grpc_types.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/log.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/port_platform.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/propagation_bits.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/slice.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/status.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/sync.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/sync_abseil.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/sync_custom.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/sync_generic.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/sync_posix.h
-- Installing: C:/Program Files/grpc/include/grpc/impl/codegen/sync_windows.h
-- Installing: C:/Program Files/grpc/include/grpc/support/alloc.h
-- Installing: C:/Program Files/grpc/include/grpc/support/atm.h
-- Installing: C:/Program Files/grpc/include/grpc/support/atm_gcc_atomic.h
-- Installing: C:/Program Files/grpc/include/grpc/support/atm_gcc_sync.h
-- Installing: C:/Program Files/grpc/include/grpc/support/atm_windows.h
-- Installing: C:/Program Files/grpc/include/grpc/support/cpu.h
-- Installing: C:/Program Files/grpc/include/grpc/support/log.h
-- Installing: C:/Program Files/grpc/include/grpc/support/log_windows.h
-- Installing: C:/Program Files/grpc/include/grpc/support/port_platform.h
-- Installing: C:/Program Files/grpc/include/grpc/support/string_util.h
-- Installing: C:/Program Files/grpc/include/grpc/support/sync.h
-- Installing: C:/Program Files/grpc/include/grpc/support/sync_abseil.h
-- Installing: C:/Program Files/grpc/include/grpc/support/sync_custom.h
-- Installing: C:/Program Files/grpc/include/grpc/support/sync_generic.h
-- Installing: C:/Program Files/grpc/include/grpc/support/sync_posix.h
-- Installing: C:/Program Files/grpc/include/grpc/support/sync_windows.h
-- Installing: C:/Program Files/grpc/include/grpc/support/thd_id.h
-- Installing: C:/Program Files/grpc/include/grpc/support/time.h
-- Installing: C:/Program Files/grpc/lib/gpr.lib
-- Installing: C:/Program Files/grpc/include/grpc/byte_buffer.h
-- Installing: C:/Program Files/grpc/include/grpc/byte_buffer_reader.h
-- Installing: C:/Program Files/grpc/include/grpc/census.h
-- Installing: C:/Program Files/grpc/include/grpc/compression.h
-- Installing: C:/Program Files/grpc/include/grpc/fork.h
-- Installing: C:/Program Files/grpc/include/grpc/grpc.h
-- Installing: C:/Program Files/grpc/include/grpc/grpc_posix.h
-- Installing: C:/Program Files/grpc/include/grpc/grpc_security.h
-- Installing: C:/Program Files/grpc/include/grpc/grpc_security_constants.h
-- Installing: C:/Program Files/grpc/include/grpc/load_reporting.h
-- Installing: C:/Program Files/grpc/include/grpc/slice.h
-- Installing: C:/Program Files/grpc/include/grpc/slice_buffer.h
-- Installing: C:/Program Files/grpc/include/grpc/status.h
-- Installing: C:/Program Files/grpc/include/grpc/support/workaround_list.h
-- Installing: C:/Program Files/grpc/lib/grpc.lib
-- Up-to-date: C:/Program Files/grpc/include/grpc/byte_buffer.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/byte_buffer_reader.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/census.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/compression.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/fork.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/grpc.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/grpc_posix.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/grpc_security_constants.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/load_reporting.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/slice.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/slice_buffer.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/status.h
-- Up-to-date: C:/Program Files/grpc/include/grpc/support/workaround_list.h
-- Installing: C:/Program Files/grpc/lib/grpc_unsecure.lib
-- Installing: C:/Program Files/grpc/include/grpc++/alarm.h
-- Installing: C:/Program Files/grpc/include/grpc++/channel.h
-- Installing: C:/Program Files/grpc/include/grpc++/client_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/completion_queue.h
-- Installing: C:/Program Files/grpc/include/grpc++/create_channel.h
-- Installing: C:/Program Files/grpc/include/grpc++/create_channel_posix.h
-- Installing: C:/Program Files/grpc/include/grpc++/ext/health_check_service_server_builder_option.h
-- Installing: C:/Program Files/grpc/include/grpc++/generic/async_generic_service.h
-- Installing: C:/Program Files/grpc/include/grpc++/generic/generic_stub.h
-- Installing: C:/Program Files/grpc/include/grpc++/grpc++.h
-- Installing: C:/Program Files/grpc/include/grpc++/health_check_service_interface.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/call.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/channel_argument_option.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/client_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/async_stream.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/async_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/byte_buffer.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/call.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/call_hook.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/channel_interface.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/client_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/client_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/completion_queue.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/completion_queue_tag.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/config.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/config_protobuf.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/core_codegen.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/core_codegen_interface.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/create_auth_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/grpc_library.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/metadata_map.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/method_handler_impl.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/proto_utils.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/rpc_method.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/rpc_service_method.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/security/auth_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/serialization_traits.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/server_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/server_interface.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/service_type.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/slice.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/status.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/status_code_enum.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/string_ref.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/stub_options.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/sync_stream.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/codegen/time.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/grpc_library.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/method_handler_impl.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/rpc_method.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/rpc_service_method.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/serialization_traits.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/server_builder_option.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/server_builder_plugin.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/server_initializer.h
-- Installing: C:/Program Files/grpc/include/grpc++/impl/service_type.h
-- Installing: C:/Program Files/grpc/include/grpc++/resource_quota.h
-- Installing: C:/Program Files/grpc/include/grpc++/security/auth_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/security/auth_metadata_processor.h
-- Installing: C:/Program Files/grpc/include/grpc++/security/credentials.h
-- Installing: C:/Program Files/grpc/include/grpc++/security/server_credentials.h
-- Installing: C:/Program Files/grpc/include/grpc++/server.h
-- Installing: C:/Program Files/grpc/include/grpc++/server_builder.h
-- Installing: C:/Program Files/grpc/include/grpc++/server_context.h
-- Installing: C:/Program Files/grpc/include/grpc++/server_posix.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/async_stream.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/async_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/byte_buffer.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/channel_arguments.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/config.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/slice.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/status.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/status_code_enum.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/string_ref.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/stub_options.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/sync_stream.h
-- Installing: C:/Program Files/grpc/include/grpc++/support/time.h
-- Installing: C:/Program Files/grpc/include/grpcpp/alarm.h
-- Installing: C:/Program Files/grpc/include/grpcpp/alarm_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/channel.h
-- Installing: C:/Program Files/grpc/include/grpcpp/channel_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/client_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/completion_queue.h
-- Installing: C:/Program Files/grpc/include/grpcpp/completion_queue_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/create_channel.h
-- Installing: C:/Program Files/grpc/include/grpcpp/create_channel_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/create_channel_posix.h
-- Installing: C:/Program Files/grpc/include/grpcpp/create_channel_posix_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/ext/health_check_service_server_builder_option.h
-- Installing: C:/Program Files/grpc/include/grpcpp/generic/async_generic_service.h
-- Installing: C:/Program Files/grpc/include/grpcpp/generic/generic_stub.h
-- Installing: C:/Program Files/grpc/include/grpcpp/generic/generic_stub_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/grpcpp.h
-- Installing: C:/Program Files/grpc/include/grpcpp/health_check_service_interface.h
-- Installing: C:/Program Files/grpc/include/grpcpp/health_check_service_interface_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/call.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/channel_argument_option.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/client_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_generic_service.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_stream.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_stream_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_unary_call_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/byte_buffer.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/call.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/call_hook.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/call_op_set.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/call_op_set_interface.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/callback_common.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/channel_interface.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_callback.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_callback_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_context_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_interceptor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/completion_queue.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/completion_queue_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/completion_queue_tag.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/config.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/config_protobuf.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/core_codegen.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/core_codegen_interface.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/create_auth_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/delegating_channel.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/grpc_library.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/intercepted_channel.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/interceptor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/interceptor_common.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/message_allocator.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/metadata_map.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/method_handler.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/method_handler_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/proto_buffer_reader.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/proto_buffer_writer.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/proto_utils.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/rpc_method.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/rpc_service_method.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/security/auth_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/serialization_traits.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_callback.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_callback_handlers.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_callback_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_context_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_interceptor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_interface.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/service_type.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/slice.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/status.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/status_code_enum.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/string_ref.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/stub_options.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/sync.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/sync_stream.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/sync_stream_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/codegen/time.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/grpc_library.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/method_handler_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/rpc_method.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/rpc_service_method.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/serialization_traits.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/server_builder_option.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/server_builder_option_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/server_builder_plugin.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/server_initializer.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/server_initializer_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/impl/service_type.h
-- Installing: C:/Program Files/grpc/include/grpcpp/resource_quota.h
-- Installing: C:/Program Files/grpc/include/grpcpp/resource_quota_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/auth_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/auth_metadata_processor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/auth_metadata_processor_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/credentials.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/credentials_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/server_credentials.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/server_credentials_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/tls_credentials_options.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server_builder.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server_builder_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server_posix.h
-- Installing: C:/Program Files/grpc/include/grpcpp/server_posix_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/async_stream.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/async_stream_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/async_unary_call.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/async_unary_call_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/byte_buffer.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/channel_arguments.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/channel_arguments_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/client_callback.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/client_callback_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/client_interceptor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/config.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/interceptor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/message_allocator.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/method_handler.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/proto_buffer_reader.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/proto_buffer_writer.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/server_callback.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/server_callback_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/server_interceptor.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/slice.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/status.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/status_code_enum.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/string_ref.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/stub_options.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/sync_stream.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/sync_stream_impl.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/time.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/validate_service_config.h
-- Installing: C:/Program Files/grpc/lib/grpc++.lib
-- Installing: C:/Program Files/grpc/include/grpcpp/security/alts_context.h
-- Installing: C:/Program Files/grpc/include/grpcpp/security/alts_util.h
-- Installing: C:/Program Files/grpc/lib/grpc++_alts.lib
-- Installing: C:/Program Files/grpc/include/grpc++/support/error_details.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/error_details.h
-- Installing: C:/Program Files/grpc/include/grpcpp/support/error_details_impl.h
-- Installing: C:/Program Files/grpc/lib/grpc++_error_details.lib
-- Installing: C:/Program Files/grpc/include/grpc++/ext/proto_server_reflection_plugin.h
-- Installing: C:/Program Files/grpc/include/grpcpp/ext/proto_server_reflection_plugin.h
-- Installing: C:/Program Files/grpc/include/grpcpp/ext/proto_server_reflection_plugin_impl.h
-- Installing: C:/Program Files/grpc/lib/grpc++_reflection.lib
-- Up-to-date: C:/Program Files/grpc/include/grpc++/alarm.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/channel.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/client_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/completion_queue.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/create_channel.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/create_channel_posix.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/ext/health_check_service_server_builder_option.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/generic/async_generic_service.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/generic/generic_stub.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/grpc++.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/health_check_service_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/call.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/channel_argument_option.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/client_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/async_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/async_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/byte_buffer.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/call.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/call_hook.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/channel_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/client_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/client_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/completion_queue.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/completion_queue_tag.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/config.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/config_protobuf.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/core_codegen.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/core_codegen_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/create_auth_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/grpc_library.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/metadata_map.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/method_handler_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/proto_utils.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/rpc_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/rpc_service_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/security/auth_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/serialization_traits.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/server_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/server_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/service_type.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/slice.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/status.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/status_code_enum.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/string_ref.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/stub_options.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/sync_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/time.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/grpc_library.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/method_handler_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/rpc_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/rpc_service_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/serialization_traits.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/server_builder_option.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/server_builder_plugin.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/server_initializer.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/service_type.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/resource_quota.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/security/auth_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/security/auth_metadata_processor.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/security/credentials.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/security/server_credentials.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/server.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/server_builder.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/server_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/server_posix.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/async_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/async_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/byte_buffer.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/channel_arguments.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/config.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/slice.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/status.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/status_code_enum.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/string_ref.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/stub_options.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/sync_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpc++/support/time.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/alarm.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/alarm_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/channel.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/channel_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/client_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/completion_queue.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/completion_queue_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/create_channel.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/create_channel_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/create_channel_posix.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/create_channel_posix_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/ext/health_check_service_server_builder_option.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/generic/async_generic_service.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/generic/generic_stub.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/generic/generic_stub_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/grpcpp.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/health_check_service_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/health_check_service_interface_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/call.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/channel_argument_option.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/client_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_generic_service.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_stream_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/async_unary_call_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/byte_buffer.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/call.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/call_hook.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/call_op_set.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/call_op_set_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/callback_common.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/channel_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_callback.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_callback_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_context_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_interceptor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/client_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/completion_queue.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/completion_queue_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/completion_queue_tag.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/config.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/config_protobuf.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/core_codegen.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/core_codegen_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/create_auth_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/delegating_channel.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/grpc_library.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/intercepted_channel.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/interceptor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/interceptor_common.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/message_allocator.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/metadata_map.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/method_handler.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/method_handler_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/proto_buffer_reader.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/proto_buffer_writer.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/proto_utils.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/rpc_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/rpc_service_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/security/auth_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/serialization_traits.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_callback.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_callback_handlers.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_callback_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_context_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_interceptor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/server_interface.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/service_type.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/slice.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/status.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/status_code_enum.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/string_ref.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/stub_options.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/sync.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/sync_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/sync_stream_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/time.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/grpc_library.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/method_handler_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/rpc_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/rpc_service_method.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/serialization_traits.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/server_builder_option.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/server_builder_option_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/server_builder_plugin.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/server_initializer.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/server_initializer_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/service_type.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/resource_quota.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/resource_quota_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/auth_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/auth_metadata_processor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/auth_metadata_processor_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/credentials.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/credentials_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/server_credentials.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/server_credentials_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/security/tls_credentials_options.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server_builder.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server_builder_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server_context.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server_posix.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/server_posix_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/async_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/async_stream_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/async_unary_call.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/async_unary_call_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/byte_buffer.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/channel_arguments.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/channel_arguments_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/client_callback.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/client_callback_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/client_interceptor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/config.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/interceptor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/message_allocator.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/method_handler.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/proto_buffer_reader.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/proto_buffer_writer.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/server_callback.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/server_callback_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/server_interceptor.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/slice.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/status.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/status_code_enum.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/string_ref.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/stub_options.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/sync_stream.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/sync_stream_impl.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/time.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/support/validate_service_config.h
-- Installing: C:/Program Files/grpc/lib/grpc++_unsecure.lib
-- Up-to-date: C:/Program Files/grpc/include/grpc++/impl/codegen/config_protobuf.h
-- Up-to-date: C:/Program Files/grpc/include/grpcpp/impl/codegen/config_protobuf.h
-- Installing: C:/Program Files/grpc/lib/grpc_plugin_support.lib
-- Installing: C:/Program Files/grpc/include/grpcpp/ext/channelz_service_plugin.h
-- Installing: C:/Program Files/grpc/include/grpcpp/ext/channelz_service_plugin_impl.h
-- Installing: C:/Program Files/grpc/lib/grpcpp_channelz.lib
-- Installing: C:/Program Files/grpc/lib/upb.lib
-- Installing: C:/Program Files/grpc/bin/grpc_cpp_plugin.exe
-- Installing: C:/Program Files/grpc/bin/grpc_csharp_plugin.exe
-- Installing: C:/Program Files/grpc/bin/grpc_node_plugin.exe
-- Installing: C:/Program Files/grpc/bin/grpc_objective_c_plugin.exe
-- Installing: C:/Program Files/grpc/bin/grpc_php_plugin.exe
-- Installing: C:/Program Files/grpc/bin/grpc_python_plugin.exe
-- Installing: C:/Program Files/grpc/bin/grpc_ruby_plugin.exe
-- Installing: C:/Program Files/grpc/lib/cmake/grpc/gRPCTargets.cmake
-- Installing: C:/Program Files/grpc/lib/cmake/grpc/gRPCTargets-release.cmake
-- Installing: C:/Program Files/grpc/lib/cmake/grpc/gRPCConfig.cmake
-- Installing: C:/Program Files/grpc/lib/cmake/grpc/gRPCConfigVersion.cmake
-- Installing: C:/Program Files/grpc/lib/cmake/grpc/modules/Findc-ares.cmake
-- Installing: C:/Program Files/grpc/share/grpc/roots.pem
-- Installing: C:/Program Files/grpc/lib/pkgconfig/gpr.pc
-- Installing: C:/Program Files/grpc/lib/pkgconfig/grpc.pc
-- Installing: C:/Program Files/grpc/lib/pkgconfig/grpc_unsecure.pc
-- Installing: C:/Program Files/grpc/lib/pkgconfig/grpc++.pc
-- Installing: C:/Program Files/grpc/lib/pkgconfig/grpc++_unsecure.pc
-- Up-to-date: C:/Program Files/grpc/lib/cares.lib
-- Installing: C:/Program Files/grpc/include/ares.h
-- Installing: C:/Program Files/grpc/include/ares_version.h
-- Installing: C:/Program Files/grpc/include/ares_dns.h
-- Installing: C:/Program Files/grpc/include/ares_build.h
-- Installing: C:/Program Files/grpc/include/ares_rules.h
-- Installing: C:/Program Files/grpc/lib/cmake/c-ares/c-ares-targets.cmake
-- Installing: C:/Program Files/grpc/lib/cmake/c-ares/c-ares-targets-release.cmake
-- Installing: C:/Program Files/grpc/lib/cmake/c-ares/c-ares-config.cmake
-- Installing: C:/Program Files/grpc/lib/pkgconfig/libcares.pc
-- Installing: C:/Program Files/grpc/bin/ahost.exe
-- Installing: C:/Program Files/grpc/bin/adig.exe
-- Installing: C:/Program Files/grpc/bin/acountry.exe
-- Installing: C:/Program Files/grpc/lib/libprotobuf-lite.lib
-- Installing: C:/Program Files/grpc/lib/libprotobuf.lib
-- Installing: C:/Program Files/grpc/lib/libprotoc.lib
-- Installing: C:/Program Files/grpc/bin/protoc.exe
-- Installing: C:/Program Files/grpc/lib/pkgconfig/protobuf.pc
-- Installing: C:/Program Files/grpc/lib/pkgconfig/protobuf-lite.pc
-- Installing: C:/Program Files/grpc/include/google/protobuf/any.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/any.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/api.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/arena.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/arena_impl.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/arenastring.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/code_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/command_line_interface.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/cpp/cpp_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/csharp/csharp_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/csharp/csharp_names.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/importer.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/java/java_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/java/java_names.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/js/js_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/js/well_known_types_embed.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/objectivec/objectivec_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/objectivec/objectivec_helpers.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/parser.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/php/php_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/plugin.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/plugin.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/python/python_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/ruby/ruby_generator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/descriptor.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/descriptor.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/descriptor_database.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/duration.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/dynamic_message.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/empty.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/extension_set.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/extension_set_inl.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/field_mask.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/generated_enum_reflection.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/generated_enum_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/generated_message_reflection.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/generated_message_table_driven.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/generated_message_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/has_bits.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/implicit_weak_message.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/inlined_string_field.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/coded_stream.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/gzip_stream.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/io_win32.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/printer.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/strtod.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/tokenizer.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/zero_copy_stream.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/zero_copy_stream_impl.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/io/zero_copy_stream_impl_lite.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map_entry.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map_entry_lite.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map_field.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map_field_inl.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map_field_lite.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/map_type_handler.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/message.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/message_lite.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/metadata.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/metadata_lite.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/parse_context.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/port.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/port_def.inc
-- Installing: C:/Program Files/grpc/include/google/protobuf/port_undef.inc
-- Installing: C:/Program Files/grpc/include/google/protobuf/reflection.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/reflection_ops.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/repeated_field.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/service.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/source_context.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/struct.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/bytestream.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/callback.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/casts.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/common.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/fastmem.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/hash.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/logging.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/macros.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/map_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/mutex.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/once.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/platform_macros.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/port.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/status.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/stl_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/stringpiece.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/strutil.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/stubs/template_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/text_format.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/timestamp.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/type.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/unknown_field_set.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/delimited_message_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/field_comparator.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/field_mask_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/json_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/message_differencer.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/time_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/type_resolver.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/util/type_resolver_util.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/wire_format.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/wire_format_lite.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/wrappers.pb.h
-- Installing: C:/Program Files/grpc/include/google/protobuf/any.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/api.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/compiler/plugin.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/descriptor.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/duration.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/empty.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/field_mask.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/source_context.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/struct.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/timestamp.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/type.proto
-- Installing: C:/Program Files/grpc/include/google/protobuf/wrappers.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/descriptor.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/any.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/api.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/duration.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/empty.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/field_mask.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/source_context.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/struct.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/timestamp.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/type.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/wrappers.proto
-- Up-to-date: C:/Program Files/grpc/include/google/protobuf/compiler/plugin.proto
-- Installing: C:/Program Files/grpc/cmake/protobuf-targets.cmake
-- Installing: C:/Program Files/grpc/cmake/protobuf-targets-release.cmake
-- Up-to-date: C:/Program Files/grpc/cmake
-- Installing: C:/Program Files/grpc/cmake/protobuf-config-version.cmake
-- Installing: C:/Program Files/grpc/cmake/protobuf-config.cmake
-- Installing: C:/Program Files/grpc/cmake/protobuf-module.cmake
-- Installing: C:/Program Files/grpc/cmake/protobuf-options.cmake
-- Installing: C:/Program Files/grpc/lib/zlib.lib
-- Installing: C:/Program Files/grpc/bin/zlib.dll
-- Up-to-date: C:/Program Files/grpc/lib/zlibstatic.lib
-- Installing: C:/Program Files/grpc/include/zconf.h
-- Installing: C:/Program Files/grpc/include/zlib.h
-- Installing: C:/Program Files/grpc/share/man/man3/zlib.3
-- Installing: C:/Program Files/grpc/share/pkgconfig/zlib.pc
```