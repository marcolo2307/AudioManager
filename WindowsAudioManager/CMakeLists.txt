cmake_minimum_required(VERSION 3.1)

project(WindowsAudioManager)

set(CMAKE_CXX_STANDARD 11)

add_library(WindowsAudioManager SHARED WindowsAudioManager.cpp Manager.cpp Device.cpp)
