//////////////////////////////////////////////////////////////////////
//
//    TypeCheckVisitor - Walk the parser tree to do the semantic
//                       typecheck for the Asl programming language
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


#include "TypeCheckVisitor.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/SemErrors.h"

#include <iostream>
#include <string>

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
TypeCheckVisitor::TypeCheckVisitor(TypesMgr       & Types,
				   SymTable       & Symbols,
				   TreeDecoration & Decorations,
				   SemErrors      & Errors) :
  Types{Types},
  Symbols {Symbols},
  Decorations{Decorations},
  Errors{Errors} {
}

// Methods to visit each kind of node:
//
antlrcpp::Any TypeCheckVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  //Symbols.print();
  for (auto ctxFunc : ctx->function()) {
    visit(ctxFunc);
  }
  if (Symbols.noMainProperlyDeclared())
    Errors.noMainProperlyDeclared(ctx);
  Symbols.popScope();
  Errors.print();
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();

  //tipo return de la funcion en scope
  std::vector<TypesMgr::TypeId> lParamsTy;
  TypesMgr::TypeId tRet = Types.createVoidTy();
  if (ctx->basic_type() != NULL){
    //visit(ctx->basic_type());   //no haria falta, basic_type ya se visito en Symbols.
    tRet = getTypeDecor(ctx->basic_type());
  }
  TypesMgr::TypeId tFunc = Types.createFunctionTy(lParamsTy, tRet); //tipo funcion en scope
  Symbols.setCurrentFunctionTy(tFunc);

  // otro metodo, tipo return!
  //std::cout << Types.to_string(getTypeDecor(ctx)) << std::endl;
  //Symbols.setCurrentFunctionTy(getTypeDecor(ctx));    //error en (chkt_04)
  //std::cout << Types.to_string(Symbols.getCurrentFunctionTy()) << std::endl;


  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  //Symbols.print();

  visit(ctx->statements());
  Symbols.popScope();

  DEBUG_EXIT();
  return 0;
}



////  ////  ////  ////  ////  ////  ////  ////
//// STATEMENTS   ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////  ////

antlrcpp::Any TypeCheckVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  visitChildren(ctx);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and //diferente tipo, no se pueden copiar
      (not Types.copyableTypes(t1, t2)))
    Errors.incompatibleAssignment(ctx->ASSIGN());
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr()))) //mal identificador
    Errors.nonReferenceableLeftExpr(ctx->left_expr());
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements(0));

  if (ctx->ELSE())
    visit(ctx->statements(1));  //ELSE ¿¿¿evaluar siempre el else???

  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1)))
    Errors.booleanRequired(ctx);
  visit(ctx->statements());
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->ident());  //visitamos ID
  for (size_t i = 0; i < (ctx->expr()).size(); ++i) {  //visitamo parametros
          visit(ctx->expr(i));
  }
  
  TypesMgr::TypeId tID = getTypeDecor(ctx->ident());

  if (not Types.isFunctionTy(tID) and not Types.isErrorTy(tID)) {   //ID no es funcion
    Errors.isNotCallable(ctx->ident());
  }
  else if (not Types.isErrorTy(tID)){

    /*if (Types.isVoidFunction(tID)){   //it can be void.. (we allow it)
      Errors.isNotFunction(ctx->ident());
      t = Types.createErrorTy();
    }*/

    if (Types.getNumOfParameters(tID) != (ctx->expr()).size() ){  //diferente numero de parametros
      Errors.numberOfParameters(ctx->ident());
    }
    else {
      std::vector<TypesMgr::TypeId> lParamsTy = Types.getFuncParamsTypes(tID);
      for (size_t i = 0; i < lParamsTy.size(); ++i) {
        //visit(ctx->expr(i));  //ya se visita antes
        TypesMgr::TypeId tPar = getTypeDecor(ctx->expr(i));
        //std::cout << Types.to_string(getTypeDecor(ctx->expr(i))) << std::endl;
        //std::cout << Types.to_string(lParamsTy[i]) << std::endl;

        if (not Types.equalTypes(lParamsTy[i], tPar)) {
          if (not (Types.isIntegerTy(tPar) and Types.isFloatTy(lParamsTy[i])))
            Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
        }
      }
    }
  }
  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {    //NEW
  DEBUG_ENTER();

  TypesMgr::TypeId f = Symbols.getCurrentFunctionTy();

  if (ctx->expr()) {
    visit(ctx->expr());
    TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
    TypesMgr::TypeId tr = Types.getFuncReturnType(f);

    /* std::cout << "hola" << std::endl;
    if (Types.isIntegerTy(tr)) std::cout << "1" << std::endl;
    if (Types.isErrorTy(tr)) std::cout << "2" << std::endl;
    if (Types.isFloatTy(tr)) std::cout << "3" << std::endl;
    if (Types.isBooleanTy(tr)) std::cout << "4" << std::endl;
    if (Types.isCharacterTy(tr)) std::cout << "5" << std::endl;
    if (Types.isVoidTy(tr)) std::cout << "6" << std::endl;
    if (Types.isNumericTy(tr)) std::cout << "7" << std::endl;
    if (Types.isPrimitiveTy(tr)) std::cout << "8" << std::endl;
    if (Types.isPrimitiveNonVoidTy(tr)) std::cout << "9" << std::endl;
    if (Types.isFunctionTy(tr)) std::cout << "10" << std::endl;
    //if (Types.isVoidFunction(tr)) std::cout << "11" << std::endl;
    std::cout << "adios" << std::endl; */

    //mirar tipo non-primitive ???

    if (not Types.isErrorTy(t1) and Types.isVoidFunction(f)) 
      Errors.incompatibleReturn(ctx->RETURN());  //funcion VOID salida no void

    else if ((not Types.isErrorTy(t1)) and (not Types.equalTypes(t1, tr))){
      if (not (Types.isIntegerTy(t1) and Types.isFloatTy(tr))) {
        Errors.incompatibleReturn(ctx->RETURN());   //tipos diferentes en el return
      }

    }
  }
  else if (not Types.isVoidFunction(f)) Errors.incompatibleReturn(ctx->RETURN());  //salida void, funcion no void
  
  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->left_expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->left_expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)) and
      (not Types.isFunctionTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  if ((not Types.isErrorTy(t1)) and (not getIsLValueDecor(ctx->left_expr())))
    Errors.nonReferenceableExpression(ctx);
  DEBUG_EXIT();
  return 0;
}

