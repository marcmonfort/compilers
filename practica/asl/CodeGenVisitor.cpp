//////////////////////////////////////////////////////////////////////
//
//    CodeGenVisitor - Walk the parser tree to do
//                     the generation of code
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

#include "CodeGenVisitor.h"

#include "antlr4-runtime.h"

#include "../common/TypesMgr.h"
#include "../common/SymTable.h"
#include "../common/TreeDecoration.h"
#include "../common/code.h"

#include <string>
#include <cstddef>    // std::size_t

// uncomment the following line to enable debugging messages with DEBUG*
// #define DEBUG_BUILD
#include "../common/debug.h"

// using namespace std;


// Constructor
CodeGenVisitor::CodeGenVisitor(TypesMgr       & Types,
                               SymTable       & Symbols,
                               TreeDecoration & Decorations) :
  Types{Types},
  Symbols{Symbols},
  Decorations{Decorations} {
}

// Methods to visit each kind of node:
//
antlrcpp::Any CodeGenVisitor::visitProgram(AslParser::ProgramContext *ctx) {
  DEBUG_ENTER();
  code my_code;
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  for (auto ctxFunc : ctx->function()) { 
    subroutine subr = visit(ctxFunc);
    my_code.add_subroutine(subr);
  }
  Symbols.popScope();
  DEBUG_EXIT();
  return my_code;
}


antlrcpp::Any CodeGenVisitor::visitFunction(AslParser::FunctionContext *ctx) {
  DEBUG_ENTER();
  SymTable::ScopeId sc = getScopeDecor(ctx);
  Symbols.pushThisScope(sc);
  subroutine subr(ctx->ID()->getText());
  codeCounters.reset();
  
  if (ctx->basic_type()) //returns a value
    subr.add_param("_result");

  std::vector<std::string> && lparam = visit(ctx->parameters());
  for (auto & oneparam : lparam) {
    subr.add_param(oneparam);
  }
  std::vector<var> && lvars = visit(ctx->declarations());
  for (auto & onevar : lvars) {
    subr.add_var(onevar);
  }
  instructionList && code = visit(ctx->statements());
  code = code || instruction(instruction::RETURN());
  subr.set_instructions(code);
  Symbols.popScope();
  DEBUG_EXIT();
  return subr;
}


antlrcpp::Any CodeGenVisitor::visitParameters(AslParser::ParametersContext *ctx) {
  DEBUG_ENTER();
  std::vector<std::string> lparam;
  for (auto & param : ctx->ID()){
    lparam.push_back(param->getText());
  }
  DEBUG_EXIT();
  return lparam;
}


antlrcpp::Any CodeGenVisitor::visitDeclarations(AslParser::DeclarationsContext *ctx) {
  DEBUG_ENTER();
  std::vector<var> lvars;
  for (auto & varDeclCtx : ctx->variable_decl()) {
    std::vector<var> aux = visit(varDeclCtx);
    lvars.insert(lvars.end(), aux.begin(), aux.end());
    //lvars.push_back(onevar);
  }
  DEBUG_EXIT();
  return lvars;
}


antlrcpp::Any CodeGenVisitor::visitVariable_decl(AslParser::Variable_declContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId   t1 = getTypeDecor(ctx->type());
  std::size_t      size = Types.getSizeOfType(t1);
  std::vector<var> lvars;

  for (unsigned int i = 0; i < ctx->ID().size(); i++) { //better auto
    lvars.push_back(var{ctx->ID(i)->getText(), size});
  }
  DEBUG_EXIT();
  return lvars;
}



////  ////  ////  ////  ////  ////  ////  ////
//// STATEMENTS   ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////  ////


