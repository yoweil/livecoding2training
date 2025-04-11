include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    tests
    tests.cpp
)

target_link_libraries(
    tests
    PUBLIC
    GTest::gtest_main
    GTest::gmock_main
)

target_link_libraries(
    tests
    PRIVATE
    sorted_vector
)

include(GoogleTest)

gtest_discover_tests(tests)