antlrcpp::Any TypeCheckVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  visit(ctx->expr());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr());
  if ((not Types.isErrorTy(t1)) and (not Types.isPrimitiveTy(t1)))
    Errors.readWriteRequireBasic(ctx);
  DEBUG_EXIT();
  return 0;
}

// antlrcpp::Any TypeCheckVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }



////  ////  ////  ////  ////  ////  ////  ////  ////
////  LEFT EXPRESSIONS  ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////  ////  ////

antlrcpp::Any TypeCheckVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->ident());
  TypesMgr::TypeId tID = getTypeDecor(ctx->ident());
  bool b = getIsLValueDecor(ctx->ident());

  if (ctx->expr()) {  //es un array
    visit(ctx->expr());
    TypesMgr::TypeId tIndex = getTypeDecor(ctx->expr());
    bool array_okay = not Types.isErrorTy(tID);

    if ((not Types.isErrorTy(tID)) and (not Types.isArrayTy(tID))){  //ID no array
      Errors.nonArrayInArrayAccess(ctx);
      tID = Types.createErrorTy(); //no acumula mas errores
      array_okay = false;
      b = false;  //no sabemos que es...
    }
    if ((not Types.isErrorTy(tIndex)) and (not Types.isIntegerTy(tIndex))){  //index no entero
      Errors.nonIntegerIndexInArrayAccess(ctx->expr());
      //array_okay = false; // SE PUEDE INFERIR EL TIPO DEL ARRAY
      //poner tID como errorType ??? NO, porque ya podemos inferir!
    }
    if (array_okay) {
      tID = Types.getArrayElemType(tID);
      //b = true; //NOSE
    }
  }
  putTypeDecor(ctx, tID);
  putIsLValueDecor(ctx, b);   //b correcto???
  DEBUG_EXIT();
  return 0;
}



////  ////  ////  ////  ////  ////  ////  ////
//// EXPRESSIONS  ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////  ////


