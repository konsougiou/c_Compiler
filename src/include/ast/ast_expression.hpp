#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <memory>
#include <cmath>

struct Context
{
    std::map<std::string, std::vector<std::string>> bindings;
    int available_mem;
    int frame_size;
    int makeNameUnq;
    
};



class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:

    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream

    //! Evaluate the tree using the given mapping of variables to numbers
    virtual void translate(std::string dest, Context &context, 
    std::stack<std::string> available_registers
    ) const
    { std::cout<<"error"<<std::endl; }

    virtual void make_frame(int available, int &frame_size)const {
    }

    virtual std::string get_operand( 
    Context context, std::stack<std::string> available_registers) const
    {
        return "get_operand not implemented."; 
    }
    virtual std::string getId() const
    { return "error"; }

};


#endif
