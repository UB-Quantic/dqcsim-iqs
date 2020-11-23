include(FetchContent)
FetchContent_Declare(iqs GIT_REPOSITORY https://github.com/iqusoft/intel-qs.git)

# disable MPI for distributed memory use
set(IqsMPI OFF)

# enable latest vector capability
set(IqsNATIVE ON)

# disable Python binding
set(IqsPython OFF)

# disable unit tests
set(IqsUtest OFF)

FetchContent_MakeAvailable(iqs)