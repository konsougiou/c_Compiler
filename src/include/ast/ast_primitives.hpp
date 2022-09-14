#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include <map>
#include "ast_expression.hpp"


class Variable
    : public Expression
{
private:
    std::string id;
public:
    
    Variable(const std::string &_id)
        : id(_id)
        
    {}

    virtual std::string getId() const override
    { return id; }

    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {       
        /*if(dest == "param_list"){
        std::string tmp1 = available_registers.top();
        
        std::cout<<"lw "<<tmp1<<","<<(context.bindings.at(id))[0]<<" ($sp)"<<std::endl;

        }else{*/
        std::cout<<"lw "<<dest<<","<<(context.bindings.at(id))[0]<<" ($sp)"<<std::endl;
        

    }    

    virtual std::string get_operand(
    Context context, std::stack<std::string> available_registers) 
    const override
    {
        return (context.bindings.at(id))[0];
    }
};

class Number
    : public Expression
{
private:
    double value;
public:
    
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }


    virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override
    {
        /*if(dest == "param_list"){
        std::string tmp1 = available_registers.top();
        std::string tmp = std::to_string(value);
        tmp = tmp.substr(0, tmp.find("."));
        std::cout<<"li "<<<<","<<tmp<<std::endl;

        }else{ */
    
        std::string tmp = std::to_string(value);
        tmp = tmp.substr(0, tmp.find("."));
        std::cout<<"li "<<dest<<","<<tmp<<std::endl;
        
    }

    virtual std::string get_operand( Context context,
     std::stack<std::string> available_registers
   ) const override
    {
        return std::to_string(value);
    }
};


#endif
