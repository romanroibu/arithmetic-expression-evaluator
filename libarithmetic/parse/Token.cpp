#include "Token.h"

#include <ctype.h>
#include <exception>

namespace arithmetic::parse
{
    bool Token::operator!=(const Token &other) const
    {
        return !(*this == other);
    }

    bool Token::operator==(const Token &other) const
    {
        return _kind == other._kind && _value == other._value;
    }

    Token makeToken(char ch);

    std::deque<Token> Token::tokenize(std::string_view source)
    {
        std::deque<Token> tokens;

        for (auto ch : source)
            if (!iswspace(ch))
                tokens.push_back(makeToken(ch));

        tokens.push_back(Token::eos());
        return tokens;
    }

    Token makeToken(char ch)
    {
        switch (ch)
        {
        case '(':
            return Token::lparen();
        case ')':
            return Token::rparen();
        case '+':
            return Token::add();
        case '-':
            return Token::sub();
        case '*':
            return Token::mul();
        case '/':
            return Token::div();
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return Token::integer(std::string(1, ch));
        default:
            throw std::runtime_error(""); //FIXME
        }
    }
}

namespace arithmetic::parse::TokenTraits
{

    int integerValue(Token &token)
    {
        if (isIntegerLiteral(token.kind()))
            return std::stoi(token.value());

        throw std::runtime_error(""); //FIXME
    }

    char binaryOperationSymbol(Token &token)
    {
        auto kind = token.kind();

        if (!isBinaryOperator(kind))
            throw std::runtime_error(""); //FIXME

        switch (kind)
        {
        case TokenKind::Add:
            return '+';
        case TokenKind::Sub:
            return '-';
        case TokenKind::Mul:
            return '*';
        case TokenKind::Div:
            return '/';
        default:
            throw std::runtime_error(""); //FIXME
        }
    }

    std::string prettyName(TokenKind kind)
    {
        switch (kind)
        {
        case TokenKind::EOS:
            return "EOS";
        case TokenKind::LParen:
            return "LPAREN";
        case TokenKind::RParen:
            return "RPAREN";
        case TokenKind::Add:
            return "+";
        case TokenKind::Sub:
            return "-";
        case TokenKind::Mul:
            return "*";
        case TokenKind::Div:
            return "/";
        case TokenKind::IntLit:
            return "Integer";
        default:
            throw std::runtime_error(""); //FIXME
        }
    }

    std::string prettyName(Token &token)
    {
        if (hasValue(token.kind()))
        {
            std::string name = "";
            name.append("<");
            name.append(prettyName(token.kind()));
            name.append("=");
            name.append(token.value());
            name.append(">");
            return name;
        }
        else
        {
            std::string name = "";
            name.append("<");
            name.append(prettyName(token.kind()));
            name.append(">");
            return name;
        }
    }
}
