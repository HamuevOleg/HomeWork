cmake_minimum_required(VERSION 3.27)
project(Lab_4 C)

set(CMAKE_C_STANDARD 23)

add_executable(Lab_4 main.c
        RSA.h
        RSA.c
        vernam.h
        vernam.c
        utils.h
        utils.c
        DES.h
        DES.c)
