enable_testing()

add_executable(
  hello_test
  hellotest.cpp
)
target_link_libraries(
  hello_test
  gtest_main
)

include(GoogleTest)
if(NOT CMAKE_CROSSCOMPILING)
  gtest_discover_tests(hello_test)
endif()