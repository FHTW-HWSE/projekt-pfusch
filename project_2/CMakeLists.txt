
file(GLOB p2_sources
    src/db/*.cpp
    src/entities/*.cpp
    src/fascades/*.cpp
    src/helper/*.cpp
    src/ui/*.cpp
    src/views/*.cpp
)

add_subdirectory(dependencies/result)
# message(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(p2 src/P2.cpp ${p2_sources})
target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 
target_link_libraries(p2 PRIVATE Result::Result)

# # target_include_directories(${PROJECT_NAME} PRIVATE include) 
# target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 
# # target_include_directories(p2 PRIVATE "src") 
# target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/db) 
# target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/entities) 
# target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/fascades) 
# target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/helper) 
# target_include_directories(p2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ui) 

file(GLOB test_sources
    test/*.cpp
    test/db/*.cpp
)

message(${test_sources})

add_executable(project_2_test 
    ${test_sources}
    # test/Main.cpp 
    # test/Project_2_test.cpp 
)
target_include_directories(project_2_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 

add_library(ps_lib ${p2_sources})
target_include_directories(ps_lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include) 
target_link_libraries(ps_lib PRIVATE Result::Result)

target_link_libraries(project_2_test 
    PRIVATE Result::Result
    ps_lib
)

catch_discover_tests(project_2_test)
