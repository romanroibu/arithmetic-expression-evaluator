#pragma once

#include <deque>
#include <exception>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <string_view>

namespace arithmetic::parse
{

    enum TokenKind
    {
        /* End of Source */
        EOS,
        /* Grouping */
        LParen,
        RParen,
        /* Binary Operators */
        Add,
        Sub,
        Mul,
        Div,
        /* Literals */
        IntLit
    };

    class Token;

    namespace TokenTraits
    {
        constexpr bool isAdditionOperator(TokenKind kind) { return TokenKind::Add == kind || TokenKind::Sub == kind; }
        constexpr bool isMultiplicationOperator(TokenKind kind) { return TokenKind::Mul == kind || TokenKind::Div == kind; }
        constexpr bool isBinaryOperator(TokenKind kind) { return isAdditionOperator(kind) || isMultiplicationOperator(kind); }

        constexpr bool isIntegerLiteral(TokenKind kind) { return TokenKind::IntLit == kind; }
        constexpr bool isLiteral(TokenKind kind) { return isIntegerLiteral(kind); }
        constexpr bool hasValue(TokenKind kind) { return isLiteral(kind); }

        int integerValue(Token &token);
        char binaryOperationSymbol(Token &token);

        std::string prettyName(TokenKind kind);
        std::string prettyName(Token &token);
    }

    class Token
    {
    public:
        /* Factory Methods */
        static Token eos() { return Token(TokenKind::EOS); }
        static Token lparen() { return Token(TokenKind::LParen); }
        static Token rparen() { return Token(TokenKind::RParen); }
        static Token add() { return Token(TokenKind::Add); }
        static Token sub() { return Token(TokenKind::Sub); }
        static Token mul() { return Token(TokenKind::Mul); }
        static Token div() { return Token(TokenKind::Div); }
        static Token integer(std::string value) { return Token(TokenKind::IntLit, value); }
        static Token integer(int value) { return Token::integer(std::to_string(value)); }

        static std::deque<Token> tokenize(std::string_view source);

        /* Member Getters */
        const TokenKind &kind() { return _kind; }
        const std::string &value() { return _value; }

        /* Equatable */
        bool operator!=(const Token &other) const;
        bool operator==(const Token &other) const;

    private:
        Token(TokenKind kind) : _kind(kind)
        {
            if (TokenTraits::hasValue(kind))
                throw std::runtime_error(""); //FIXME
        }
        Token(TokenKind kind, std::string value) : _kind(kind), _value(value)
        {
            if (!TokenTraits::hasValue(kind))
                throw std::runtime_error(""); //FIXME
            if (value.empty())
                throw std::runtime_error(""); //FIXME
        }
        TokenKind _kind;
        std::string _value;
    };

    inline std::ostream &operator<<(std::ostream &os, TokenKind kind)
    {
        os << TokenTraits::prettyName(kind);
        return os;
    }

    inline std::ostream &operator<<(std::ostream &os, Token &token)
    {
        os << TokenTraits::prettyName(token);
        return os;
    }
}
