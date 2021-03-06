cmake_minimum_required(VERSION 3.14)
project(dqcsim-iqs
	DESCRIPTION "Intel QS backend for DQCsim"
	VERSION "0.2.0"
	LANGUAGES CXX)

option(LOGGING "Enable DQCsim log" ON)

add_executable(dqcsim-iqs)
target_sources(dqcsim-iqs PRIVATE
	src/main.cpp
	src/Backend.cpp
	include/Backend.hpp
)
target_include_directories(dqcsim-iqs PUBLIC include)
target_compile_features(dqcsim-iqs PUBLIC cxx_std_17)

target_compile_definitions(dqcsim-iqs PRIVATE $<$<BOOL:${LOGGING}>:DQCSIM_SHORT_LOGGING_MACROS>)

# dependencies
include(cmake/iqs.cmake)
target_link_libraries(dqcsim-iqs iqs)

find_package(dqcsim 0.3.0 REQUIRED)
target_link_libraries(dqcsim-iqs dqcsim)

# install libiqs dependency
install(TARGETS iqs
	LIBRARY DESTINATION lib
)

# install executable
install(TARGETS dqcsim-iqs
	RUNTIME DESTINATION bin
)
