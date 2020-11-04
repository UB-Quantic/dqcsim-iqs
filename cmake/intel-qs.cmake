include(FetchContent)
FetchContent_Declare(intel-qs GIT_REPOSITORY https://github.com/iqusoft/intel-qs.git)

# disable MPI for distributed memory use
set(IqsMPI OFF)

# enable latest vector capability
set(IqsNATIVE ON)

# disable Python binding
set(IqsPython OFF)

FetchContent_MakeAvailable(intel-qs)