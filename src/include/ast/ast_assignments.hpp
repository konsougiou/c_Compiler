#ifndef ast_assignments_hpp
#define ast_assignments_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <string>
#include <iostream>
#include <stack>

class Assignment
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Assignment(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Assignment()
    {
        delete left;
        delete right;
    }

    virtual const char * getAssignment() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers   
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }

    virtual void make_frame(int available, int &frame_size)const override{
            getRight()->make_frame(available, frame_size);

    }


};

class VariableAssignment
    : public Assignment
{
public:
    VariableAssignment(ExpressionPtr _left, ExpressionPtr _right)
        : Assignment(_left, _right)
    {}

    virtual const char *getAssignment() const
    { return "="; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        getRight()->translate(tmp1, context, available_registers);
        std::string id = getLeft()->getId();
        std::string address = (context.bindings.at(id)[0]);
        std::cout << "sw " << tmp1 << "," << address << "($sp)" << std::endl;   
    }
};


class DeclaratorAssignment
    : public Assignment
{
public:
    DeclaratorAssignment(ExpressionPtr _left, ExpressionPtr _right)
        : Assignment(_left, _right)
    {}

    virtual const char *getAssignment() const
    { return "="; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        std::string offset = std::to_string(context.available_mem);
        getLeft()->translate("assign", context, available_registers);
        getRight()->translate(tmp1, context, available_registers);
        std::cout<<"sw "<<tmp1<<","<<offset<<" ($sp)"<<std::endl;
     
    }
};



class SelfAddAssignment
    : public Assignment
{
public:
    SelfAddAssignment(ExpressionPtr _left, ExpressionPtr _right)
        : Assignment(_left, _right)
    {}

    virtual const char *getAssignment() const
    { return "="; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        
        getRight()->translate(tmp1, context, available_registers);
        std::string id = getLeft()->getId();
        std::string address = (context.bindings.at(id)[0]);
        std::cout<<"lw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
        std::cout<<"add "<<tmp2<<","<<tmp2<<","<<tmp1<<std::endl;
        std::cout<<"sw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
    }
};

class SelfSubAssignment
    : public Assignment
{
public:
    SelfSubAssignment(ExpressionPtr _left, ExpressionPtr _right)
        : Assignment(_left, _right)
    {}

    virtual const char *getAssignment() const
    { return "="; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        
        getRight()->translate(tmp1, context, available_registers);
        std::string id = getLeft()->getId();
        std::string address = (context.bindings.at(id)[0]);
        std::cout<<"lw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
        std::cout<<"sub "<<tmp2<<","<<tmp2<<","<<tmp1<<std::endl;
        std::cout<<"sw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
    }
};

class SelfMulAssignment
    : public Assignment
{
public:
    SelfMulAssignment(ExpressionPtr _left, ExpressionPtr _right)
        : Assignment(_left, _right)
    {}

    virtual const char *getAssignment() const
    { return "="; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        
        getRight()->translate(tmp1, context, available_registers);
        std::string id = getLeft()->getId();
        std::string address = (context.bindings.at(id)[0]);
        std::cout<<"lw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
        std::cout<<"mul "<<tmp2<<","<<tmp2<<","<<tmp1<<std::endl;
        std::cout<<"sw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
    }
};


class SelfDivAssignment
    : public Assignment
{
public:
    SelfDivAssignment(ExpressionPtr _left, ExpressionPtr _right)
        : Assignment(_left, _right)
    {}

    virtual const char *getAssignment() const
    { return "="; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        
        getRight()->translate(tmp1, context, available_registers);
        std::string id = getLeft()->getId();
        std::string address = (context.bindings.at(id)[0]);
        std::cout<<"lw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
        std::cout<<"div "<<tmp2<<","<<tmp1<<std::endl;
        std::cout<<"mflo "<<tmp2<<std::endl;
        std::cout<<"sw "<<tmp2<<","<<address<<" ($sp)"<<std::endl;
    }
};




#endif