# add Libraries 
add_subdirectory(camera)

# Sources and Headers
set(LIBRARY_SOURCES "dogCamlib.cpp" "Vision.cpp")
set(LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/")
set(LIBRARY_HEADERS "${LIBRARY_INCLUDES}/dogCamlib.hpp")


# DogCam Library 
add_library(${LIBRARY_DOGCAM} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS} )
target_include_directories(${LIBRARY_DOGCAM} PUBLIC ${LIBRARY_INCLUDES})
target_compile_features(${LIBRARY_DOGCAM} PUBLIC cxx_std_17)
target_link_libraries(${LIBRARY_DOGCAM} pthread)