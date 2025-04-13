set(GTEST_ROOT "/opt/homebrew/Cellar/googletest/1.16.0")

include_directories(
    ${GTEST_ROOT}/include
    ${CMAKE_SOURCE_DIR}/include
)

link_directories(${GTEST_ROOT}/lib)

add_executable(${PROJECT_NAME}.test
    AllTests.cpp
    tests.cpp
)

target_link_libraries(${PROJECT_NAME}.test
    ${PROJECT_NAME}
    ${GTEST_ROOT}/lib/libgtest.a
    ${GTEST_ROOT}/lib/libgtest_main.a
    pthread
)

target_compile_definitions(${PROJECT_NAME}.test 
    PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test")

install(TARGETS ${PROJECT_NAME}.test
    DESTINATION "${tool_dest}"
)