//
// Created by cpp-ninja on 08.10.18.
//

#include "../calculator.h"
#include "test_runner.h"



void TestResult(){
    {
        std::string expression = "1 + 1 * 2 ";
        Calculator calculator;
        std::string result = calculator.evaluate(Type::REAL, expression);
        AssertEqual(result, "3.00", "1");
    }

    {
        std::string expression = "3 + (4 * 2) / (1 - 5)^2";
        Calculator calculator;
        std::string result = calculator.evaluate(Type::REAL, expression);
        AssertEqual(result, "3.50", "2");
    }

}

void TestRPNNodes(){
    {
        std::deque<std::shared_ptr<Node>> expression;
        expression.push_back(make_shared<RealNumber>(1));
        expression.push_back(make_shared<RealNumber>(1));
        expression.push_back(make_shared<Operation>('+'));

        Calculator calculator;
        auto number = calculator.eval_rpn<RealNumber>(expression);
        AssertEqual(number->toString(), "2.00", "1");
    }
}

void TestMakeRPNNodes(){
    {
        Calculator calculator;
        std::string expression = "1 + 1";
        auto rpn_nodes = calculator.make_rpn_nodes<RealNumber>(expression);
        RealNumber r(1);
        rpn_nodes.pop_front();
        RealNumber r2 = *(dynamic_cast<RealNumber*>(rpn_nodes.front().get()));
        Assert(r == r2, "1");

    }
}

void TestAll(){
    TestRunner runner;
    runner.RunTest(TestResult, "TestResult");
    runner.RunTest(TestRPNNodes, "Test RPN nodes");
    runner.RunTest(TestMakeRPNNodes, "TestMakeRPNNodes");
}


int main(){
    TestAll();
}