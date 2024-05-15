cmake_minimum_required(VERSION 3.10)
project(libklvanc VERSION 1.0)

# Specify C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/src/)

# Set the source files
set(SOURCES
    src/core.c
    src/core-packet-eia_708b.c
    src/core-packet-eia_608.c
    src/core-packet-scte_104.c
    src/core-packet-afd.c
    src/core-packet-sdp.c
    src/core-packet-smpte_12_2.c
    src/core-packet-smpte_2108_1.c
    src/core-packets.c
    src/core-lines.c
    src/core-did.c
    src/core-pixels.c
    src/core-checksum.c
    src/smpte2038.c
    src/core-cache.c
    src/core-packet-kl_u64le_counter.c
)

# Set the header files
set(HEADERS
    src/core-private.h
    src/xorg-list.h
    src/klbitstream_readwriter.h
    src/libklvanc/vanc.h
    src/libklvanc/did.h
    src/libklvanc/pixels.h
    src/libklvanc/smpte2038.h
    src/libklvanc/vanc-eia_708b.h
    src/libklvanc/vanc-eia_608.h
    src/libklvanc/vanc-scte_104.h
    src/libklvanc/vanc-smpte_12_2.h
    src/libklvanc/vanc-smpte_2108_1.h
    src/libklvanc/vanc-packets.h
    src/libklvanc/vanc-lines.h
    src/libklvanc/vanc-afd.h
    src/libklvanc/vanc-sdp.h
    src/libklvanc/vanc-checksum.h
    src/libklvanc/klrestricted_code_path.h
    src/libklvanc/cache.h
    src/libklvanc/vanc-kl_u64le_counter.h
)

# Add the library target
add_library(klvanc SHARED ${SOURCES} ${HEADERS})

# Compiler options
target_compile_options(klvanc PRIVATE -Wall -D_FILE_OFFSET_BITS=64 -O3 -D_BSD_SOURCE)

# Add version definition
target_compile_definitions(klvanc PRIVATE VERSION=\"${PROJECT_VERSION}\" PROG=\"${PROJECT_NAME}\")

# Set debug options if in debug mode
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(klvanc PRIVATE -g)
endif()

# Installation directives
install(TARGETS klvanc
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/libklvanc
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")
