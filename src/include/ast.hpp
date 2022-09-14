#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_comparators.hpp"
#include "ast/ast_assignments.hpp"
#include "ast/ast_logical.hpp"
#include "ast/ast_function.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_declarators.hpp"
#include "ast/ast_cond_statements.hpp"

 

extern const Expression *parseAST();

#endif
