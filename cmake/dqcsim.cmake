include(FetchContent)
FetchContent_Declare(dqcsim
	GIT_REPOSITORY https://github.com/QE-Lab/dqcsim.git
	GIT_TAG 0.2.4)
set(DQCSIM_FROM_SOURCE "yes")
FetchContent_MakeAvailable(dqcsim)
