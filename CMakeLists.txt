# Copyright 2022 tusen authors.

cmake_minimum_required(VERSION 3.5.1)

project(logger_test)

set(CMAKE_CXX_STANDARD 14)

add_definitions(-DBOOST_LOG_DYN_LINK)
# set(gPLATFROM "x86" CACHE STRING "build platfrom is x86")

# include(cmake/common.cmake)
# include(cmake/fmtlib.cmake)

# find_package(gRPC REQUIRED)

# if (gPLATFROM STREQUAL "x86")
#     message("build platform is x86")
# elseif (gPLATFROM STREQUAL "arm")
#     message("build platfrom is arm")
# else()
#     message(FATAL_ERROR "unknown build platfrom, not define gPLATFROM param")
# endif()

include_directories(
    logger
)

# 
# add_library(base_core
#     base/sensor_types.cpp
#     base/framework/core/msg.cpp
#     base/framework/core/thread.cpp
#     base/framework/base.cpp
#     base/framework/message.cpp
#     base/framework/module.cpp
#     base/framework/messagemanager.cpp
#     module/framework.cpp
#     module/module_novatel.cpp
#     module/module_vmps.cpp
# )
# target_link_libraries(base_core
#     pthread
# )

add_executable(logger_main 
    "logger/logger.cpp"
    "main.cpp"
)
target_link_libraries(logger_main
    boost_system
    boost_thread
    pthread
    boost_log
    boost_log_setup
)
# install(TARGETS main DESTINATION lib/${PROJECT_NAME})

# add_executable(msg_test 
#     "base/framework/core/msg.cpp"
#     "examples/msg_test.cpp")
# target_link_libraries(msg_test
#     fmt
#     pthread
#     )
# install(TARGETS msg_test DESTINATION lib/${PROJECT_NAME})

# add_executable(message_test 
#     "base/core/msg.cpp"
#     "base/framework/message.cpp"
#     "examples/message_test.cpp")
# target_link_libraries(message_test
#     fmt
#     pthread
#     )
# install(TARGETS msg_test DESTINATION lib/${PROJECT_NAME})


# add_executable(seq_queue_test 
#     "examples/seq_queue_test.cpp"
#     )
# target_link_libraries(seq_queue_test
#     fmt
#     pthread
#     )
# install(TARGETS seq_queue_test DESTINATION lib/${PROJECT_NAME})