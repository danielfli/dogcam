
# Add Google Test
include(FetchContent)  
FetchContent_Declare(googletest 
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "703bd9caab50b139428cea1aaff9974ebee5742e" ) 
FetchContent_MakeAvailable(googletest)
