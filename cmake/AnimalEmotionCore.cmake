cmake_minimum_required(VERSION 3.13)

if (NOT TARGET "AnimalEmotionCore")

    include("${CMAKE_CURRENT_LIST_DIR}/GenericEmotionCore.cmake")

    # target
    add_library("AnimalEmotionCore")
    # src
    file(GLOB_RECURSE AnimalEmotionCore_SRCS "${CMAKE_CURRENT_LIST_DIR}/../src/AnimalEmotionCore/**.cpp")
    target_sources("AnimalEmotionCore" PRIVATE ${AnimalEmotionCore_SRCS})
    # include
    set(AnimalEmotionCore_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../include")
    target_include_directories(
            "AnimalEmotionCore" PUBLIC ${AnimalEmotionCore_INCLUDE_DIRS} ${GenericEmotionCore_INCLUDE_DIRS}
    )
    # libs
    target_link_libraries("AnimalEmotionCore" "GenericEmotionCore")
endif ()
