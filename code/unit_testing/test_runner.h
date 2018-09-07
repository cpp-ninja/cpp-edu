//
// Created by dan on 08.09.18.
//
#pragma once
#ifndef YELLOW_TEST_RUNNER_H
#define YELLOW_TEST_RUNNER_H



void Assert(bool b, const string& hint);


class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name);
    ~TestRunner();

    private:
    int fail_count = 0;
};






#endif //YELLOW_TEST_RUNNER_H
