#ifndef ast_unary_hpp
#define ast_unary_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"



class Unary
    : public Expression
{
private:
    ExpressionPtr expr;
protected:
    Unary(const ExpressionPtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Unary()
    {
        delete expr;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getExpr() const
    { return expr; }

    virtual void make_frame(int available, int &frame_size)const override{
         
         getExpr()->make_frame(available, frame_size);

    }
};

class NegOperator
    : public Unary
{
public:
    NegOperator(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();

        getExpr()->translate(tmp1, context, available_registers);
         
        
        std::cout<<"sub "<<dest<<","<<"$zero,"<<tmp1<<std::endl;
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};


class PreIncrement
    : public Unary
{
public:
    PreIncrement (const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "++"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
       std::cout<<"pre_increment"<<std::endl;
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};

class PreDecrement
    : public Unary
{
public:
    PreDecrement (const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "++"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
       std::cout<<"pre_decrement"<<std::endl;
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};

class LogicNot
    : public Unary
{
public:
    LogicNot (const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "++"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
       std::cout<<"slti"<<dest<<","<<dest<<","<<"1"<<std::endl;
    
    }
};

class Return
    : public Unary
{
public:
    Return(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {

        getExpr()->translate("$v0", context, available_registers);


        std::cout<<"lw "<<"$s0,"<<"4 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s1,"<<"8 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s2,"<<"12 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s3,"<<"16 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s4,"<<"20 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s5,"<<"24 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s6,"<<"28 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$s7,"<<"32 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$a0,"<<"36 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$a1,"<<"40 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$a2,"<<"44 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$a3,"<<"48 "<<"($sp)"<<std::endl;
        std::cout<<"lw "<<"$ra,"<<"52 "<<"($sp)"<<std::endl;
        std::cout<<"addiu "<<"$sp,"<<"$sp"<<","<<context.frame_size+8<<std::endl;
        std::cout<<"jr "<<"$ra"<<std::endl;

        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};

class statement
    : public Unary
{
public:
    statement(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {

        getExpr()->translate(dest, context, available_registers);
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};

class PostIncrement
    : public Unary
{
public:
    PostIncrement(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {   
        std::string tmp1 = available_registers.top();
        getExpr()->translate(tmp1, context, available_registers);
        std::cout<<"addiu "<<tmp1<<","<<tmp1<<", 1"<<std::endl;
        std::string address = (context.bindings.at(getExpr()->getId())[0]);
        std::cout << "sw " << tmp1 << "," << address << "($sp)" << std::endl;   
        
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};



class PostDecrement
    : public Unary
{
public:
    PostDecrement(const ExpressionPtr _expr)
        : Unary(_expr)
    {}

    virtual const char *getOpcode() const override
    { return "-"; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {   
        std::string tmp1 = available_registers.top();
        getExpr()->translate(tmp1, context, available_registers);
        std::cout<<"addiu "<<tmp1<<","<<tmp1<<", -1"<<std::endl;
        std::string address = (context.bindings.at(getExpr()->getId())[0]);
        std::cout << "sw " << tmp1 << "," << address << "($sp)" << std::endl;   
        
        // TODO-F: Implement this similar to how AddOperator was implemented.
        //throw std::runtime_error("NegOperator::evaluate is not implemented.");
    }
};





#endif