antlrcpp::Any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  for (auto & stCtx : ctx->statement()) { //added & ???
    instructionList && codeS = visit(stCtx);
    code = code || codeS;
  }
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE1 = visit(ctx->left_expr());
  std::string           addr1 = codAtsE1.addr;
  std::string           offs1 = codAtsE1.offs;
  instructionList &     code1 = codAtsE1.code;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());

  CodeAttribs     && codAtsE2 = visit(ctx->expr());
  std::string           addr2 = codAtsE2.addr;
  std::string           offs2 = codAtsE2.offs;
  instructionList &     code2 = codAtsE2.code;
  TypesMgr::TypeId tid2 = getTypeDecor(ctx->expr());

  instructionList && code = code1 || code2;;

  if (Types.isArrayTy(tid1) and Types.isArrayTy(tid2)){ //two arrays

    if (not Symbols.isLocalVarClass(addr1)) { 
      std::string tempL1 = "%"+codeCounters.newTEMP();
      code = code || instruction::LOAD(tempL1, addr1);
      addr1 = tempL1;
    }
    if (not Symbols.isLocalVarClass(addr2)) { 
      std::string tempL2 = "%"+codeCounters.newTEMP();
      code = code || instruction::LOAD(tempL2, addr2);
      addr2 = tempL2;
    }

    std::string labelWhile = "while"+codeCounters.newLabelWHILE();
    std::string labelEndWhile = "end"+labelWhile;

    std::string numElems = std::to_string(Types.getArraySize(tid1)-1);
    std::string tempOffs = "%"+codeCounters.newTEMP();
    std::string tempElem = "%"+codeCounters.newTEMP();
    std::string tempCond = "%"+codeCounters.newTEMP();
    std::string justZero = "%"+codeCounters.newTEMP();
    std::string justOne  = "%"+codeCounters.newTEMP();

    code = code || instruction::ILOAD(tempOffs, numElems) ||
                   //instruction::WRITEI(tempOffs) ||
                   instruction::ILOAD(justOne,  "1") ||
                   instruction::ILOAD(justZero, "0") ||

                   instruction::LABEL(labelWhile) ||
                   instruction::LE(tempCond, justZero, tempOffs) ||
                   instruction::FJUMP(tempCond, labelEndWhile) ||

                   instruction::LOADX(tempElem, addr2, tempOffs) ||
                   instruction::XLOAD(addr1, tempOffs, tempElem) ||
                   instruction::SUB(tempOffs, tempOffs, justOne) ||
                   
                   instruction::UJUMP(labelWhile) ||
                   instruction::LABEL(labelEndWhile);
    //code = code || instruction::LOAD(addr1, addr2); //no need!
  }

  else {
    if (Types.isFloatTy(tid1) and Types.isIntegerTy(tid2)){  //cast to float
      std::string tempFloat = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(tempFloat, addr2);
      addr2 = tempFloat;
    }
    if (ctx->left_expr()->expr()){  //array element
      code = code || instruction::XLOAD(addr1, offs1, addr2);
    }
    else
      code = code || instruction::LOAD(addr1, addr2);
  }
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsExpr = visit(ctx->expr());
  std::string          addrExpr = codAtsExpr.addr;
  instructionList &    codeExpr = codAtsExpr.code;
  instructionList &&   codeThen = visit(ctx->statements(0));
  
  std::string label = codeCounters.newLabelIF();
  std::string labelEndIf = "endif"+label;

  if (ctx->ELSE()) {  // IF ELSE
    instructionList &&   codeElse = visit(ctx->statements(1));
    std::string labelElse = "else"+label;

    code = codeExpr || instruction::FJUMP(addrExpr, labelElse) || 
           codeThen || instruction::UJUMP(labelEndIf) || 
           instruction::LABEL(labelElse) || codeElse || 
           instruction::LABEL(labelEndIf);
  }
  else {  // IF
    code = codeExpr || instruction::FJUMP(addrExpr, labelEndIf) ||
           codeThen || instruction::LABEL(labelEndIf);
  }
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsExpr = visit(ctx->expr());
  std::string          addrExpr = codAtsExpr.addr;
  instructionList &    codeExpr = codAtsExpr.code;
  instructionList &&     codeDo = visit(ctx->statements());

  std::string labelWhile = "while"+codeCounters.newLabelWHILE();
  std::string labelEndWhile = "end"+labelWhile;

  code = instruction::LABEL(labelWhile) || codeExpr ||
         instruction::FJUMP(addrExpr, labelEndWhile) || codeDo ||
         instruction::UJUMP(labelWhile) || instruction::LABEL(labelEndWhile);
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();
  TypesMgr::TypeId  tId = getTypeDecor(ctx->ident());
  auto typesParams = Types.getFuncParamsTypes(tId);

  instructionList code;
  instructionList paramsPush;
  instructionList paramsPop;

  for (size_t i = 0; i < (ctx->expr()).size(); ++i){
    CodeAttribs     && codAtParam = visit(ctx->expr(i));
    std::string         addrParam = codAtParam.addr;
    instructionList &   codeParam = codAtParam.code;
    TypesMgr::TypeId       tParam = getTypeDecor(ctx->expr(i));
    
    code = code || codeParam;
    std::string temp = addrParam;

    if (Types.isFloatTy(typesParams[i]) and Types.isIntegerTy(tParam)){  //cast to float
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp,addrParam);
    }
    else if (Types.isArrayTy(tParam)){  //array by reference
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(temp,addrParam);
    }
    //add it after, in case or more CALL's
    paramsPush = paramsPush || instruction::PUSH(temp); 
    paramsPop = paramsPop || instruction::POP(); 
  }

  if (not Types.isVoidFunction(tId)) {  // if there is return...
    paramsPush = paramsPush || instruction::PUSH();
    paramsPop = paramsPop || instruction::POP();
  }

  code = code || paramsPush;

  std::string name = ctx->ident()->getText(); //hacer visit???
  code = code || instruction::CALL(name);

  code = code || paramsPop;
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  if (ctx->expr()) {
    CodeAttribs     && codAtExpr = visit(ctx->expr());
    std::string         addrExpr = codAtExpr.addr;
    instructionList &   codeExpr = codAtExpr.code;

    code = codeExpr || instruction::LOAD("_result",addrExpr) || instruction::RETURN();
  }
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsExpr = visit(ctx->left_expr());
  std::string          addrExpr = codAtsExpr.addr;
  std::string          offsExpr = codAtsExpr.offs;
  instructionList &    codeExpr = codAtsExpr.code;
  TypesMgr::TypeId      tidExpr = getTypeDecor(ctx->left_expr());

  instructionList &        code = codeExpr;

  bool && isArrayElem = ctx->left_expr()->expr();
  std::string temp = isArrayElem ? "%"+codeCounters.newTEMP() : addrExpr;

  if (Types.isFloatTy(tidExpr))          code = code || instruction::READF(temp);
  else if (Types.isCharacterTy(tidExpr)) code = code || instruction::READC(temp);
  else /*integer and bool*/              code = code || instruction::READI(temp);

  if (isArrayElem){
    code = code || instruction::XLOAD(addrExpr, offsExpr, temp);
  }
  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  // std::string         offs1 = codAt1.offs; // para que ??? array_index devuelve elemento.
  instructionList &   code1 = codAt1.code;
  instructionList &    code = code1;

  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());

  if (Types.isFloatTy(tid1))          code = code || instruction::WRITEF(addr1);
  else if (Types.isCharacterTy(tid1)) code = code || instruction::WRITEC(addr1);
  else                                code = code || instruction::WRITEI(addr1);

  DEBUG_EXIT();
  return code;
}


