cmake_minimum_required(VERSION 3.10)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(esp_http_client)

target_add_binary_data(esp_http_client.wasm "main/howsmyssl_com_root_cert.pem" TEXT)
target_add_binary_data(esp_http_client.wasm "main/postman_root_cert.pem" TEXT)