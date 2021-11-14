# Sources
set(APP_SOURCES "dogCamApp.cpp")

# Executable
add_executable(${EXECUTABLE_NAME} ${APP_SOURCES})

# Main Executetable
target_link_libraries(${EXECUTABLE_NAME} PUBLIC ${LIBRARY_NAME})
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_17)