cmake_minimum_required(VERSION 3.11)
project(dqcsim-intel-qs
	DESCRIPTION "Intel QS backend for DQCsim"
	VERSION "0.1.0"
	LANGUAGES CXX)


add_library(dqcsim-intel-qs)
target_sources(dqcsim-intel-qs PRIVATE src/Backend.cpp)
target_compile_features(dqcsim-intel-qs PUBLIC cxx_std_17)

# dependencies
include(cmake/iqs.cmake)
target_link_libraries(dqcsim-intel-qs iqs)

include(cmake/dqcsim.cmake)
target_link_libraries(dqcsim-intel-qs dqcsim)
