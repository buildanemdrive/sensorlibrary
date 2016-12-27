include_directories("${PROJECT_BINARY_DIR}")
add_executable(test_sensor test_sensor.cxx)
set_target_properties(test_sensor PROPERTIES LINK_FLAGS -Wl,-lcunit)
target_link_libraries (test_sensor sensorlibrary)
