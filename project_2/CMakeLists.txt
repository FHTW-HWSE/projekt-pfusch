
add_subdirectory(dependencies/result)

# project 2 executable

file(GLOB p2_sources
    src/db/*.cpp
    src/entities/*.cpp
    src/fascades/*.cpp
    src/helper/*.cpp
    src/ui/*.cpp
    src/views/*.cpp
    src/interaction/*.cpp
    src/enviroment/*.cpp
)

add_executable(p2 src/P2.cpp ${p2_sources})


target_include_directories(p2 PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/db
    ${CMAKE_CURRENT_SOURCE_DIR}/include/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/include/enviroment
    ${CMAKE_CURRENT_SOURCE_DIR}/include/fascades
    ${CMAKE_CURRENT_SOURCE_DIR}/include/helper
    ${CMAKE_CURRENT_SOURCE_DIR}/include/interaction
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui_menu
)
    
target_link_libraries(p2 PRIVATE Result::Result)


# test executable

file(GLOB test_sources
    test/*.cpp
    test/db/*.cpp
    test/entities/*.cpp
    test/mock_objects/*.cpp
    test/fascades/*.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)

add_executable(project_2_test 
${test_sources}
)

target_include_directories(project_2_test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/db
    ${CMAKE_CURRENT_SOURCE_DIR}/include/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/include/enviroment
    ${CMAKE_CURRENT_SOURCE_DIR}/include/fascades
    ${CMAKE_CURRENT_SOURCE_DIR}/include/helper
    ${CMAKE_CURRENT_SOURCE_DIR}/include/interaction
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui_menu
) 
target_include_directories(project_2_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test/include) 

# create a lib from main project and link to test executable

add_library(ps_lib ${p2_sources})
target_include_directories(ps_lib PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/db
    ${CMAKE_CURRENT_SOURCE_DIR}/include/entities
    ${CMAKE_CURRENT_SOURCE_DIR}/include/enviroment
    ${CMAKE_CURRENT_SOURCE_DIR}/include/fascades
    ${CMAKE_CURRENT_SOURCE_DIR}/include/helper
    ${CMAKE_CURRENT_SOURCE_DIR}/include/interaction
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui_menu
) 
target_link_libraries(ps_lib PRIVATE Result::Result)

target_link_libraries(project_2_test 
    PRIVATE
    Catch2::Catch2
    PRIVATE Result::Result
    ps_lib
)

catch_discover_tests(project_2_test
    EXTRA_ARGS ${CMAKE_CURRENT_SOURCE_DIR}/test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
)
