cmake_minimum_required(VERSION 3.10)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(mqtt_generic)

target_add_binary_data(mqtt_generic.wasm "main/mqtt_eclipseprojects_io.pem" TEXT)