#pragma once

#include "AST.h"
#include "Token.h"

#include <string_view>

namespace arithmetic::parse
{

    class Parser
    {
    public:
        static std::shared_ptr<ast::ASTNode> parse(std::string_view);

    private:
        Parser(std::deque<Token> tokens) : _tokens(tokens){};
        std::shared_ptr<ast::ASTNode> _parse();
        std::shared_ptr<ast::Expression> _parseExpression();
        std::shared_ptr<ast::Expression> _parseExpressionTerm();
        std::shared_ptr<ast::Expression> _parseExpressionFactor();
        Token _consumeToken();
        Token _consumeToken(Token &token);
        Token _consumeToken(TokenKind kind);
        Token &_head();
        bool _is_eos();
        std::deque<Token> _tokens;
    };
}
