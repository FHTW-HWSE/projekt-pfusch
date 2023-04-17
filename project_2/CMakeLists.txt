add_library(project_2 src/project_2.cpp)
target_include_directories(project_2 PUBLIC include)

add_executable(project_2_test 
test/main.cpp 
test/project_2_test.cpp 
)

target_link_libraries(project_2_test project_2)

catch_discover_tests(project_2_test)
