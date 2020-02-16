
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseListener.h"
#include "tree/ParseTreeWalker.h"
#include "tree/ParseTreeProperty.h"

#include <iostream>
#include <fstream>
#include <cstdio>     // fopen
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS

// using namespace std;
// using namespace antlr4;


///////////////////////////////////////////////////////////////////////
// Sample "evaluator" (implemented with a listener and tree properties)
class Evaluator : public ExprBaseListener {
public:
  antlr4::tree::ParseTreeProperty<int> values;  // to store values computed at each node

  void exitS(ExprParser::SContext *ctx) {  // s : e EOF ;
    values.put(ctx, values.get(ctx->e()));
  }

  void exitE(ExprParser::EContext *ctx) {  // e : e MUL e | e ADD e | INT ;
    if (ctx->INT()) {  // if this node has a child INT
    // Alternative:
    // if (ctx->children.size() == 1) {  // if this node has one child
      int val = std::stoi(ctx->INT()->getText());
      values.put(ctx, val);
    }
    else {
      int left = values.get(ctx->e(0));
      int right = values.get(ctx->e(1));
      if (ctx->MUL())  // if this node has a child MUL
        values.put(ctx, left*right);
      else             // must be ADD
        values.put(ctx, left+right);
    }
  }

};
// Sample "Evaluator" (implemented with a listener)
///////////////////////////////////////////////////////////////////////


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

  // create a lexer that consumes the character stream and produces a token stream
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
  
  // create a walker that will traverse the tree
  antlr4::tree::ParseTreeWalker walker;
  
  // create a listener that will evaluate the expression
  Evaluator eval;

  // traverse the tree using this Evaluator with properties
  walker.walk(&eval, tree);

  // dump the result (accessing the root node property)
  std::cout << "result = " << eval.values.get(tree) << std::endl;

  return EXIT_SUCCESS;
}