antlrcpp::Any CodeGenVisitor::visitWriteString(AslParser::WriteStringContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string s = ctx->STRING()->getText();
  std::string temp = "%"+codeCounters.newTEMP();
  int i = 1;
  while (i < int(s.size())-1) {
    if (s[i] != '\\') {
      code = code || instruction::CHLOAD(temp, s.substr(i,1)) ||
	                   instruction::WRITEC(temp);
      i += 1;
    }
    else {
      assert(i < int(s.size())-2);
      if (s[i+1] == 'n') {
        code = code || instruction::WRITELN();
        i += 2;
      }
      else if (s[i+1] == 't' or s[i+1] == '"' or s[i+1] == '\\') {
        code = code || instruction::CHLOAD(temp, s.substr(i,2)) ||
	                     instruction::WRITEC(temp);
        i += 2;
      }
      else {
        code = code || instruction::CHLOAD(temp, s.substr(i,1)) ||
	                     instruction::WRITEC(temp);
        i += 1;
      }
    }
  }
  DEBUG_EXIT();
  return code;
}



////  ////  ////  ////  ////  ////  ////  ////  ////
////  LEFT EXPRESSIONS  ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////  ////  ////

antlrcpp::Any CodeGenVisitor::visitLeft_expr(AslParser::Left_exprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtID = visit(ctx->ident());
  std::string         addrID = codAtID.addr;
  instructionList &   codeID = codAtID.code;
  instructionList &   code = codeID;

  std::string offs = "";
  if (ctx->expr()) {
    CodeAttribs     && codAtIndex = visit(ctx->expr());
    offs                          = codAtIndex.addr;
    instructionList &   codeIndex = codAtIndex.code;

    code = code || codeIndex;

    if (Symbols.isParameterClass(addrID)) { // por referencia
      std::string temp = "%"+codeCounters.newTEMP();
      code = code || instruction::LOAD(temp, addrID);
      addrID = temp;
    }
  }

  CodeAttribs codAts(addrID, offs, code);
  DEBUG_EXIT();
  return codAts;
}



