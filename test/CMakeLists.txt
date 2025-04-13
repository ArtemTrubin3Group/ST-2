find_package(GTest REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}.test
    AllTests.cpp
    tests.cpp
)

target_link_libraries(${PROJECT_NAME}.test
    ${PROJECT_NAME}
    GTest::GTest
    GTest::Main
    pthread
)

if(NOT TARGET GTest::GTest)
    message(WARNING "GTest not found via find_package, using manual config")
    set(GTEST_ROOT "/opt/homebrew/Cellar/googletest/1.16.0")
    target_link_libraries(${PROJECT_NAME}.test
        ${PROJECT_NAME}
        ${GTEST_ROOT}/lib/libgtest.dylib
        ${GTEST_ROOT}/lib/libgtest_main.dylib
        pthread
    )
endif()

target_compile_definitions(${PROJECT_NAME}.test 
    PRIVATE TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test")

install(TARGETS ${PROJECT_NAME}.test
    DESTINATION "${tool_dest}"
)