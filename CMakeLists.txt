cmake_minimum_required(VERSION 3.14)
project(dqcsim-intel-qs
	DESCRIPTION "Intel QS backend for DQCsim"
	VERSION "0.1.0"
	LANGUAGES CXX)

option(ENABLE_LOG "Enable DQCsim log" ON)

add_executable(dqcsim-intel-qs)
target_sources(dqcsim-intel-qs PRIVATE
	src/main.cpp
	src/Backend.cpp)
target_include_directories(dqcsim-intel-qs PUBLIC include)
target_compile_features(dqcsim-intel-qs PUBLIC cxx_std_17)

target_compile_definitions(dqcsim-intel-qs PRIVATE $<$<BOOL:${ENABLE_LOG}>:DQCSIM_SHORT_LOGGING_MACROS>)

# dependencies
include(cmake/iqs.cmake)
target_link_libraries(dqcsim-intel-qs iqs)

include(cmake/dqcsim.cmake)
target_link_libraries(dqcsim-intel-qs dqcsim)
