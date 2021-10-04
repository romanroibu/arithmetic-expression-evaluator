#include "Evaluator.h"
#include "Parser.h"

#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        std::string source(argv[1]);

        try
        {
            auto root = arithmetic::parse::Parser::parse(source);
            auto eval = arithmetic::eval::Evaluator();
            root.get()->accept(eval);
            std::cout << eval.result() << std::endl;
        }
        catch (const std::exception &exc)
        {
        }

        return 0;
    }

    return 1;
}
