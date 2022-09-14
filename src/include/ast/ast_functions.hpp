#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;
protected:
    Function(ExpressionPtr _arg)
        : arg(_arg)
    {}
public:
    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    ExpressionPtr getArg() const
    { return arg; }

    virtual void print(std::ostream &dst) const override
    {
        dst<<getFunction()<<"( ";
        arg->print(dst);
        dst<<" )";
    }

    virtual void translate(std::string dest,
        const std::map<std::string,std::string> &bindings
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class LogFunction
    : public Function
{
public:
    LogFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "log"; }
    
    virtual void translate(std::string dest,
        const std::map<std::string,std::string> &bindings
    ) const override
    {
        
        std::cout<<"log"<<std::endl;
        
        
        //return log(v);
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
       // throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
    // TODO-E : Override evaluate, and implement it
};

class ExpFunction
    : public Function
{
public:
    ExpFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "exp"; }

    virtual void translate(std::string dest,
        const std::map<std::string,std::string> &bindings
    ) const override
    {
        
        std::cout<<"exp"<<std::endl;
        
        //return pow(M_E,v);
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
       // throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "sqrt"; }

    virtual void translate(std::string dest,
        const std::map<std::string,std::string> &bindings
    ) const override
    {
       
        std::cout<<"sqrt"<<std::endl;
        
        
        //return sqrt(v);
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
       // throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};


#endif
