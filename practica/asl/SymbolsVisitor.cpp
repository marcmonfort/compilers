//////////////////////////////////////////////////////////////////////
//
//    SymbolsVisitor - Walk the parser tree to register symbols
//                     for the Asl programming language
//
//    Copyright (C) 2019  Universitat Politecnica de Catalunya
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU General Public License
//    as published by the Free Software Foundation; either version 3
//    of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
//
//    contact: José Miguel Rivero (rivero@cs.upc.edu)
//             Computer Science Department
//             Universitat Politecnica de Catalunya
//             despatx Omega.110 - Campus Nord UPC
//             08034 Barcelona.  SPAIN
//
//////////////////////////////////////////////////////////////////////

#include "SymbolsVisitor.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>
#include <vector>

#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
SymbolsVisitor::SymbolsVisitor(TypesMgr       & Types,
			       SymTable       & Symbols,
			       TreeDecoration & Decorations,
			       SemErrors      & Errors) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations},
  Errors{Errors} {
}


// Methods to visit each kind of node:
//
antlrcpp::Any SymbolsVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = Symbols.pushNewScope("$global$");
  putScopeDecor(ctx, sc);
  for (auto ctxFunc : ctx->function()) {
    visit(ctxFunc);
  }
  //Symbols.print();
  //Symbols.printCurrentScope();
  Symbols.popScope();
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  std::string funcName = ctx->ID()->getText();
  SymTable::ScopeId sc = Symbols.pushNewScope(funcName);
  putScopeDecor(ctx, sc);
  
  /*if (ctx->parameters()) {
    if (funcName == "main") Errors.noMainProperlyDeclared(ctx);
    else visit(ctx->parameters());   // else???
  }*/ //working but error in different lane...???

  visit(ctx->parameters());
  visit(ctx->declarations()); //++

  //Symbols.print();
  Symbols.popScope();

  std::string ident = ctx->ID()->getText();
  if (Symbols.findInCurrentScope(ident)) {
    Errors.declaredIdent(ctx->ID());
  }
  else {    //hace falta mirar si hay return!!! y tambien llamar parameters!!!
    std::vector<TypesMgr::TypeId> lParamsTy;
    for (int i = 0; i < ctx->parameters()->type().size(); ++i){
      lParamsTy.push_back(getTypeDecor(ctx->parameters()->type(i)));
    }

    TypesMgr::TypeId tRet = Types.createVoidTy();
    if (ctx->basic_type()) {
      visit(ctx->basic_type());
      tRet = getTypeDecor(ctx->basic_type());
    }

    TypesMgr::TypeId tFunc = Types.createFunctionTy(lParamsTy, tRet);
    Symbols.addFunction(ident, tFunc);
    //putTypeDecor(ctx, tFunc); //NUEVO ??? CORRECTO????? -> mejor no! da errores laterales
    //Symbols.setCurrentFunctionTy(tFunc);
  }

  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitParameters(AslParser::ParametersContext *ctx) {    //NEW ¿¿¿¿NO entra
  DEBUG_ENTER();
  //visit(ctx->type());   //outside or inside???

  for (int i = 0; i < ctx->ID().size(); i++) {  
    visit(ctx->type(i));  //here ???
    
	  std::string ident = ctx->ID(i)->getText();
	  if (Symbols.findInCurrentScope(ident)) {  //can it be find???
	    Errors.declaredIdent(ctx->ID(i));
	  }
	  else {
	    TypesMgr::TypeId t1 = getTypeDecor(ctx->type(i));
	    Symbols.addParameter(ident, t1);
	  }
  }
	DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();


  visit(ctx->type()); //outside or inside??? with type(i) or not???
  for (int i = 0; i < ctx->ID().size(); i++) {   //NEW
	  std::string ident = ctx->ID(i)->getText();
	  if (Symbols.findInCurrentScope(ident)) {
	    Errors.declaredIdent(ctx->ID(i));
	  }
	  else {
	    TypesMgr::TypeId t1 = getTypeDecor(ctx->type());
	    Symbols.addLocalVar(ident, t1);
	  }
  }
	DEBUG_EXIT();
  return 0;
}


/*antlrcpp::Any SymbolsVisitor::visitType(AslParser::TypeContext *ctx) {  //faltaria array en otra funcion!
  DEBUG_ENTER();

  TypesMgr::TypeId t = Types.createErrorTy();

  if (ctx->INT()) t = Types.createIntegerTy();
	else if (ctx->FLOAT()) t = Types.createFloatTy();
	else if (ctx->BOOL()) t = Types.createBooleanTy();
	else if (ctx->CHAR()) t = Types.createCharacterTy();

  putTypeDecor(ctx, t);

  DEBUG_EXIT();
  return 0;
}*/

antlrcpp::Any SymbolsVisitor::visitType(AslParser::TypeContext *ctx) {  //faltaria array en otra funcion!
  DEBUG_ENTER();

  TypesMgr::TypeId t;

  if (ctx->basic_type()) {
    visit(ctx->basic_type());
    t = getTypeDecor(ctx->basic_type());
    putTypeDecor(ctx, t);
  }
  else {
    visit(ctx->array_type());
    t = getTypeDecor(ctx->array_type());
  }

  putTypeDecor(ctx, t);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any SymbolsVisitor::visitBasic_type(AslParser::Basic_typeContext *ctx) {  //faltaria array en otra funcion!
  DEBUG_ENTER();

  TypesMgr::TypeId t = Types.createErrorTy();

  if (ctx->INT()) t = Types.createIntegerTy();
	else if (ctx->FLOAT()) t = Types.createFloatTy();
	else if (ctx->BOOL()) t = Types.createBooleanTy();
	else if (ctx->CHAR()) t = Types.createCharacterTy();

  putTypeDecor(ctx, t);

  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any SymbolsVisitor::visitArray_type(AslParser::Array_typeContext *ctx) {  //faltaria array en otra funcion!
  DEBUG_ENTER();

  //TypesMgr::TypeId t = Types.createErrorTy();

  //visit(ctx->INTVAL());
  unsigned int size = std::stoi(ctx->INTVAL()->getText());
  visit(ctx->basic_type()); //hace falta???
  TypesMgr::TypeId elemType = getTypeDecor(ctx->basic_type());

  TypesMgr::TypeId t = Types.createArrayTy(size,elemType);

  putTypeDecor(ctx, t);

  DEBUG_EXIT();
  return 0;
}

// antlrcpp::Any SymbolsVisitor::visitStatements(AslParser::StatementsContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitRelational(AslParser::RelationalContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitValue(AslParser::ValueContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any SymbolsVisitor::visitIdent(AslParser::IdentContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId SymbolsVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId SymbolsVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope and Type
void SymbolsVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void SymbolsVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
