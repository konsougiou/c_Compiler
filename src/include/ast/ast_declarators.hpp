#ifndef ast_declarators_hpp
#define ast_declarators_hpp

#include "ast_expression.hpp"
#include <string>
#include <iostream>
#include <map>
#include <vector>

class IntDeclarator
    : public Expression
{
private:
    std::string id;;
public:
    
    //IntDeclarator(const ExpressionPtr _expr)
        //: expr(_expr)
        IntDeclarator(const std::string &_id)
        : id(_id)
        {}
    ///   ExpressionPtr getExpr() const
    //{ return expr; }

    virtual std::string getId() const override
    { return id.substr(4,id.length()-1); }

    virtual void translate(std::string dest,
         Context &context, std::stack<std::string> available_registers
    ) const override
    {   
    
        if (dest == "arg"){
            
            std::vector<std::string> temp_vector;
            temp_vector.push_back(std::to_string(context.makeNameUnq));
            context.makeNameUnq = context.makeNameUnq + 4;
            temp_vector.push_back("int");
            context.bindings.insert({getId(),temp_vector});
            
        }
        else if(dest == "assign"){
        std::string tmp1 = available_registers.top();
        std::vector<std::string> temp_vector;
        temp_vector.push_back(std::to_string(context.available_mem));
        std::string offset = std::to_string(context.available_mem);
        context.available_mem = context.available_mem +4;
        temp_vector.push_back("int");
        context.bindings.insert({getId(),temp_vector});

        }else{
        std::string tmp1 = available_registers.top();
        std::vector<std::string> temp_vector;
        temp_vector.push_back(std::to_string(context.available_mem));
        std::string offset = std::to_string(context.available_mem);
        context.available_mem = context.available_mem +4;
        temp_vector.push_back("int");
        std::cout << "li "<< tmp1 << ",0" << std::endl;
        std::cout << "sw "<< tmp1<<","<< offset<<"($sp)"<< std::endl;
        context.bindings.insert({getId(),temp_vector});
        }
    }    


    virtual std::string get_operand(
     Context context, std::stack<std::string> available_registers) const override
    {
        return context.bindings.at(getId())[0];
    }

    virtual void make_frame(int available, int &frame_size)const override{

            frame_size++;
        }
};


#endif