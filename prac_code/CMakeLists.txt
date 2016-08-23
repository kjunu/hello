PROJECT (prac)

SET (CMAKE_BUILD_TYPE "debug")
ADD_EXECUTABLE (prac func_ptr.cpp)
ADD_EXECUTABLE (server_echo server.cpp)
ADD_EXECUTABLE (client_echo client.cpp)
ADD_EXECUTABLE (timer timer_asio.cpp)
ADD_EXECUTABLE (cptr cptr.cpp)

TARGET_LINK_LIBRARIES (timer boost_timer boost_chrono boost_thread boost_system)
TARGET_LINK_LIBRARIES (server_echo boost_timer boost_chrono boost_thread boost_system)
TARGET_LINK_LIBRARIES (client_echo pthread boost_chrono boost_thread boost_system)
