cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)


add_executable(Calculator main.cpp calculator.cpp calculator.h numbers.cpp numbers.h)

add_executable(TestCalculator test/CalculatorTest.cpp test/test_runner.h test/test_runner.cpp calculator.cpp calculator.h numbers.cpp numbers.h)
