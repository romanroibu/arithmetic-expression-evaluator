#include <Evaluator.h>
#include <Parser.h>
#include <gtest/gtest.h>

int eval(std::string);

TEST(evaluate_tests, tokenize_source_1)
{
    EXPECT_EQ(eval("(4 + 5 * (7 - 3)) - 2"), 22);
}

TEST(evaluate_tests, tokenize_source_2)
{
    EXPECT_EQ(eval("4+5+7/2"), 12);
}

int eval(std::string source)
{
    auto root = arithmetic::parse::Parser::parse(source);
    auto eval = arithmetic::eval::Evaluator();
    root.get()->accept(eval);
    return eval.result();
}
