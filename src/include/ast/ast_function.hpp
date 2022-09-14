#ifndef ast_function_hpp
#define ast_function_hpp


#include "ast_expression.hpp"
#include <cmath>
#include <string>
#include <iostream>



class Function
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Function(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
    virtual ~Function()
    {
        delete left;
        delete right;
    }

    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

};


class Function_declaration
    : public Function
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    Function_declaration(ExpressionPtr _left, ExpressionPtr _right)
        : Function(_left, _right)
    {}
    virtual void make_frame(int available, int &frame_size)const {
         std::cout<<"error"<<std::endl; 
    }
    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const  override

    {   int frame_length = 13;

        getRight()->make_frame(18, frame_length );
        context.frame_size = 4*frame_length;
        context.available_mem = 56;
        context.makeNameUnq = 0;
        std::string func_name = getLeft()->getId();
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

class Function_call
    : public Function
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:

    Function_call(ExpressionPtr _left, ExpressionPtr _right)
        : Function(_left, _right)
    {}
    virtual void make_frame(int available, int &frame_size)const {
         frame_size = frame_size + 40;
    }
    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const  override
    {   
    
        
        std::string func_name = getLeft()->getId();

        std::stack<std::string> available_registers_tmp;


        getRight()->translate("$a0", context, available_registers);
        std::stack<std::string> non_avail;
        int non_avail_size = 18 - available_registers.size();
        if (non_avail_size>10){for(int i = available_registers.size(); i < 8; i++){
                non_avail.push("$s"+std::to_string(i));}
                 for(int i = 0; i < 10; i++){non_avail.push("$t"+std::to_string(i));}}
         else { for(int i = available_registers.size()-8; i < 10; i++){
             non_avail.push("$t"+std::to_string(i));
         }
         }
        std::stack<std::string> tmp_non_avail = non_avail;
        std::stack<int> mem_addresses;
        for(int i = 0; i < non_avail.size(); i ++){
        std::cout<<"sw "<<non_avail.top()<<","<<context.available_mem<<" ($sp)"<<std::endl;
        mem_addresses.push(context.available_mem);
        context.available_mem = context.available_mem + 4;
        non_avail.pop();
        }
        std::cout<<"jal "<<func_name<<std::endl;
        for(int i = 0; i < tmp_non_avail.size(); i ++){
        std::cout<<"lw "<<tmp_non_avail.top()<<","<<std::to_string(mem_addresses.top())<<" ($sp)"<<std::endl;
        mem_addresses.pop();
        }
               
        std::cout<<"move "<<dest<<",$v0"<<std::endl;
    

    }
};


#endif


