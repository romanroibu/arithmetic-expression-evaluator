#pragma once

#include "AST.h"

#include <stack>
#include <variant>

namespace arithmetic::eval
{

    class Evaluator : public ast::ASTVisitor
    {
    public:
        int result();

        bool visitBegin(ast::BinaryOperation &_node);
        bool visitBegin(ast::IntegerLiteral &_node);
        void visitEnd(ast::BinaryOperation &_node);
        void visitEnd(ast::IntegerLiteral &_node);

    private:
        using Value = std::variant<int, char>;
        std::stack<Value> _stack;

        template <class T>
        T top_stack()
        {
            if (_stack.empty())
                throw std::runtime_error(""); //FIXME
            auto item = _stack.top();
            if (!std::holds_alternative<T>(item))
                throw std::runtime_error(""); //FIXME
            return std::get<T>(item);
        }

        template <class T>
        T pop_stack()
        {
            auto value = top_stack<T>();
            _stack.pop();
            return value;
        }

        template <class T>
        void push_stack(const T item) noexcept
        {
            _stack.push(item);
        }

        int calc(char, int, int);
    };
}
