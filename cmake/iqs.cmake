include(FetchContent)
FetchContent_Declare(iqs GIT_REPOSITORY https://github.com/iqusoft/intel-qs.git)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# enable MPI if found in system
set(IqsMPI OFF)
find_package(MPI)
if(MPI_FOUND)
	set(IqsMPI ON)
endif()

# enable latest vector capability
set(IqsNATIVE ON)

# disable Python binding
set(IqsPython OFF)

# disable unit tests
set(IqsUtest OFF)

FetchContent_MakeAvailable(iqs)