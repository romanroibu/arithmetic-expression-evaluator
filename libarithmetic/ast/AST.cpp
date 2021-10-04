#include "AST.h"

#include <sstream>

namespace arithmetic::ast
{

    // ASTFactory

    std::shared_ptr<IntegerLiteral> ASTFactory::integer(int _value)
    {
        return integer(parse::Token::integer(_value));
    };

    std::shared_ptr<IntegerLiteral> ASTFactory::integer(parse::Token _token)
    {
        return std::make_shared<IntegerLiteral>(_token);
    };

    static std::shared_ptr<IntegerLiteral> integer();

    std::shared_ptr<BinaryOperation> ASTFactory::add(std::shared_ptr<Expression> _lhs, std::shared_ptr<Expression> _rhs)
    {
        return binaryOperation(parse::Token::add(), _lhs, _rhs);
    }

    std::shared_ptr<BinaryOperation> ASTFactory::sub(std::shared_ptr<Expression> _lhs, std::shared_ptr<Expression> _rhs)
    {
        return binaryOperation(parse::Token::sub(), _lhs, _rhs);
    }

    std::shared_ptr<BinaryOperation> ASTFactory::mul(std::shared_ptr<Expression> _lhs, std::shared_ptr<Expression> _rhs)
    {
        return binaryOperation(parse::Token::mul(), _lhs, _rhs);
    }

    std::shared_ptr<BinaryOperation> ASTFactory::div(std::shared_ptr<Expression> _lhs, std::shared_ptr<Expression> _rhs)
    {
        return binaryOperation(parse::Token::div(), _lhs, _rhs);
    }

    std::shared_ptr<BinaryOperation> ASTFactory::binaryOperation(parse::Token _token, std::shared_ptr<Expression> _lhs, std::shared_ptr<Expression> _rhs)
    {
        return std::make_shared<BinaryOperation>(_token, _lhs, _rhs);
    };

    // IntegerLiteral

    IntegerLiteral::IntegerLiteral(parse::Token _token) : _token(_token)
    {
        if (!parse::TokenTraits::isIntegerLiteral(_token.kind()))
            throw std::runtime_error(""); //FIXME
    };

    int IntegerLiteral::value()
    {
        return parse::TokenTraits::integerValue(_token);
    }

    void IntegerLiteral::accept(ASTVisitor &_visitor)
    {
        _visitor.visitBegin(*this);
        _visitor.visitEnd(*this);
    }

    std::string IntegerLiteral::prettyPrint(int indent)
    {
        std::stringstream ss;
        ss << std::string("\t", indent) << "<IntegerLiteral: (" << value() << ")>";
        return ss.str();
    };

    // BinaryOperation

    const char BinaryOperation::symbol()
    {
        return parse::TokenTraits::binaryOperationSymbol(_token);
    }

    const Expression &BinaryOperation::lhs()
    {
        return *_lhs;
    }

    const Expression &BinaryOperation::rhs()
    {
        return *_rhs;
    }

    void BinaryOperation::accept(ASTVisitor &_visitor)
    {
        if (_visitor.visitBegin(*this))
        {
            _lhs->accept(_visitor);
            _rhs->accept(_visitor);
        }
        _visitor.visitEnd(*this);
    };

    std::string BinaryOperation::prettyPrint(int indent)
    {
        std::stringstream ss;
        ss << std::string("\t", indent) << "<BinaryOperation: (" << symbol() << ")>";
        ss << std::endl;
        ss << "- " << _lhs->prettyPrint(indent + 1);
        ss << std::endl;
        ss << "- " << _rhs->prettyPrint(indent + 1);
        return ss.str();
    };

    std::ostream &operator<<(std::ostream &os, ASTNode &node)
    {
        os << node.prettyPrint(0);
        return os;
    }
}
