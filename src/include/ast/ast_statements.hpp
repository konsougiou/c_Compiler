#ifndef ast_statement_hpp
#define ast_statement_hpp

#include <string>
#include <iostream>
#include <cmath>
#include <map>
#include "ast_expression.hpp"


class Single
    : public Expression
{
private:
    ExpressionPtr expr;
protected:
    Single(const ExpressionPtr _expr)
        : expr(_expr)
    {}
public:
    virtual ~Single()
    {
        delete expr;
    }


    ExpressionPtr getExpr() const
    { return expr; }

    virtual void make_frame(int available, int &frame_size)const override{
         
         getExpr()->make_frame(available, frame_size);

    }
};

class Statement
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Statement(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Statement()
    {
        delete left;
        delete right;
    }


    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void make_frame(int available, int &frame_size)const override{
        getLeft()->make_frame(available, frame_size);
         
        getRight()->make_frame(available, frame_size);
    }
};

class Statement3
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr mid;
    ExpressionPtr right;
protected:
    Statement3(ExpressionPtr _left, ExpressionPtr _mid, ExpressionPtr _right)
        : left(_left)
        , mid(_mid)
        , right(_right)
    {}
public:
    virtual ~Statement3()
    {
        delete left;
        delete mid;
        delete right;
    }


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

class Statement4
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr lmid;
    ExpressionPtr rmid;
    ExpressionPtr right;
protected:
    Statement4(ExpressionPtr _left, ExpressionPtr _lmid, ExpressionPtr _rmid, ExpressionPtr _right)
        : left(_left)
        , lmid(_lmid)
        , rmid(_rmid)
        , right(_right)
    {}
public:
    virtual ~Statement4()
    {
        delete left;
        delete lmid;
        delete rmid;
        delete right;
    }


    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    ExpressionPtr getLMid() const
    { return lmid; }

    ExpressionPtr getRMid() const
    { return rmid; }

    virtual void make_frame(int available, int &frame_size)const override{
        getLeft()->make_frame(available, frame_size);
        getLMid()->make_frame(available, frame_size);
        getRMid()->make_frame(available, frame_size);
        getRight()->make_frame(available, frame_size);
    }
};





class StatementList
    : public Statement
{

public:

    StatementList(ExpressionPtr _left, ExpressionPtr _right)
        : Statement(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        getLeft()->translate(dest, context, available_registers);
        getRight()->translate(dest, context, available_registers);

    }
};


class ArgumentList
    : public Statement
{

public:


    ArgumentList(ExpressionPtr _left, ExpressionPtr _right)
        : Statement(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        getLeft()->translate(dest, context, available_registers);
        getRight()->translate(dest, context, available_registers);

    }
};

class ParameterList
    : public Statement
{

public:


    ParameterList(ExpressionPtr _left, ExpressionPtr _right)
        : Statement(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   getLeft()->translate("$a0", context, available_registers);
        getRight()->translate("$a1", context, available_registers);
    }
};

class ParameterList3
    : public Statement3
{

public:


    ParameterList3(ExpressionPtr _left, ExpressionPtr _mid,  ExpressionPtr _right)
        : Statement3(_left, _mid, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   
        getLeft()->translate("$a0", context, available_registers);
        getMid()->translate("$a1", context, available_registers);
        getRight()->translate("$a2", context, available_registers);

    }
};


class ParameterList4
    : public Statement4
{

public:


    ParameterList4(ExpressionPtr _left, ExpressionPtr _lmid, ExpressionPtr _rmid ,  ExpressionPtr _right)
        : Statement4(_left, _lmid, _rmid, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   
        getLeft()->translate("$a0", context, available_registers);
        getLMid()->translate("$a1", context, available_registers);
        getRMid()->translate("$a2", context, available_registers);
        getRight()->translate("$a3", context, available_registers);

    }
};

class for_statement
    : public Statement4
{

public:

    bool is_primitive = false;

    for_statement(ExpressionPtr _left, ExpressionPtr _lmid, ExpressionPtr _rmid , ExpressionPtr _right)
        : Statement4(_left, _lmid, _rmid, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        getLeft()->translate("dest", context, available_registers);
        std::string tmp1 = available_registers.top();
        std::string start = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::string end = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::cout << start <<":"<< std::endl;
        getLMid()->translate(tmp1, context, available_registers);
        std::cout<<"beq "<<tmp1<<",$zero"<<","<<end<<std::endl;
        getRight()->translate("dest", context, available_registers);
        getRMid()->translate("dest", context, available_registers);
        std::cout<< "j " <<start<<std::endl;
        std::cout<< end <<":"<<std::endl;

    }
};

class empty_for_statement
    : public Statement3
{

public:


    empty_for_statement(ExpressionPtr _left, ExpressionPtr _mid,  ExpressionPtr _right)
        : Statement3(_left, _mid, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   
        getLeft()->translate("dest", context, available_registers);
        std::string tmp1 = available_registers.top();
        std::string start = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::string end = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::cout << start <<":"<< std::endl;
        getMid()->translate(tmp1, context, available_registers);
        std::cout<<"beq "<<tmp1<<",$zero"<<","<<end<<std::endl;
        getRight()->translate("dest", context, available_registers);
        std::cout<< "j " <<start<<std::endl;
        std::cout<< end <<":"<<std::endl;

    }
};


class empty_while_statement
    : public Single
{

public:


    empty_while_statement(ExpressionPtr _expr)
        : Single(_expr)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   
        std::string tmp1 = available_registers.top();
        std::string Loop = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::string Endloop = "label" + std::to_string(context.makeNameUnq);
        context.makeNameUnq++;
        std::cout<<Loop<<":"<<std::endl;
        getExpr()-> translate(tmp1, context, available_registers);
        std::cout<<"beq "<<tmp1<<",$zero"<<","<<Endloop<<std::endl;
       // throw std::runtime_error("MulOperator::evaluate is not implemented.");
        std::cout<<"j "<<Loop<<std::endl;
        std::cout<<Endloop<<":"<<std::endl;

    }
};

class Empty_func_declaration
    : public Statement
{

public:

    Empty_func_declaration(ExpressionPtr _left, ExpressionPtr _right)
        : Statement(_left, _right)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {
        std::cout<<"";

    }
};


class Lamda_func_declaration
    : public Single
{

public:


    Lamda_func_declaration(ExpressionPtr _expr)
        : Single(_expr)
    {}
    
     virtual void translate(std::string dest,
        Context &context, std::stack<std::string> available_registers
    ) const override 
    {   
            std::cout<<"";

    }
};




#endif