antlrcpp::Any TypeCheckVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->expr());
  //necesario (abajo)
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());
  putTypeDecor(ctx, t);

  bool b = getIsLValueDecor(ctx->expr());
  putIsLValueDecor(ctx, b);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitArray_index(AslParser::Array_indexContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->ident());
  visit(ctx->expr());
  TypesMgr::TypeId tID = getTypeDecor(ctx->ident());
  TypesMgr::TypeId tIndex = getTypeDecor(ctx->expr());
  TypesMgr::TypeId tElem = Types.createErrorTy();
  
  if (not Types.isErrorTy(tID) ){
    if (not Types.isArrayTy(tID))
      Errors.nonArrayInArrayAccess(ctx);
    else tElem = Types.getArrayElemType(tID); 
  }

  if (not Types.isErrorTy(tIndex) and not Types.isIntegerTy(tIndex)){  //index no entero
    Errors.nonIntegerIndexInArrayAccess(ctx->expr());
  }

  putTypeDecor(ctx, tElem);
  putIsLValueDecor(ctx, true);  //se podria considerar lvalue, pero no creo nunca tenga ese uso...

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitFunction_call(AslParser::Function_callContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->ident());
  /*for (int i = 0; i < (ctx->expr()).size(); ++i) {    //aqui no!!! porque??? No propaga error!
          visit(ctx->expr(i));
  }*/

  TypesMgr::TypeId tID = getTypeDecor(ctx->ident());
  TypesMgr::TypeId t = Types.createErrorTy();

  if (not Types.isFunctionTy(tID) and not Types.isErrorTy(tID)) {   //no es funcion
    Errors.isNotCallable(ctx->ident());
  }
  else {
    t = Types.getFuncReturnType(tID); //return type

    if (Types.isVoidFunction(tID)){   //no puede ser void, tiene que devolver algo
      Errors.isNotFunction(ctx->ident());
      t = Types.createErrorTy();
    }
    if (Types.getNumOfParameters(tID) != (ctx->expr()).size() ){
      Errors.numberOfParameters(ctx->ident());
    }
    else {
      std::vector<TypesMgr::TypeId> lParamsTy = Types.getFuncParamsTypes(tID);
      for (size_t i = 0; i < lParamsTy.size(); ++i) {
        visit(ctx->expr(i));  //Aqui si
        TypesMgr::TypeId tPar = getTypeDecor(ctx->expr(i));
        //std::cout << Types.to_string(getTypeDecor(ctx->expr(i))) << std::endl;
        //std::cout << Types.to_string(lParamsTy[i]) << std::endl;

        if (not Types.equalTypes(lParamsTy[i], tPar)) {
          if (not Types.isErrorTy(tPar) and not (Types.isIntegerTy(tPar) and Types.isFloatTy(lParamsTy[i])))
            Errors.incompatibleParameter(ctx->expr(i), i+1, ctx);
        }
      }
    }
  }
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitUnary(AslParser::UnaryContext *ctx) {    //hace falta???
  DEBUG_ENTER();

  visit(ctx->expr());
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());

  if (ctx->NOT()) {
    if (not Types.isErrorTy(t) and not Types.isBooleanTy(t))
      Errors.incompatibleOperator(ctx->op); //dont know which
      //Errors.booleanRequired(ctx->expr());
    t = Types.createBooleanTy();
  }
  else {
    if (not Types.isErrorTy(t) and not Types.isIntegerTy(t) and not Types.isFloatTy(t))
      Errors.incompatibleOperator(ctx->op);
    if (Types.isFloatTy(t))
      t = Types.createFloatTy();
    else 
      t = Types.createIntegerTy();
  }

  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

          /* std::cout << Types.to_string(t1) << std::endl;
          std::cout << Types.to_string(t2) << std::endl; */

  TypesMgr::TypeId t = Types.createIntegerTy();

  if (ctx->MOD()) {   //MOD solo a enteros
     if (((not Types.isErrorTy(t1)) and (not Types.isIntegerTy(t1))) or 
        ((not Types.isErrorTy(t2)) and (not Types.isIntegerTy(t2))))
        Errors.incompatibleOperator(ctx->op);
  }
  else {
    ////  EXAM 2019 - Producte escalar
    if (Types.isArrayTy(t1) and Types.isArrayTy(t2)){   //prod. scalar

      if (Types.getArraySize(t1) != Types.getArraySize(t2))
        Errors.incompatibleOperator(ctx->op);

      TypesMgr::TypeId elem1 = Types.getArrayElemType(t1);
      TypesMgr::TypeId elem2 = Types.getArrayElemType(t2);

      if ((not Types.isErrorTy(elem1) and not Types.isIntegerTy(elem1)) or 
          (not Types.isErrorTy(elem2) and not Types.isIntegerTy(elem2))){
        if ((not Types.isErrorTy(elem1) and not Types.isFloatTy(elem1)) or 
            (not Types.isErrorTy(elem2) and not Types.isFloatTy(elem2))){
          Errors.incompatibleOperator(ctx->op);
        }
      }
      if (Types.isFloatTy(elem1) and Types.isFloatTy(elem2)) {
        t = Types.createFloatTy();
      }
    }
    ////  FI - EXAM 2019
    else if (((not Types.isErrorTy(t1)) and (not Types.isNumericTy(t1))) or 
            ((not Types.isErrorTy(t2)) and (not Types.isNumericTy(t2))))
      Errors.incompatibleOperator(ctx->op);
    if (Types.isFloatTy(t1) or Types.isFloatTy(t2)) t = Types.createFloatTy();
  }
    
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  std::string oper = ctx->op->getText();

        /* std::cout << Types.to_string(t1) << std::endl;
        std::cout << Types.to_string(t2) << std::endl; */


  if ((not Types.isErrorTy(t1)) and (not Types.isErrorTy(t2)) and
      (not Types.comparableTypes(t1, t2, oper)))    //check bool -> (==) y (!=), y float-int, o deberia...
    Errors.incompatibleOperator(ctx->op);

  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitLogical(AslParser::LogicalContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->expr(0));
  visit(ctx->expr(1));
  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));

  if (((not Types.isErrorTy(t1)) and (not Types.isBooleanTy(t1))) or
      ((not Types.isErrorTy(t2)) and (not Types.isBooleanTy(t2))))
    Errors.incompatibleOperator(ctx->op);

  TypesMgr::TypeId t = Types.createBooleanTy();
  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();

  TypesMgr::TypeId t = Types.createErrorTy();

	if      (ctx->INTVAL())   t = Types.createIntegerTy();
	else if (ctx->FLOATVAL()) t = Types.createFloatTy();
	else if (ctx->BOOLVAL())  t = Types.createBooleanTy();
	else if (ctx->CHARVAL())  t = Types.createCharacterTy();

	putTypeDecor(ctx, t);
	putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {  //NOTHING
  DEBUG_ENTER();

  visit(ctx->ident());
  TypesMgr::TypeId t1 = getTypeDecor(ctx->ident());

  putTypeDecor(ctx, t1);
  bool b = getIsLValueDecor(ctx->ident());
  putIsLValueDecor(ctx, b);

  DEBUG_EXIT();
  return 0;
}



