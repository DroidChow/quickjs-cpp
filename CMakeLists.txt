cmake_minimum_required(VERSION 3.14)
project(quickjs_cpp)

set(CMAKE_CXX_STANDARD 11)

add_compile_definitions(CONFIG_VERSION="2019-07-09")

set(QUICKJS_SOURCE
        quickjs/bjson.c
        quickjs/cutils.c
        quickjs/libbf.c
        quickjs/libregexp.c
        quickjs/libunicode.c
        quickjs/quickjs-libc.c
        quickjs/quickjs.c
        )

set(CPPQUICKJS_SOURCE
        quickjscpp/quickjscpp.cpp
        )

add_executable(quickjs_cpp
        ${QUICKJS_SOURCE}
        ${CPPQUICKJS_SOURCE}
        main.cpp
        )