INCLUDE_DIRECTORIES(${MATLAB_INCLUDE_DIR})
add_executable (mat_engine matlab_engine.cpp)
target_link_libraries(mat_engine ${MATLAB_LIBRARIES})