////  ////  ////  ////  ////  ////  ////
//// IDENT  ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////

antlrcpp::Any TypeCheckVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();

  std::string ident = ctx->getText();
  if (Symbols.findInStack(ident) == -1) {   //ID no esta declarado
    Errors.undeclaredIdent(ctx->ID());
    TypesMgr::TypeId te = Types.createErrorTy();
    putTypeDecor(ctx, te);
    putIsLValueDecor(ctx, true);  //...pero si puede ser l-value
  }
  else {
    TypesMgr::TypeId t1 = Symbols.getType(ident);
    putTypeDecor(ctx, t1);
    if (Symbols.isFunctionClass(ident))   //si ID es funcion no es l-value
      putIsLValueDecor(ctx, false);
    else
      putIsLValueDecor(ctx, true);
  }
  DEBUG_EXIT();
  return 0;
}


////  ////  ////  ////
//// EXAM 2020    ////
////  ////  ////  ////

antlrcpp::Any TypeCheckVisitor::visitMax(AslParser::MaxContext *ctx) {
  DEBUG_ENTER();

  TypesMgr::TypeId tFinal = Types.createErrorTy();
  bool isFloat = false;
  bool isChar = false;
  bool isInt = false;
  bool isError = false;
  for (size_t i = 0; i < (ctx->expr()).size(); ++i) {  //visitamo elementos
    visit(ctx->expr(i));
    TypesMgr::TypeId elem = getTypeDecor(ctx->expr(i));

    if ((not Types.isErrorTy(elem) and not Types.isNumericTy(elem)) and 
    not Types.isCharacterTy(elem)){
      //Errors.incompatibleMaxArguments(ctx);
    }
    if (Types.isCharacterTy(elem)) {
      if (isFloat or isInt) {
        //Errors.incompatibleMaxArguments(ctx);
        isError = true;
      }
      else isChar = true;
    }
    if (Types.isNumericTy(elem)) {
      if (isChar){
        //Errors.incompatibleMaxArguments(ctx);
        isError = true;
      }
      else if (Types.isIntegerTy(elem)) isInt = true;
      else isFloat = true; //!!!
    }
  }

  if (isChar) tFinal = Types.createCharacterTy();
  else if (isInt) tFinal = Types.createIntegerTy();
  if (isFloat) tFinal = Types.createFloatTy();

  if (isError) tFinal = Types.createErrorTy();
  
  if ((ctx->expr()).size() < 2) {
    //Errors.numberOfMaxArguments(ctx);
  }

  putTypeDecor(ctx, tFinal);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


antlrcpp::Any TypeCheckVisitor::visitForRange(AslParser::ForRangeContext *ctx) {
  DEBUG_ENTER();

  if ((ctx->expr()).size() < 2 or (ctx->expr()).size() > 4) {
    //Errors.numberOfRangeExpressions(ctx);
  }

  visit(ctx->expr(0));
  TypesMgr::TypeId ct = getTypeDecor(ctx->expr(0));
  if (not Types.isErrorTy(ct) and not Types.isIntegerTy(ct)) {
    //Errors.forRequireIntegerVar(ctx->expr(0));
  }
  

  for (size_t i = 1; i < (ctx->expr()).size(); ++i) {  //visitamo elementos
    visit(ctx->expr(i));
    TypesMgr::TypeId tp = getTypeDecor(ctx->expr(i));
    if (not Types.isErrorTy(tp) and not Types.isIntegerTy(tp)) {
      //Errors.forRequireIntegerExpr(ctx->expr(i));
    }
  }
  
  visit(ctx->statements());

  

  TypesMgr::TypeId t = getTypeDecor(ctx->expr(0));

  putTypeDecor(ctx, t);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}


////  ////  ////  ////
//// EXAM 2019    ////
////  ////  ////  ////

antlrcpp::Any TypeCheckVisitor::visitArrayMax(AslParser::ArrayMaxContext *ctx) {
  DEBUG_ENTER();

  visit(ctx->expr());
  TypesMgr::TypeId t = getTypeDecor(ctx->expr());

  TypesMgr::TypeId elem = Types.createErrorTy();

  if (not Types.isErrorTy(t) and not Types.isArrayTy(t))  //no es array
    Errors.incompatibleOperator(ctx->op);

  else if (not Types.isErrorTy(t)) {   //es array
    elem = Types.getArrayElemType(t);
    if (Types.isBooleanTy(elem))   //es array pero de bool
      Errors.incompatibleOperator(ctx->op);
  }

  putTypeDecor(ctx, elem);
  putIsLValueDecor(ctx, false);

  DEBUG_EXIT();
  return 0;
}




// antlrcpp::Any TypeCheckVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any TypeCheckVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }

// antlrcpp::Any TypeCheckVisitor::visitType(AslParser::TypeContext *ctx) {
//   DEBUG_ENTER();
//   antlrcpp::Any r = visitChildren(ctx);
//   DEBUG_EXIT();
//   return r;
// }



// Getters for the necessary tree node atributes:
//   Scope, Type ans IsLValue
SymTable::ScopeId TypeCheckVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId TypeCheckVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getType(ctx);
}
bool TypeCheckVisitor::getIsLValueDecor(antlr4::ParserRuleContext *ctx) {
  return Decorations.getIsLValue(ctx);
}

// Setters for the necessary tree node attributes:
//   Scope, Type ans IsLValue
void TypeCheckVisitor::putScopeDecor(antlr4::ParserRuleContext *ctx, SymTable::ScopeId s) {
  Decorations.putScope(ctx, s);
}
void TypeCheckVisitor::putTypeDecor(antlr4::ParserRuleContext *ctx, TypesMgr::TypeId t) {
  Decorations.putType(ctx, t);
}
void TypeCheckVisitor::putIsLValueDecor(antlr4::ParserRuleContext *ctx, bool b) {
  Decorations.putIsLValue(ctx, b);
}
