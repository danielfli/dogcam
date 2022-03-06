#Library libcamera
# Sources and Headers
set(LIBRARY_libcamera_SOURCES  "Camera.cpp" "post_processor.cpp" "post_processing_stage.cpp" "post_processor.cpp")
# set(LIBRARY_libcamera_INCLUDES "completed_request.hpp" )
# set(LIBRARY_libcamera_HEADERS "${LIBRARY_INCLUDES}/dogCamlib.hpp")

# DogCam Library 
add_library(${LIBRARY_LIBCAMERA} ${LIBRARY_libcamera_SOURCES} )
# target_include_directories(${LIBRARY_DOGCAM} PUBLIC ${LIBRARY_INCLUDES})
# target_compile_features(${LIBRARY_DOGCAM} PUBLIC cxx_std_17)
target_link_libraries(${LIBRARY_LIBCAMERA} pthread)


#Library IMAGE
find_library(EXIF_LIBRARY exif REQUIRED)
find_library(JPEG_LIBRARY jpeg REQUIRED)

set(LIBRARY_IMAGE_SOURCES "jpeg.cpp")
# set(LIBRARY_IMAGE_INCLUDES "image.hpp")

add_library(${LIBRARY_IMAGE} OBJECT ${LIBRARY_IMAGE_SOURCES})
# target_include_directories(${LIBRARY_IMAGE} PUBLIC ${LIBRARY_IMAGE_INCLUDES})
target_link_libraries(${LIBRARY_IMAGE} jpeg exif)
target_compile_features(${LIBRARY_IMAGE} PUBLIC cxx_std_17)

