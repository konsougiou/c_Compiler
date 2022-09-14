#ifndef ast_cond_statements_hpp
#define ast_cond_statements_hpp

#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include "ast_expression.hpp"

/*std::string makeName(std::string base, Context &context)
{   
    context.makeNameUnq++;
    return base+std::to_string(context.makeNameUnq);
}*/

class Three_branch
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
    ExpressionPtr mid;
protected:
    Three_branch(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right)
        : left(_left)
        , right(_right)
        , mid(_mid)
    {}
public:
    virtual ~Three_branch()
    {
        delete left;
        delete right;
        delete mid;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    ExpressionPtr getMid() const
    { return mid; }
    

    virtual void make_frame(int available, int &frame_size)const override{
        getLeft()->make_frame(available, frame_size);

        getMid()->make_frame(available, frame_size);

        getRight()->make_frame(available, frame_size);
         }

};

class Two_branch
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
    
protected:
    Two_branch(ExpressionPtr _left,  ExpressionPtr _right)
        : left(_left)
        , right(_right)
        
    {}
public:
    virtual ~Two_branch()
    {
        delete left;
        delete right;
        
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }
    

    virtual void make_frame(int available, int &frame_size)const override{
        getLeft()->make_frame(available, frame_size);

        getRight()->make_frame(available, frame_size);
         }

};





class if_else_statement
    : public Three_branch
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    bool is_primitive = false;

    if_else_statement(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right)
        : Three_branch(_left, _mid, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
        std::string tmp1 = available_registers.top();
        std::string Else = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::string Endif = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        getLeft()-> translate(tmp1, context, available_registers);
        std::cout<<"beq "<<tmp1<<",$zero,"<<Else<<std::endl;
        getMid() -> translate(dest, context, available_registers);
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
       std::cout<<"j "<<Endif<<std::endl;
       std::cout<<Else<<":"<<std::endl;
       getRight() -> translate(dest, context, available_registers);
       std::cout<<Endif<<":"<<std::endl;

    }
};


class if_statement
    : public Two_branch
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    bool is_primitive = false;

    if_statement(ExpressionPtr _left, ExpressionPtr _right)
        : Two_branch(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
        std::string tmp1 = available_registers.top();
        std::string Endif = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        getLeft()-> translate(tmp1, context, available_registers);
        std::cout<<"beq "<<tmp1<<",$zero"<<","<<Endif<<std::endl;
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
        getRight() -> translate(dest, context, available_registers);
        std::cout<<Endif<<":"<<std::endl;

    }
};

class while_statement
    : public Two_branch
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    bool is_primitive = false;

    while_statement(ExpressionPtr _left, ExpressionPtr _right)
        :Two_branch(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
        std::string tmp1 = available_registers.top();
        std::string Loop = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::string Endloop = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::cout<<Loop<<":"<<std::endl;
        getLeft()-> translate(tmp1, context, available_registers);
        std::cout<<"beq "<<tmp1<<",$zero"<<","<<Endloop<<std::endl;
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
        getRight() -> translate(dest, context, available_registers);
        std::cout<<"j "<<Loop<<std::endl;
        std::cout<<Endloop<<":"<<std::endl;

    }
};

class Arg_func_declaration
    : public Three_branch
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    bool is_primitive = false;

    Arg_func_declaration(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right)
        : Three_branch(_left, _mid, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   
        int frame_length = 13;
        getRight()->make_frame(18, frame_length);
        context.frame_size = 4*frame_length;
        context.available_mem = 56;
        context.makeNameUnq = 36;
        std::string func_name = getLeft()->getId();  
        getMid()->translate("arg", context, available_registers);
        context.makeNameUnq = 0;
        std::cout<<".global "<<func_name<<std::endl;
        std::cout<<func_name<<":"<<std::endl;
        std::cout<<"addiu "<<"$sp,"<<"$sp"<<", -"<<context.frame_size+8<<std::endl;
        std::cout<<"sw "<<"$s0,"<<"4 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s1,"<<"8 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s2,"<<"12 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s3,"<<"16 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s4,"<<"20 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s5,"<<"24 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s6,"<<"28 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$s7,"<<"32 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$a0,"<<"36 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$a1,"<<"40 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$a2,"<<"44 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$a3,"<<"48 "<<"($sp)"<<std::endl;
        std::cout<<"sw "<<"$ra,"<<"52 "<<"($sp)"<<std::endl;

        getRight()->translate(dest, context, available_registers);

    }
};


#endif