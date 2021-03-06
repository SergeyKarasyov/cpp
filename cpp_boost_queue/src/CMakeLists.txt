set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_library(${PROJECT_NAME}_lib producers.hpp consumers.hpp )


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME}_lib PRIVATE -Werror -Wall -Wextra)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}_lib PRIVATE -Wall -Wextra -Weverything -Wno-c++98-compat
                                                       -Wno-c++98-compat-pedantic)
endif()

find_package(Boost 1.64.0 REQUIRED COMPONENTS thread system)
include_directories(${Boost_INCLUDE_DIRS})
set_target_properties(${PROJECT_NAME}_lib PROPERTIES LINKER_LANGUAGE CXX)
target_compile_features(${PROJECT_NAME}_lib PUBLIC cxx_std_14)
target_link_libraries(${PROJECT_NAME}_lib PRIVATE "stdc++fs")
target_link_libraries(${PROJECT_NAME}_lib PRIVATE Threads::Threads)
target_compile_options(${PROJECT_NAME}_lib PRIVATE -Werror -Wall -Wextra)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
target_link_libraries(${PROJECT_NAME} PRIVATE project_options)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC Boost::thread)

