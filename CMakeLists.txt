cmake_minimum_required(VERSION 3.27)
project(c_project C)

set(CMAKE_C_STANDARD 23)

add_executable(c_project main.c
        security_system.h
        utils.c
        documents.c
        risks.c
        controls.c
        audits.c
        incidents.c
        reports.c
        menus.c
        password-Generator.c)
