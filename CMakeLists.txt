cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "arithmetic-evaluator")
project(${PROJECT_NAME} VERSION 0.01 LANGUAGES CXX)

enable_testing()
find_package(GTest REQUIRED)
include(GoogleTest)

# add_subdirectory(libarithmetic)
add_library(libarithmetic STATIC
    libarithmetic/ast/AST.cpp
    libarithmetic/eval/Evaluator.cpp
    libarithmetic/parse/Parser.cpp
    libarithmetic/parse/Token.cpp
)
target_include_directories(libarithmetic PUBLIC
    libarithmetic/ast
    libarithmetic/eval
    libarithmetic/parse
)
set_target_properties(libarithmetic PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


# add_subdirectory(test)
add_executable(tests
    tests/evaluate_tests.cpp
    tests/tokenize_tests.cpp)
target_link_libraries(tests
    GTest::GTest
    GTest::Main
    libarithmetic)
gtest_discover_tests(tests)
set_target_properties(tests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# add_subdirectory(bin)
add_executable(arithmeticc bin/arithmeticc.cpp)
target_link_libraries(arithmeticc
    libarithmetic
)
set_target_properties(arithmeticc PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
