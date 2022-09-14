#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include "ast_expression.hpp"

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Operator()
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
         if (available <= 2){
             frame_size++;
            getRight()->make_frame(available, frame_size);
         }
         else{int new_avail = available - 1;
             getRight()->make_frame(new_avail, frame_size);}
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    bool is_primitive = false;

    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
        std::string tmp1 = available_registers.top();
        available_registers.pop();
        std::stack<std::string> available_new = available_registers;
        std::string tmp2 = available_registers.top();
        available_registers.push(tmp1);
        std::string store_addr = "";
             getLeft()->translate(tmp1, context, available_registers);
        if (available_registers.size() <= 2){
            store_addr = std::to_string((context.available_mem));
            context.available_mem = context.available_mem + 4;

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
        
        std::cout<<"add "<<dest<<","<<tmp1<<","<<tmp2<<std::endl;
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        // TODO-D : Implement this, based on AddOperator::evaluate
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
        
        
        std::cout<<"sub "<<dest<<","<<tmp1<<","<<tmp2<<std::endl;
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
    }
};



class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:

    bool is_primitive = false;

    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
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
        
        
        std::cout<<"mul "<<dest<<","<<tmp1<<","<<tmp2<<std::endl;
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
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
        
        std::cout<<"div "<<tmp1<<","<<tmp2<<std::endl;
        std::cout<<"mflo "<<dest<<std::endl;

        //throw std::runtime_error("DivOperator::evaluate is not implemented.");
    }
};


class BitwiseLeft
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<<"; }
public:
    BitwiseLeft(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
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
         
        std::cout<<"sll "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 

    }
};

class BitwiseRight
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">>"; }
public:
    BitwiseRight(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
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
         
        std::cout<<"srl "<<dest<<","<<tmp1<<","<<tmp2<<std::endl; 
    }
};


class Modulo
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "%"; }
public:
    Modulo(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}
    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
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
        
        std::cout<<"div "<<tmp1<<","<<tmp2<<std::endl;
        std::cout<<"mfhi "<<dest<<std::endl;

        //throw std::runtime_error("DivOperator::evaluate is not implemented.");
    }
};



#endif
