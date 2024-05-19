add_executable(task main.cpp)

target_link_libraries(task GameClub)
target_include_directories(task PRIVATE ${PROJECT_SOURCE_DIR})
