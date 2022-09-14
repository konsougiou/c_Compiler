#ifndef ast_logical_hpp
#define ast_logical_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <string>
#include <iostream>

class Logical
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Logical(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Logical()
    {
        delete left;
        delete right;
    }

    virtual const char * getLogical() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }


    virtual void translate(
       std::string dest,
        Context &context, 
        std::stack<std::string> available_registers
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }

        virtual void make_frame(int available, int &frame_size)const override{
         getLeft()->make_frame(available, frame_size);
         if (available <= 2){
             frame_size++;
            getRight()->make_frame(available, frame_size);
         }
         else{int new_avail = available - 1;
             getRight()->make_frame(new_avail, frame_size);}
    }
};

class AndLogical
    : public Logical
{
public:
    AndLogical(ExpressionPtr _left, ExpressionPtr _right)
        : Logical(_left, _right)
    {}

    virtual const char *getLogical() const
    { return "<"; }

    virtual void translate(std::string dest,
        Context &context, 
        std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::stack<std::string> available_new = available_registers;
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        std::string store_addr = "";
             getLeft()->translate(tmp1, context, available_registers);
        if (available_registers.size() <= 2){
            store_addr = std::to_string((context.available_mem));
            context.available_mem = context.available_mem +4;

            std::cout<<"sw "<<tmp1<<" "<<store_addr<<" ($sp)"<<std::endl;
            getRight()->translate(tmp2, 
            context, available_registers);
            }
        else{
            getRight()->translate(tmp2, 
            context, available_new);
         }
        if (available_registers.size() <= 2){
            std::cout<<"lw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
        }
        
        std::cout<<"and "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 
    }
};

class OrLogical
    : public Logical
{
public:
    OrLogical(ExpressionPtr _left, ExpressionPtr _right)
        : Logical(_left, _right)
    {}

    virtual const char *getLogical() const
    { return "||"; }

    virtual void translate(std::string dest,
        Context &context, 
        std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::stack<std::string> available_new = available_registers;
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        std::string store_addr = "";
             getLeft()->translate(tmp1, context, available_registers);
        if (available_registers.size() <= 2){
            store_addr = std::to_string((context.available_mem));
            context.available_mem = context.available_mem +4;

            std::cout<<"sw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
            getRight()->translate(tmp2, 
            context, available_registers);
            }
        else{
            getRight()->translate(tmp2, 
            context, available_new);
         }
        if (available_registers.size() <= 2){
            std::cout<<"lw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
        }
        
        std::cout<<"or "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 
    }
};

class BitwiseAndLogical
    : public Logical
{
public:
    BitwiseAndLogical(ExpressionPtr _left, ExpressionPtr _right)
        : Logical(_left, _right)
    {}

    virtual const char *getLogical() const
    { return "&"; }

    virtual void translate(std::string dest,
        Context &context, 
        std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::stack<std::string> available_new = available_registers;
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        std::string store_addr = "";
             getLeft()->translate(tmp1, context, available_registers);
        if (available_registers.size() <= 2){
            store_addr = std::to_string((context.available_mem));
            context.available_mem++;

            std::cout<<"sw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
            getRight()->translate(tmp2, 
            context, available_registers);
            }
        else{
            getRight()->translate(tmp2, 
            context, available_new);
         }
        if (available_registers.size() <= 2){
            std::cout<<"lw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
        }
        std::cout<<"and "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 
    
    }
};

class BitwiseOrLogical
    : public Logical
{
public:
    BitwiseOrLogical(ExpressionPtr _left, ExpressionPtr _right)
        : Logical(_left, _right)
    {}

    virtual const char *getLogical() const
    { return "|"; }

     virtual void translate(std::string dest,
        Context &context, 
        std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::stack<std::string> available_new = available_registers;
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        std::string store_addr = "";
        getLeft()->translate(tmp1, context, available_registers);
        if (available_registers.size() <= 2){
            store_addr = std::to_string((context.available_mem));
            context.available_mem = context.available_mem +4;

            std::cout<<"sw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
            getRight()->translate(tmp2, 
            context, available_registers);
            }
        else{
            getRight()->translate(tmp2, 
            context, available_new);
        }
        if (available_registers.size() <= 2){
            std::cout<<"lw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
        }
        
        std::cout<<"or "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 
    }
    
};

class BitwiseXorLogical
    : public Logical
{
public:
    BitwiseXorLogical(ExpressionPtr _left, ExpressionPtr _right)
        : Logical(_left, _right)
    {}

    virtual const char *getLogical() const
    { return "^"; }

    virtual void translate(
        std::string dest,
        Context &context, 
        std::stack<std::string> available_registers
    ) const override
    {
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::stack<std::string> available_new = available_registers;
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        std::string store_addr = "";
        getLeft()->translate(tmp1, context, available_registers);
        if (available_registers.size() <= 2){
            store_addr = std::to_string((context.available_mem));
            context.available_mem = context.available_mem +4;

            std::cout<<"sw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
            getRight()->translate(tmp2, 
            context, available_registers);
            }
        else{
            getRight()->translate(tmp2, 
            context, available_new);
        }
        if (available_registers.size() <= 2){
            std::cout<<"lw "<<tmp1<<","<<store_addr<<" ($sp)"<<std::endl;
        }

        std::cout<<"xor "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 
    }
};


#endif