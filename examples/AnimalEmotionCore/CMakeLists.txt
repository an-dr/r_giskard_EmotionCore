cmake_minimum_required (VERSION 3.13)
project ("Example_AnimalEmotionCore")

include ("${CMAKE_CURRENT_LIST_DIR}/../../cmake/AnimalEmotionCore.cmake")

# Example 2
add_executable (${PROJECT_NAME})
target_sources (${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/main.cpp")
target_include_directories (${PROJECT_NAME} PUBLIC ${AnimalEmotionCore_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} "AnimalEmotionCore")