////  ////  ////  ////  ////  ////  ////  ////
//// EXPRESSIONS  ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////  ////


antlrcpp::Any CodeGenVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->expr());
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitArray_index(AslParser::Array_indexContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtID = visit(ctx->ident());
  std::string         addrID = codAtID.addr;
  instructionList &   codeID = codAtID.code;
  CodeAttribs     && codAtIndex = visit(ctx->expr());
  std::string         addrIndex = codAtIndex.addr;
  instructionList &   codeIndex = codAtIndex.code;
  //consideramos siempre offset tamaño 1 (basic_type)

  instructionList &&   code = codeID || codeIndex;
  std::string temp = "%"+codeCounters.newTEMP();


  if (Symbols.isLocalVarClass(addrID))
    code = code || instruction::LOADX(temp, addrID, addrIndex);
    
  else { //isParameterClass
    std::string temp2 = "%"+codeCounters.newTEMP();
    code = code || instruction::LOAD(temp2, addrID) ||
                   instruction::LOADX(temp, temp2, addrIndex);
  }

  CodeAttribs codAts(temp, "", code);  
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitFunction_call(AslParser::Function_callContext *ctx) {
  DEBUG_ENTER();
  auto typesParams = Types.getFuncParamsTypes(getTypeDecor(ctx->ident()));
  instructionList code;
  instructionList paramsPush;
  instructionList paramsPop;

  for (size_t i = 0; i < (ctx->expr()).size(); ++i){
    CodeAttribs     && codAtParam = visit(ctx->expr(i));
    std::string         addrParam = codAtParam.addr;
    instructionList &   codeParam = codAtParam.code;
    
    code = code || codeParam;
    std::string tempParam = addrParam;
    TypesMgr::TypeId  tParam = getTypeDecor(ctx->expr(i));

    if (Types.isFloatTy(typesParams[i]) and Types.isIntegerTy(tParam)){  //cast to float
      tempParam = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(tempParam, addrParam);
    }
    else if (Types.isArrayTy(tParam)){  //array by reference
      tempParam = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(tempParam, addrParam);
    }
    //added after, could be more CALL's
    paramsPush = paramsPush || instruction::PUSH(tempParam); 
    paramsPop = paramsPop || instruction::POP();
  }

  code = code || instruction::PUSH() || paramsPush;

  // std::string name = ctx->ident()->ID()->getSymbol()->getText();
  std::string name = ctx->ident()->getText(); //hacer visit???
  code = code || instruction::CALL(name);

  std::string temp = "%"+codeCounters.newTEMP();  // get the return value
  code = code || paramsPop || instruction::POP(temp);

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitUnary(AslParser::UnaryContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  TypesMgr::TypeId  t = getTypeDecor(ctx->expr());
  
  instructionList &    code = code1;
  std::string temp = "%"+codeCounters.newTEMP();

  if (ctx->NOT()) code = code || instruction::NOT(temp, addr1);
  else if (ctx->SUB()) code = code || (Types.isFloatTy(t) ? instruction::FNEG(temp, addr1)
                                                          : instruction::NEG(temp, addr1));
                                                         
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitArithmetic(AslParser::ArithmeticContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;

  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  TypesMgr::TypeId  t = getTypeDecor(ctx);

  std::string temp = "%"+codeCounters.newTEMP();

  if (Types.isIntegerTy(t)){
    if (ctx->MUL())       code = code || instruction::MUL(temp, addr1, addr2);
    else if (ctx->DIV())  code = code || instruction::DIV(temp, addr1, addr2);
    else if (ctx->PLUS()) code = code || instruction::ADD(temp, addr1, addr2);
    else if (ctx->SUB())  code = code || instruction::SUB(temp, addr1, addr2);
    else /*MOD*/          code = code || instruction::DIV(temp, addr1, addr2)
                                      || instruction::MUL(temp, temp, addr2)
                                      || instruction::SUB(temp, addr1, temp);
  }
  else { //FLOAT's
    std::string addrF1 = addr1;
    std::string addrF2 = addr2;

    if (Types.isIntegerTy(t1)) {
      addrF1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF1, addr1);
    }
    else if (Types.isIntegerTy(t2)) {
      addrF2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF2, addr2);
    }

    if (ctx->MUL())       code = code || instruction::FMUL(temp, addrF1, addrF2);
    else if (ctx->DIV())  code = code || instruction::FDIV(temp, addrF1, addrF2);
    else if (ctx->PLUS()) code = code || instruction::FADD(temp, addrF1, addrF2);
    else /*SUB*/          code = code || instruction::FSUB(temp, addrF1, addrF2);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitRelational(AslParser::RelationalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;

  TypesMgr::TypeId t1 = getTypeDecor(ctx->expr(0));
  TypesMgr::TypeId t2 = getTypeDecor(ctx->expr(1));
  //TypesMgr::TypeId  t = getTypeDecor(ctx); //always bool...

  std::string temp = "%"+codeCounters.newTEMP();

  if (not Types.isFloatTy(t1) and not Types.isFloatTy(t1)){
    if (ctx->EQ())        code = code || instruction::EQ(temp, addr1, addr2);
    else if (ctx->NEQ())  code = code || instruction::EQ(temp, addr1, addr2) ||
                                         instruction::NOT(temp, temp);
    else if (ctx->LT())   code = code || instruction::LT(temp, addr1, addr2);
    else if (ctx->LTE())  code = code || instruction::LE(temp, addr1, addr2);
    else if (ctx->GT())   code = code || instruction::LE(temp, addr1, addr2) ||
                                         instruction::NOT(temp, temp);
    else                  code = code || instruction::LT(temp, addr1, addr2) ||
                                         instruction::NOT(temp, temp);
  }
  else { //FLOAT's
    std::string addrF1 = addr1;
    std::string addrF2 = addr2;
    if (Types.isIntegerTy(t1)) {
      addrF1 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF1, addr1);
    }
    else if (Types.isIntegerTy(t2)) {
      addrF2 = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(addrF2, addr2);
    }
    
    if (ctx->EQ())        code = code || instruction::FEQ(temp, addrF1, addrF2);
    else if (ctx->NEQ())  code = code || instruction::FEQ(temp, addrF1, addrF2) ||
                                         instruction::NOT(temp, temp);
    else if (ctx->LT())   code = code || instruction::FLT(temp, addrF1, addrF2);
    else if (ctx->LTE())  code = code || instruction::FLE(temp, addrF1, addrF2);
    else if (ctx->GT())   code = code || instruction::FLE(temp, addrF1, addrF2) ||
                                         instruction::NOT(temp, temp);
    else /*GTE*/          code = code || instruction::FLT(temp, addrF1, addrF2) ||
                                         instruction::NOT(temp, temp);
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitLogical(AslParser::LogicalContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr(0));
  std::string         addr1 = codAt1.addr;
  instructionList &   code1 = codAt1.code;
  CodeAttribs     && codAt2 = visit(ctx->expr(1));
  std::string         addr2 = codAt2.addr;
  instructionList &   code2 = codAt2.code;
  instructionList &&   code = code1 || code2;

  std::string temp = "%"+codeCounters.newTEMP();

  if (ctx->AND()) code = code || instruction::AND(temp, addr1, addr2);
  else /*OR*/     code = code || instruction::OR(temp, addr1, addr2);

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  if (ctx->INTVAL())        code = instruction::ILOAD(temp, ctx->getText());
  else if (ctx->FLOATVAL()) code = instruction::FLOAD(temp, ctx->getText());
  else if (ctx->BOOLVAL())  code = instruction::LOAD(temp, (ctx->getText()=="true" ? "1":"0" ));
  else {  // character
                            std::string token = ctx->getText();
                            code = instruction::CHLOAD(temp, token.substr(1, token.size()-2));
  }
  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}


antlrcpp::Any CodeGenVisitor::visitExprIdent(AslParser::ExprIdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->ident());
  DEBUG_EXIT();
  return codAts;
}



////  ////  ////  ////  ////  ////  ////
//// IDENT  ////  ////  ////  ////  ////
////  ////  ////  ////  ////  ////  ////

antlrcpp::Any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
  DEBUG_EXIT();
  return codAts;
}


////  ////  ////  ////
//// EXAM 2020    ////
////  ////  ////  ////

antlrcpp::Any CodeGenVisitor::visitMax(AslParser::MaxContext *ctx) {
  DEBUG_ENTER();

  CodeAttribs     && codAtElem0 = visit(ctx->expr(0));
  std::string         addrElem0 = codAtElem0.addr;
  instructionList &   codeElem0 = codAtElem0.code;
  TypesMgr::TypeId       tElem0 = getTypeDecor(ctx->expr(0));

  instructionList & code = codeElem0;

  bool someFloat = Types.isFloatTy(tElem0);
  bool alreadyFloat = false;

  std::string maxElem  = "%"+codeCounters.newTEMP();
  //asignamos a maxElem el primer elemento
  if (someFloat){
    code = code || instruction::FLOAD(maxElem, addrElem0);
    alreadyFloat = true;
  }
  else {
    code = code || instruction::LOAD(maxElem, addrElem0);
  }


  for (size_t i = 1; i < (ctx->expr()).size(); ++i){
    CodeAttribs     && codAtElem = visit(ctx->expr(i));
    std::string         addrElem = codAtElem.addr;
    instructionList &   codeElem = codAtElem.code;
    TypesMgr::TypeId       tElem = getTypeDecor(ctx->expr(i));
    
    code = code || codeElem;

    std::string tempCond  = "%"+codeCounters.newTEMP();
    std::string labelElse = "else"+codeCounters.newLabelIF();

    if (Types.isFloatTy(tElem) and not alreadyFloat) {
      someFloat = true;
      code = code || instruction::FLOAT(maxElem,maxElem);
      alreadyFloat = true;
    }


    if (someFloat){  //cast to float
      if (Types.isIntegerTy(tElem)){
        std::string tempElem = "%"+codeCounters.newTEMP();
        code = code || instruction::FLOAT(tempElem, addrElem);
        addrElem = tempElem;
      }

      code = code || instruction::FLT(tempCond, maxElem, addrElem) ||
                     instruction::FJUMP(tempCond, labelElse) ||
                     instruction::FLOAD(maxElem, addrElem) || // same as LOAD
                     instruction::LABEL(labelElse);
    }
    else {
      code = code || instruction::LT(tempCond, maxElem, addrElem) ||
                   instruction::FJUMP(tempCond, labelElse) ||
                   instruction::LOAD(maxElem, addrElem) || // same as LOAD
                   instruction::LABEL(labelElse);
    }

  }
  CodeAttribs codAts(maxElem, "", code);
  DEBUG_EXIT();
  return codAts;

}

antlrcpp::Any CodeGenVisitor::visitForRange(AslParser::ForRangeContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtControl = visit(ctx->expr(0));
  std::string         addrControl = codAtControl.addr;
  instructionList &   codeControl = codAtControl.code;
  //TypesMgr::TypeId       tControl = getTypeDecor(ctx->expr(0));

  instructionList & code = codeControl;
  instructionList &&   codeStmt = visit(ctx->statements());

  if (ctx->expr().size() == 2) {
    CodeAttribs     && codAtElem = visit(ctx->expr(1));
    std::string         addrElem = codAtElem.addr;
    instructionList &   codeElem = codAtElem.code;
    //TypesMgr::TypeId       tElem = getTypeDecor(ctx->expr(i));

    code = code || codeElem;


    std::string labelWhile = "while"+codeCounters.newLabelWHILE();
    std::string labelEndWhile = "end"+labelWhile;

    std::string tempCond   = "%"+codeCounters.newTEMP();
    std::string tempIndex  = "%"+codeCounters.newTEMP();
    std::string justOne    = "%"+codeCounters.newTEMP();


    code = code || instruction::ILOAD(tempIndex, "0") ||
                  instruction::ILOAD(justOne, "1") ||

                  instruction::LABEL(labelWhile) ||
                  instruction::LT(tempCond, tempIndex, addrElem) ||
                  instruction::FJUMP(tempCond, labelEndWhile) ||

                  instruction::LOAD(addrControl, tempIndex) ||
                  codeStmt ||
                  instruction::ADD(tempIndex, tempIndex, justOne) ||
                  instruction::UJUMP(labelWhile) ||

                  instruction::LABEL(labelEndWhile);

  }
  else { // 2 o 3 parametres
    CodeAttribs     && codAtLow = visit(ctx->expr(1));
    std::string         addrLow = codAtLow.addr;
    instructionList &   codeLow = codAtLow.code;

    CodeAttribs     && codAtUp = visit(ctx->expr(2));
    std::string         addrUp = codAtUp.addr;
    instructionList &   codeUp = codAtUp.code;

    code = code || codeLow || codeUp;

    std::string labelWhile = "while"+codeCounters.newLabelWHILE();
    std::string labelEndWhile = "end"+labelWhile;

    std::string tempCond   = "%"+codeCounters.newTEMP();
    std::string tempIndex  = "%"+codeCounters.newTEMP();
    //std::string justOne    = "%"+codeCounters.newTEMP();
    std::string tempIncrem = "%"+codeCounters.newTEMP();


    if (ctx->expr(3)) {
      CodeAttribs     && codAtIncrem = visit(ctx->expr(3));
      std::string         addrIncrem = codAtIncrem.addr;
      instructionList &   codeIncrem = codAtIncrem.code;

      code = code || codeIncrem || 
                     instruction::LOAD(tempIncrem, addrIncrem);
    }
    else {
      code = code || instruction::ILOAD(tempIncrem, "1");
    }


    code = code || instruction::ILOAD(tempIndex, addrLow) ||
                  //instruction::ILOAD(tempIncrem, "1") || //same as LOAD?

                  instruction::LABEL(labelWhile) ||
                  instruction::LT(tempCond, tempIndex, addrUp) ||
                  instruction::FJUMP(tempCond, labelEndWhile) ||

                  instruction::LOAD(addrControl, tempIndex) ||
                  codeStmt ||
                  instruction::ADD(tempIndex, tempIndex, tempIncrem) ||
                  instruction::UJUMP(labelWhile) ||

                  instruction::LABEL(labelEndWhile);
  }
  DEBUG_EXIT();
  return code;
}


////  ////  ////  ////
//// EXAM 2019    ////
////  ////  ////  ////

antlrcpp::Any CodeGenVisitor::visitArrayMax(AslParser::ArrayMaxContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE1 = visit(ctx->expr());
  std::string           addr1 = codAtsE1.addr;
  std::string           offs1 = codAtsE1.offs;
  instructionList &     code1 = codAtsE1.code;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->expr());

  instructionList & code = code1;

  if (not Symbols.isLocalVarClass(addr1)) { 
    std::string tempL1 = "%"+codeCounters.newTEMP();
    code = code || instruction::LOAD(tempL1, addr1);
    addr1 = tempL1;
  }

  std::string labelWhile = "while"+codeCounters.newLabelWHILE();
  std::string labelEndWhile = "end"+labelWhile;
  std::string labelElse = "else"+codeCounters.newLabelIF();

  std::string numElems = std::to_string(Types.getArraySize(tid1)-1);
  std::string tempOffs = "%"+codeCounters.newTEMP();
  std::string tempElem = "%"+codeCounters.newTEMP();
  std::string tempCond = "%"+codeCounters.newTEMP();
  std::string justZero = "%"+codeCounters.newTEMP();
  std::string justOne  = "%"+codeCounters.newTEMP();

  std::string maxElem  = "%"+codeCounters.newTEMP();


  if (Types.isFloatTy(Types.getArrayElemType(tid1))){
    code = code || 
                  instruction::ILOAD(tempOffs, numElems) ||
                  //instruction::WRITEI(tempOffs) ||
                  instruction::ILOAD(justOne,  "1") ||
                  instruction::ILOAD(justZero, "0") ||

                  instruction::LOADX(tempElem, addr1, justZero) ||
                  instruction::LOAD(maxElem, tempElem) ||
                  //instruction::FLOAD(maxElem, "1.0") ||

                  instruction::LABEL(labelWhile) ||
                  instruction::LE(tempCond, justZero, tempOffs) || // 
                  instruction::FJUMP(tempCond, labelEndWhile) ||    // si ya hemos reccorrido todo el array

                  instruction::LOADX(tempElem, addr1, tempOffs) ||
                  instruction::FLT(tempCond, maxElem, tempElem) ||
                  instruction::FJUMP(tempCond, labelElse) ||
                  instruction::FLOAD(maxElem, tempElem) || // same as LOAD
                  instruction::LABEL(labelElse) ||
                  instruction::SUB(tempOffs, tempOffs, justOne) ||
                  
                  instruction::UJUMP(labelWhile) ||
                  instruction::LABEL(labelEndWhile);
  }
  else {
    code = code || 
                  instruction::ILOAD(tempOffs, numElems) ||
                  //instruction::WRITEI(tempOffs) ||
                  instruction::ILOAD(justOne,  "1") ||
                  instruction::ILOAD(justZero, "0") ||

                  instruction::LOADX(tempElem, addr1, justZero) ||
                  instruction::LOAD(maxElem, tempElem) ||

                  instruction::LABEL(labelWhile) ||
                  instruction::LE(tempCond, justZero, tempOffs) || // 
                  instruction::FJUMP(tempCond, labelEndWhile) ||    // si ya hemos reccorrido todo el array

                  instruction::LOADX(tempElem, addr1, tempOffs) ||
                  instruction::LT(tempCond, maxElem, tempElem) ||
                  instruction::FJUMP(tempCond, labelElse) ||
                  instruction::LOAD(maxElem, tempElem) ||
                  instruction::LABEL(labelElse) ||
                  instruction::SUB(tempOffs, tempOffs, justOne) ||
                  
                  instruction::UJUMP(labelWhile) ||
                  instruction::LABEL(labelEndWhile);
  }

  CodeAttribs codAts(maxElem, "", code);
  DEBUG_EXIT();
  return codAts;

}



////  ////  ////  ////  ////  
////    COMMONS   ////  //// 
////  ////  ////  ////  //// 


// Getters for the necessary tree node atributes:
//   Scope and Type
SymTable::ScopeId CodeGenVisitor::getScopeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getScope(ctx);
}
TypesMgr::TypeId CodeGenVisitor::getTypeDecor(antlr4::ParserRuleContext *ctx) const {
  return Decorations.getType(ctx);
}


// Constructors of the class CodeAttribs:
//
CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
					 const std::string & offs,
					 instructionList & code) :
  addr{addr}, offs{offs}, code{code} {
}

CodeGenVisitor::CodeAttribs::CodeAttribs(const std::string & addr,
					 const std::string & offs,
					 instructionList && code) :
  addr{addr}, offs{offs}, code{code} {
}
