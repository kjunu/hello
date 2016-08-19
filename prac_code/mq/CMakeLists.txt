PROJECT (mq)

SET (CMAKE_BUILD_TYPE "debug")
ADD_EXECUTABLE (server_echo msg_ser.cpp)
ADD_EXECUTABLE (client_echo msg_cli.cpp)

TARGET_LINK_LIBRARIES (server_echo pthread rt boost_timer boost_chrono boost_thread boost_system)
TARGET_LINK_LIBRARIES (client_echo pthread rt boost_chrono boost_thread boost_system boost_program_options)
