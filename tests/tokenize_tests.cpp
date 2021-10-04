#include <Parser.h>
#include <gtest/gtest.h>

using Token = arithmetic::parse::Token;
using TokenList = std::deque<Token>;

TEST(tokenize_tests, tokenize_empty)
{
    EXPECT_EQ(Token::tokenize(""), TokenList{Token::eos()});
}

TEST(tokenize_tests, tokenize_spaces)
{
    TokenList tokens;

    tokens = TokenList{
        Token::integer("7"),
        Token::div(),
        Token::integer("2"),
        Token::eos(),
    };
    EXPECT_EQ(Token::tokenize("7/ 2"), tokens);

    tokens = TokenList{
        Token::integer("7"),
        Token::div(),
        Token::integer("2"),
        Token::eos(),
    };
    EXPECT_EQ(Token::tokenize("\r7\n/   \t2 "), tokens);
}

TEST(tokenize_tests, tokenize_source_1)
{
    TokenList tokens{
        Token::lparen(),
        Token::integer("4"),
        Token::add(),
        Token::integer("5"),
        Token::mul(),
        Token::lparen(),
        Token::integer("7"),
        Token::sub(),
        Token::integer("3"),
        Token::rparen(),
        Token::rparen(),
        Token::sub(),
        Token::integer("2"),
        Token::eos(),
    };
    EXPECT_EQ(Token::tokenize("(4 + 5 * (7 - 3)) - 2"), tokens);
}

TEST(tokenize_tests, tokenize_source_2)
{
    TokenList tokens{
        Token::integer("4"),
        Token::add(),
        Token::integer("5"),
        Token::add(),
        Token::integer("7"),
        Token::div(),
        Token::integer("2"),
        Token::eos(),
    };
    EXPECT_EQ(Token::tokenize("4+5+7/2"), tokens);
}
