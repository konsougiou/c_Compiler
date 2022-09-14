#ifndef ast_comparators_hpp
#define ast_comparators_hpp


#include "ast_expression.hpp"
#include <cmath>
#include <string>
#include <iostream>

class Comparator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Comparator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Comparator()
    {
        delete left;
        delete right;
    }

    virtual const char * getComparator() const =0;

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
         else{getRight()->make_frame(available, frame_size);}
    }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class LessThanComparator
    : public Comparator
{
public:
    LessThanComparator(ExpressionPtr _left, ExpressionPtr _right)
        : Comparator(_left, _right)
    {}

    virtual const char *getComparator() const
    { return "<"; }

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
        
        std::cout << "slt "<<dest<<","<<tmp1<<","<<tmp2 << std::endl;
    }
};

class MoreThanComparator
    : public Comparator
{
public:
    MoreThanComparator(ExpressionPtr _left, ExpressionPtr _right)
        : Comparator(_left, _right)
    {}

    virtual const char *getComparator() const
    { return ">"; }

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
        
        std::cout << "slt "<<dest<<","<<tmp2<<","<<tmp1<< std::endl;
    }
};

  

class MoreEqualComparator
    : public Comparator
{
public:
    MoreEqualComparator(ExpressionPtr _left, ExpressionPtr _right)
        : Comparator(_left, _right)
    {}

    virtual const char *getComparator() const
    { return ">="; }

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
        
        std::cout << "subi "<<tmp2<<","<<tmp2<<",1" <<std::endl;
        std::cout << "slt "<<dest<<","<<tmp2<<","<<tmp1<<std::endl;  
    }
};

class LessEqualComparator
    : public Comparator
{
public:
    LessEqualComparator(ExpressionPtr _left, ExpressionPtr _right)
        : Comparator(_left, _right)
    {}

    virtual const char *getComparator() const
    { return "<="; }

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
        
        std::cout <<"addi "<<tmp2<<",1" << std::endl;
        std::cout <<"slt "<<dest<<","<<tmp1<<","<<tmp2 << std::endl;
    }
};

class EqualComparator
    : public Comparator
{
public:
    EqualComparator(ExpressionPtr _left, ExpressionPtr _right)
        : Comparator(_left, _right)
    {}

    virtual const char *getComparator() const
    { return "=="; }

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
            std::string Else = "label" + std::to_string(context.makeNameUnq);
            context.makeNameUnq = context.makeNameUnq + 1;
            std::string End = "label" + std::to_string(context.makeNameUnq);
            std::cout<<"beq "<<tmp1<<","<<tmp2<<","<<Else<<std::endl;
            std::cout<<"li "<<dest<<","<<"0"<<std::endl;
            std::cout<<"j "<<End<<std::endl;
            std::cout<<Else<<":"<<std::endl;
            std::cout<<"li "<<dest<<","<<"1"<<std::endl;
            std::cout<<End<<":"<<std::endl;

    }
};

class NotEqualComparator
    : public Comparator
{
public:
    NotEqualComparator(ExpressionPtr _left, ExpressionPtr _right)
        : Comparator(_left, _right)
    {}

    virtual const char *getComparator() const
    { return "!="; }

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
            std::string Else = "label" + std::to_string(context.makeNameUnq);
            context.makeNameUnq = context.makeNameUnq + 1;
            std::string End = "label" + std::to_string(context.makeNameUnq);
            std::cout<<"bne "<<tmp1<<","<<tmp2<<","<<Else<<std::endl;
            std::cout<<"li "<<dest<<","<<"0"<<std::endl;
            std::cout<<"j "<<End<<std::endl;
            std::cout<<Else<<":"<<std::endl;
            std::cout<<"li "<<dest<<","<<"1"<<std::endl;
            std::cout<<End<<":"<<std::endl;
    }
        
};

#endif