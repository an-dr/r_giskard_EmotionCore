cmake_minimum_required (VERSION 3.13)
project ("Example_GenericEmotionCore")

include ("${CMAKE_CURRENT_LIST_DIR}/../../cmake/GenericEmotionCore.cmake")

# Example 1
add_executable (${PROJECT_NAME})
target_sources (${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
target_include_directories (${PROJECT_NAME} PUBLIC ${GenericEmotionCore_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} "GenericEmotionCore")
