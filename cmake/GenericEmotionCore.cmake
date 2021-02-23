cmake_minimum_required(VERSION 3.13)

if (NOT TARGET "GenericEmotionCore")
    # target
    add_library("GenericEmotionCore")
    # src
    file(GLOB_RECURSE GenericEmotionCore_SRCS "${CMAKE_CURRENT_LIST_DIR}/../src/GenericEmotionCore/**.cpp")
    target_sources("GenericEmotionCore" PRIVATE ${GenericEmotionCore_SRCS})
    # include
    set(GenericEmotionCore_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")
    target_include_directories("GenericEmotionCore" PUBLIC ${GenericEmotionCore_INCLUDE_DIRS})
endif ()