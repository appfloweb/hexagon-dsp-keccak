# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Declares and names the project.
project("keccak")

# Set HEXAGON_SDK_ROOT and HEXAGON_CMAKE_ROOT
set(HEXAGON_SDK_ROOT "H:/python/Hexagon_SDK/4.3.0.0")
set(ENV{HEXAGON_SDK_ROOT} ${HEXAGON_SDK_ROOT})
set(HEXAGON_CMAKE_ROOT "${HEXAGON_SDK_ROOT}/build/cmake")

# Set required variant here
set(PREBUILT_LIB_DIR "android_aarch64")

# Choosing default sub-system as CDSP
set(dsp "cdsprpc")

# Use the file `hexagon_helper.cmake` as helper to CMakeLists.txt.
# It contains the definition of functions `build_idl` to build the IDL.
include(${HEXAGON_CMAKE_ROOT}/hexagon_fun.cmake)

# Create keccak library as SHARED to be packaged with the APK.
add_library( keccak
        SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/util.c
        ${CMAKE_CURRENT_SOURCE_DIR}/sha3.c
        ${CMAKE_CURRENT_SOURCE_DIR}/native-lib.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/calculator_stub.c
        )

# Build calculator.idl to produce calculator.h, calculator_stub.c and calculator_skel.c
build_idl(inc/calculator.idl keccak)

# Add necessary includes for the project
set(dsp_incs
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${CMAKE_CURRENT_BINARY_DIR}/
        ${HEXAGON_SDK_ROOT}/incs/
        ${HEXAGON_SDK_ROOT}/incs/stddef
        ${HEXAGON_SDK_ROOT}/ipc/fastrpc/rpcmem/inc
        )
include_directories(${dsp_incs})

# Prepare log library
find_library(log-lib log)

# Preparing rpcmem library
add_dependencies(keccak rpcmem)
add_library(rpcmem SHARED ${HEXAGON_SDK_ROOT}/ipc/fastrpc/rpcmem/src/rpcmem_android.c)

# Include path of cdsrpc library
target_link_directories(keccak PUBLIC "${HEXAGON_SDK_ROOT}/ipc/fastrpc/remote/ship/${PREBUILT_LIB_DIR}")

# Linking keccak library with dependencies - log, rpcmem, libcdsprpc
target_link_libraries(rpcmem ${log-lib})
target_link_libraries(keccak rpcmem ${log-lib} ${dsp})