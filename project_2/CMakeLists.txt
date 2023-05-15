add_subdirectory("dependencies/result")

add_library(project_2 src/Project_2.cpp)

target_include_directories(project_2 PUBLIC include)

target_link_libraries(project_2
    PRIVATE Result::Result
)

# target_link_libraries(project_2 PRIVATE GSL::gsl)

add_executable(project_2_test 
test/Main.cpp 
test/Project_2_test.cpp 
)

target_link_libraries(project_2_test project_2)

catch_discover_tests(project_2_test)
