#pragma once

#include "Token.h"

#include <iostream>
#include <memory>

namespace arithmetic::ast
{

    class ASTVisitor;

    class ASTNode
    {
    public:
        ASTNode() = default;
        virtual ~ASTNode() = default;

        virtual void accept(ASTVisitor &) = 0;
        virtual std::string prettyPrint(int) = 0;
    };

    class Expression : public ASTNode
    {
    };

    class IntegerLiteral : public Expression
    {
    public:
        IntegerLiteral(parse::Token);
        virtual ~IntegerLiteral(){};

        int value();

        void accept(ASTVisitor &);
        std::string prettyPrint(int);

    private:
        parse::Token _token;
    };

    class BinaryOperation : public Expression
    {
    public:
        BinaryOperation(parse::Token &_token, std::shared_ptr<Expression> _lhs, std::shared_ptr<Expression> _rhs) : _token(_token), _lhs(_lhs), _rhs(_rhs)
        {
            if (!parse::TokenTraits::isBinaryOperator(_token.kind()))
                throw std::runtime_error(""); //FIXME
        };
        virtual ~BinaryOperation(){};

        const char symbol();
        const Expression &lhs();
        const Expression &rhs();

        void accept(ASTVisitor &_visitor);
        std::string prettyPrint(int);

    private:
        parse::Token _token;
        std::shared_ptr<Expression> _lhs;
        std::shared_ptr<Expression> _rhs;
    };

    class ASTFactory
    {
    public:
        static std::shared_ptr<IntegerLiteral> integer(int);
        static std::shared_ptr<IntegerLiteral> integer(parse::Token);
        static std::shared_ptr<BinaryOperation> add(std::shared_ptr<Expression>, std::shared_ptr<Expression>);
        static std::shared_ptr<BinaryOperation> sub(std::shared_ptr<Expression>, std::shared_ptr<Expression>);
        static std::shared_ptr<BinaryOperation> mul(std::shared_ptr<Expression>, std::shared_ptr<Expression>);
        static std::shared_ptr<BinaryOperation> div(std::shared_ptr<Expression>, std::shared_ptr<Expression>);
        static std::shared_ptr<BinaryOperation> binaryOperation(parse::Token, std::shared_ptr<Expression>, std::shared_ptr<Expression>);
    };

    class ASTVisitor
    {
    public:
        ASTVisitor() = default;
        virtual ~ASTVisitor() = default;
        virtual bool visitBegin(BinaryOperation &_node) = 0;
        virtual bool visitBegin(IntegerLiteral &_node) = 0;
        virtual void visitEnd(BinaryOperation &_node) = 0;
        virtual void visitEnd(IntegerLiteral &_node) = 0;

    private:
        ASTVisitor(ASTVisitor const &) = delete;
        ASTVisitor &operator=(ASTVisitor const &) = delete;
    };

    std::ostream &operator<<(std::ostream &, ASTNode &);

}
