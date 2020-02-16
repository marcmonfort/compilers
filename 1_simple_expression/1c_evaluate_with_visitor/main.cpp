
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseVisitor.h"

#include <iostream>
#include <fstream>
#include <cstdio>     // fopen
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS

// using namespace std;
// using namespace antlr4;
// using namespace antlrcpp;


//////////////////////////////////////////////////////////////////////
// Sample "evaluator" using visitors
class Evaluator : public ExprBaseVisitor {
public:
  
  // s : e EOF ;
  antlrcpp::Any visitS(ExprParser::SContext *ctx) {
    return visit(ctx->e());  // get value of child expression
  }

  // e : e MUL e | e ADD e | INT ;
  antlrcpp::Any visitE(ExprParser::EContext *ctx) {
    if (ctx->INT()) {   // if this node has a child INT
      return std::stoi(ctx->INT()->getText());    // or: ctx->getText()
    }
    else {
      int left = visit(ctx->e(0));     // get value of left subexpression
      int right = visit(ctx->e(1));    // get value of right subexpression
      if (ctx->MUL())  // if this node has a child MUL
        return left*right;
      else             // must be ADD
        return left+right;
    }
  }
  
};
// Sample "Evaluator" (implemented with a visitor)
//////////////////////////////////////////////////////////////////////


int main(int argc, const char* argv[]) {
  // check the correct use of the program
  if (argc > 2) {
    std::cout << "Usage: ./main [<file>]" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc == 2 and not std::fopen(argv[1], "r")) {
    std::cout << "No such file: " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  // open input file (or std::cin) and create a character stream
  antlr4::ANTLRInputStream input;
  if (argc == 2) {  // reads from <file>
    std::ifstream stream;
    stream.open(argv[1]);
    input = antlr4::ANTLRInputStream(stream);
  }
  else {            // reads fron std::cin
    input = antlr4::ANTLRInputStream(std::cin);
  }

  // create a lexer that consumes the character stream and produce a token stream
  ExprLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);

  // create a parser that consumes the token stream, and parses it
  ExprParser parser(&tokens);

  // call the parser and get the parse tree. s is the initial rule
  antlr4::tree::ParseTree *tree = parser.s();

  // check for lexical or syntactical errors
  if (lexer.getNumberOfSyntaxErrors() > 0 or
      parser.getNumberOfSyntaxErrors() > 0) {
    std::cout << "Lexical and/or syntactical errors have been found." << std::endl;
    return EXIT_FAILURE;
  }
  
  // print the parse tree (for debugging purposes)
  std::cout << tree->toStringTree(&parser) << std::endl;

  ////////////////////////////////////////////////////////////////////

  // create a visitor that will evaluate the expression
  Evaluator eval;

  // traverse the tree using this Evaluator and dump the result
  int result = eval.visit(tree);
  std::cout << "result = " << result << std::endl;

  return EXIT_SUCCESS;
}
