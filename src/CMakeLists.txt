# Sources and Headers
set(LIBRARY_SOURCES "dogCamlib.cpp" "Camera.hpp" "Vision.cpp")
set(LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/")
set(LIBRARY_HEADERS "${LIBRARY_INCLUDES}/dogCamlib.hpp")


# DogCam Library 
add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})
target_include_directories(${LIBRARY_NAME} PUBLIC ${LIBRARY_INCLUDES})
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_11)