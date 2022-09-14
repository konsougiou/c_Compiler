#include "include/ast.hpp"




#include <iomanip>

int main(int argc, char *argv[]){
    std::map<std::string,std::vector<std::string>> bindings;
    std::stack<std::string> available_registers;
    for(int i = 0; i < 8; i++){
        available_registers.push("$s" + std::to_string(i));}
    for(int i = 0; i < 10; i++){
        available_registers.push("$t" + std::to_string(i));
    }
    Context context;
    context.available_mem = 12;
    context.frame_size = 25;
    context.makeNameUnq = 0;
    /*std::vector<std::string> tmp1;
    tmp1.push_back("600");
    tmp1.push_back("int");
    std::vector<std::string> tmp2;
    tmp2.push_back("700");
    tmp2.push_back("int");
    
    context.bindings.insert({"x",tmp1});
    context.bindings.insert({"y",tmp2});
    // Parse the AST*/
    
    const Expression *ast=parseAST();
   

    
    ast->translate("r31", context, available_registers);
    
    // Print it out
    //std::cout << std::fixed << std::setprecision(6) << res << std::endl;

    return 0;
    }
