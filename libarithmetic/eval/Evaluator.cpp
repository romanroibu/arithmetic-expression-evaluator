#include "Evaluator.h"
#include "Token.h"

namespace arithmetic::eval
{

    int Evaluator::result()
    {
        if (_stack.size() != 1)
            throw std::runtime_error(""); //FIXME
        return pop_stack<int>();
    }

    bool Evaluator::visitBegin(ast::BinaryOperation &_node)
    {
        push_stack(_node.symbol());
        return true;
    }

    bool Evaluator::visitBegin(ast::IntegerLiteral &_node)
    {
        push_stack(_node.value());
        return true;
    }

    void Evaluator::visitEnd(ast::BinaryOperation &_node)
    {
        auto rhs = pop_stack<int>();
        auto lhs = pop_stack<int>();
        auto symbol = pop_stack<char>();

        if (_node.symbol() != symbol)
            throw std::runtime_error(""); //FIXME

        auto value = calc(symbol, lhs, rhs);
        push_stack(value);
    }

    void Evaluator::visitEnd(ast::IntegerLiteral &_node)
    {
        if (_node.value() != top_stack<int>())
            throw std::runtime_error(""); //FIXME
    }

    int Evaluator::calc(char _symbol, int _lhs, int _rhs)
    {
        switch (_symbol)
        {
        case '+':
            return _lhs + _rhs;
        case '-':
            return _lhs - _rhs;
        case '*':
            return _lhs * _rhs;
        case '/':
            return _lhs / _rhs;
        default:
            throw std::runtime_error(""); //FIXME
        }
    }
}
