#include "Parser.h"
#include "Token.h"

#include <exception>

namespace arithmetic::parse
{

    std::shared_ptr<ast::ASTNode> Parser::parse(std::string_view source)
    {
        auto tokens = Token::tokenize(source);
        auto parser = Parser(tokens);
        return parser._parse();
    }

    std::shared_ptr<ast::ASTNode> Parser::_parse()
    {
        std::shared_ptr<ast::ASTNode> root;

        if (!_is_eos())
            root = _parseExpression();

        _consumeToken(TokenKind::EOS);
        if (!_tokens.empty())
            throw std::runtime_error(""); //FIXME

        return root;
    }

    std::shared_ptr<ast::Expression> Parser::_parseExpression()
    {
        auto expr = _parseExpressionTerm();

        while (TokenTraits::isAdditionOperator(_head().kind()))
        {
            auto lhs = std::move(expr);
            auto addOp = _consumeToken();
            auto rhs = _parseExpressionTerm();
            expr = ast::ASTFactory::binaryOperation(addOp, lhs, rhs);
        }

        return expr;
    }

    std::shared_ptr<ast::Expression> Parser::_parseExpressionTerm()
    {
        auto expr = _parseExpressionFactor();

        while (TokenTraits::isMultiplicationOperator(_head().kind()))
        {
            auto lhs = std::move(expr);
            auto mulOp = _consumeToken();
            auto rhs = _parseExpressionFactor();
            expr = ast::ASTFactory::binaryOperation(mulOp, lhs, rhs);
        }

        return expr;
    }

    std::shared_ptr<ast::Expression> Parser::_parseExpressionFactor()
    {
        auto headKind = _head().kind();

        if (TokenTraits::isIntegerLiteral(headKind))
        {
            return ast::ASTFactory::integer(_consumeToken());
        }
        else if (headKind == TokenKind::LParen)
        {
            _consumeToken(TokenKind::LParen);
            auto expr = _parseExpression();
            _consumeToken(TokenKind::RParen);
            return expr;
        }
        else
        {
            throw std::runtime_error(""); //FIXME
        }
    }

    Token Parser::_consumeToken()
    {
        auto t = _head();
        _tokens.pop_front();
        return t;
    }

    Token Parser::_consumeToken(Token &token)
    {
        auto t = _consumeToken();
        if (t != token)
            throw std::runtime_error(""); //FIXME
        return t;
    }

    Token Parser::_consumeToken(TokenKind kind)
    {
        auto t = _consumeToken();
        if (t.kind() != kind)
            throw std::runtime_error(""); //FIXME
        return t;
    }

    Token &Parser::_head()
    {
        if (_tokens.empty())
            throw std::runtime_error(""); //FIXME
        return _tokens.front();
    }

    bool Parser::_is_eos()
    {
        return _head().kind() == TokenKind::EOS;
    }
}
