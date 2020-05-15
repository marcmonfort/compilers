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
  
  if (ctx->basic_type()) 
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
  //subroutine & subr = Code.get_last_subroutine();
  std::vector<var> lvars;

  for (unsigned int i = 0; i < ctx->ID().size(); i++) {
    lvars.push_back(var{ctx->ID(i)->getText(), size});
  }
  DEBUG_EXIT();
  return lvars;

}

antlrcpp::Any CodeGenVisitor::visitStatements(AslParser::StatementsContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  for (auto stCtx : ctx->statement()) {
    instructionList && codeS = visit(stCtx);
    code = code || codeS;
  }
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitAssignStmt(AslParser::AssignStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
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

  code = code1 || code2;

  /* if (Types.isArrayTy(tid1) and Types.isArrayTy(tid2)){

  } */

  if (Types.isFloatTy(tid1) and Types.isIntegerTy(tid2)){
    std::string temp = "%"+codeCounters.newTEMP();
    code = code || instruction::FLOAT(temp, addr2);
    addr2 = temp;
  }

  if (ctx->left_expr()->expr()){  //assig to and element
    code = code || instruction::XLOAD(addr1, offs1, addr2);
  }
  else
    code = code || instruction::LOAD(addr1, addr2);







  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitIfStmt(AslParser::IfStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = visit(ctx->expr());
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = visit(ctx->statements(0)); //NEW falta ELSE
  if (ctx->ELSE())
    instructionList &&   code3 = visit(ctx->statements(1)); //NEW falta ELSE

  std::string label = codeCounters.newLabelIF();
  std::string labelEndIf = "endif"+label;
  code = code1 || instruction::FJUMP(addr1, labelEndIf) ||
         code2 || instruction::LABEL(labelEndIf);
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWhileStmt(AslParser::WhileStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  CodeAttribs     && codAtsE = visit(ctx->expr());
  std::string          addr1 = codAtsE.addr;
  instructionList &    code1 = codAtsE.code;
  instructionList &&   code2 = visit(ctx->statements());
  std::string labelWhile = "while"+codeCounters.newLabelWHILE();
  std::string labelEndWhile = "end"+labelWhile;
  code = instruction::LABEL(labelWhile) || code1 ||
         instruction::FJUMP(addr1, labelEndWhile) || code2 ||
         instruction::UJUMP(labelWhile) || instruction::LABEL(labelEndWhile);
  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitProcCall(AslParser::ProcCallContext *ctx) {
  DEBUG_ENTER();

  instructionList code;
  instructionList paramsPush;
  instructionList paramsPop;
  TypesMgr::TypeId  tID = getTypeDecor(ctx->ident());
  auto typesParams = Types.getFuncParamsTypes(tID);
  std::string temp; //for all temp's

  for (size_t i = 0; i < (ctx->expr()).size(); ++i){
    CodeAttribs     && codAt1 = visit(ctx->expr(i));
    std::string         addr1 = codAt1.addr;
    instructionList &   code1 = codAt1.code;
    
    code = code || code1;
    temp = addr1;
    TypesMgr::TypeId  tParam = getTypeDecor(ctx->expr(i));

    if (Types.isFloatTy(typesParams[i]) and Types.isIntegerTy(tParam)){
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp,addr1);
    }
    else if (Types.isArrayTy(tParam)){
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(temp,addr1);
    }
    //hay que hacerlo despues, por si hay mas CALL en los parametros.
    paramsPush = paramsPush || instruction::PUSH(temp); 
    paramsPop = paramsPop || instruction::POP(); 
  }

  if (not Types.isVoidFunction(tID)) {  // return...
    paramsPush = paramsPush || instruction::PUSH();
    paramsPop = paramsPop || instruction::POP();
  }

  code = code || paramsPush;

  std::string name = ctx->ident()->getText(); //hacer visit???
  code = code || instruction::CALL(name);

  code = code || paramsPop;

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return code;





  /* instructionList code;
  // std::string name = ctx->ident()->ID()->getSymbol()->getText();
  std::string name = ctx->ident()->getText();
  code = instruction::CALL(name);
  DEBUG_EXIT();
  return code; */
}

antlrcpp::Any CodeGenVisitor::visitReturnStmt(AslParser::ReturnStmtContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  if (ctx->expr()) {
    CodeAttribs     && codAt1 = visit(ctx->expr());
    std::string         addr1 = codAt1.addr;
    instructionList &   code1 = codAt1.code;
    code = code1 || instruction::LOAD("_result",addr1) || instruction::RETURN();
  }
  //code = code || instruction::RETURN(); // ya hay return en la funcion.
  DEBUG_EXIT();
  return code;  // puede que haga falta más ?
}

antlrcpp::Any CodeGenVisitor::visitReadStmt(AslParser::ReadStmtContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAtsE = visit(ctx->left_expr());
  std::string          addr1 = codAtsE.addr;
  std::string          offs1 = codAtsE.offs;
  instructionList &    code1 = codAtsE.code;
  instructionList &     code = code1;
  TypesMgr::TypeId tid1 = getTypeDecor(ctx->left_expr());

  std::string temp = ctx->left_expr()->expr() ? "%" + codeCounters.newTEMP() 
                                              : addr1;

  if (Types.isFloatTy(tid1))          code = code || instruction::READF(temp);
  else if (Types.isCharacterTy(tid1)) code = code || instruction::READC(temp);
  else                                code = code || instruction::READI(temp);

  if (ctx->left_expr()->expr()){
    code = code || instruction::XLOAD(addr1, offs1, temp);
  }

  DEBUG_EXIT();
  return code;
}

antlrcpp::Any CodeGenVisitor::visitWriteExpr(AslParser::WriteExprContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  // std::string         offs1 = codAt1.offs;
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
      code = code ||
	     instruction::CHLOAD(temp, s.substr(i,1)) ||
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
        code = code ||
               instruction::CHLOAD(temp, s.substr(i,2)) ||
	       instruction::WRITEC(temp);
        i += 2;
      }
      else {
        code = code ||
               instruction::CHLOAD(temp, s.substr(i,1)) ||
	       instruction::WRITEC(temp);
        i += 1;
      }
    }
  }
  DEBUG_EXIT();
  return code;
}

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
    if (Symbols.isParameterClass(addrID)) { //por referencia
      std::string temp = "%"+codeCounters.newTEMP();
      code = code || instruction::LOAD(temp, addrID);
      addrID = temp;
    }
  }

  CodeAttribs codAts(addrID, offs, code);
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
    if (ctx->MUL())
      code = code || instruction::MUL(temp, addr1, addr2);
    else if (ctx->DIV())
      code = code || instruction::DIV(temp, addr1, addr2);
    else if (ctx->PLUS())
      code = code || instruction::ADD(temp, addr1, addr2);
    else if (ctx->SUB())
      code = code || instruction::SUB(temp, addr1, addr2);
    else // (ctx->MOD())
      code = code || instruction::DIV(temp, addr1, addr2) ||
             instruction::MUL(temp, temp, addr2) ||
             instruction::SUB(temp, addr1, temp);
  }
  //FLOAT's
  else {
    instructionList toFloat;
    std::string addrF1 = addr1;
    std::string addrF2 = addr2;
    if (Types.isIntegerTy(t1)) {
      addrF1 = "%"+codeCounters.newTEMP();
      //std::cout << "el_1" << addrF1 << std::endl;
      toFloat = toFloat || instruction::FLOAT(addrF1, addr1);
    }
    else if (Types.isIntegerTy(t2)) {
      addrF2 = "%"+codeCounters.newTEMP();
      //std::cout << "el_2 " << addrF2 << " -- " << addr2 << std::endl;
      toFloat = toFloat || instruction::FLOAT(addrF2, addr2);
    }

    if (ctx->MUL())
      code = code || toFloat || instruction::FMUL(temp, addrF1, addrF2);
    else if (ctx->DIV())
      code = code || toFloat || instruction::FDIV(temp, addrF1, addrF2);
    else if (ctx->PLUS())
      code = code || toFloat || instruction::FADD(temp, addrF1, addrF2);
    else // (ctx->SUB())
      code = code || toFloat || instruction::FSUB(temp, addrF1, addrF2);
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
  // TypesMgr::TypeId  t = getTypeDecor(ctx);

  std::string temp = "%"+codeCounters.newTEMP();

  if (not Types.isFloatTy(t1) and not Types.isFloatTy(t1)){
    if (ctx->EQ())
      code = code || instruction::EQ(temp, addr1, addr2);
    else if (ctx->NEQ())
      code = code || instruction::EQ(temp, addr1, addr2) ||
             instruction::NOT(temp, temp);
    else if (ctx->LT())
      code = code || instruction::LT(temp, addr1, addr2);
    else if (ctx->LTE())
      code = code || instruction::LE(temp, addr1, addr2);
    else if (ctx->GT())
      code = code || instruction::LE(temp, addr1, addr2) ||
             instruction::NOT(temp, temp);
    else// (ctx->GTE())
      code = code || instruction::LT(temp, addr1, addr2) ||
             instruction::NOT(temp, temp);
  }
  //FLOAT's
  else {
    instructionList toFloat;
    std::string addrF1 = addr1;
    std::string addrF2 = addr2;
    if (Types.isIntegerTy(t1)) {
      addrF1 = "%"+codeCounters.newTEMP();
      toFloat = toFloat || instruction::FLOAT(addrF1, addr1);
    }
    else if (Types.isIntegerTy(t2)) {
      addrF2 = "%"+codeCounters.newTEMP();
      toFloat = toFloat || instruction::FLOAT(addrF2, addr2);
    }
    
    if (ctx->EQ())
      code = code || toFloat || instruction::FEQ(temp, addrF1, addrF2);
    else if (ctx->NEQ())
      code = code || toFloat || instruction::FEQ(temp, addrF1, addrF2) ||
             instruction::NOT(temp, temp);
    else if (ctx->LT())
      code = code || toFloat || instruction::FLT(temp, addrF1, addrF2);
    else if (ctx->LTE())
      code = code || toFloat || instruction::FLE(temp, addrF1, addrF2);
    else if (ctx->GT())
      code = code || toFloat || instruction::FLE(temp, addrF1, addrF2) ||
             instruction::NOT(temp, temp);
    else// (ctx->GTE())
      code = code || toFloat || instruction::FLT(temp, addrF1, addrF2) ||
             instruction::NOT(temp, temp);
  }

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitValue(AslParser::ValueContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  std::string temp = "%"+codeCounters.newTEMP();
  if (ctx->INTVAL())
    code = instruction::ILOAD(temp, ctx->getText());
  else if (ctx->FLOATVAL())
    code = instruction::FLOAD(temp, ctx->getText());
  else if (ctx->BOOLVAL())
    code = instruction::LOAD(temp, (ctx->getText()=="true" ? "1":"0" ));
  else // (ctx->BOOLVAL())
    code = instruction::CHLOAD(temp, ctx->getText());//MAL???

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

antlrcpp::Any CodeGenVisitor::visitIdent(AslParser::IdentContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs codAts(ctx->ID()->getText(), "", instructionList());
  DEBUG_EXIT();
  return codAts;
}


/// /// /// ///
//NEW /// /// ///
/// /// /// ///

antlrcpp::Any CodeGenVisitor::visitParenthesis(AslParser::ParenthesisContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs && codAts = visit(ctx->expr());
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

  if (ctx->AND())
    code = code || instruction::AND(temp, addr1, addr2);
  else // (ctx->OR())
    code = code || instruction::OR(temp, addr1, addr2);

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitUnary(AslParser::UnaryContext *ctx) {
  DEBUG_ENTER();
  CodeAttribs     && codAt1 = visit(ctx->expr());
  std::string         addr1 = codAt1.addr;
  instructionList &   code = codAt1.code;
  //instructionList &&   code = code1; //evitar referencia??? ESTO MEJOR!!!???

  TypesMgr::TypeId  t = getTypeDecor(ctx->expr());
  std::string temp = "%"+codeCounters.newTEMP();

  if (ctx->NOT())
    code = code || instruction::NOT(temp, addr1);
  else if (ctx->SUB())
    code = code || (Types.isFloatTy(t) ? instruction::FNEG(temp, addr1)
                                       : instruction::NEG(temp, addr1));

  CodeAttribs codAts(temp, "", code);
  DEBUG_EXIT();
  return codAts;
}

antlrcpp::Any CodeGenVisitor::visitFunction_call(AslParser::Function_callContext *ctx) {
  DEBUG_ENTER();
  instructionList code;
  instructionList paramsPush;
  instructionList paramsPop;
  auto typesParams = Types.getFuncParamsTypes(getTypeDecor(ctx->ident()));
  std::string temp; //for all temp's

  for (size_t i = 0; i < (ctx->expr()).size(); ++i){
    CodeAttribs     && codAt1 = visit(ctx->expr(i));
    std::string         addr1 = codAt1.addr;
    instructionList &   code1 = codAt1.code;
    
    code = code || code1;
    temp = addr1;
    TypesMgr::TypeId  tParam = getTypeDecor(ctx->expr(i));

    if (Types.isFloatTy(typesParams[i]) and Types.isIntegerTy(tParam)){
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::FLOAT(temp,addr1);
    }
    else if (Types.isArrayTy(tParam)){
      temp = "%"+codeCounters.newTEMP();
      code = code || instruction::ALOAD(temp,addr1);
    }
    //hay que hacerlo despues, por si hay mas CALL en los parametros.
    paramsPush = paramsPush || instruction::PUSH(temp); 
    paramsPop = paramsPop || instruction::POP();
  }

  code = code || instruction::PUSH() || paramsPush;

  // std::string name = ctx->ident()->ID()->getSymbol()->getText();
  std::string name = ctx->ident()->getText(); //hacer visit???
  code = code || instruction::CALL(name);

  temp = "%"+codeCounters.newTEMP();  //put return to tmp
  code = code || paramsPop || instruction::POP(temp);

  CodeAttribs codAts(temp, "", code);
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
  instructionList &&   code = codeID || codeIndex;
  //consideramos siempre offset tamaño 1 (basic_type)

  std::string temp = "%"+codeCounters.newTEMP();

  if (Symbols.isLocalVarClass(addrID))
    code = code || instruction::LOADX(temp, addrID, addrIndex);
  else { //isParameterClass
    std::string temp2 = "%"+codeCounters.newTEMP();
    code = code || instruction::LOAD(temp2, addrID) ||
                   instruction::LOADX(temp, temp2, addrIndex);
  }
  CodeAttribs codAts(temp, "", code);

  
  //PUEDE QUE FALTE SI PARAM???
  DEBUG_EXIT();
  return codAts;
}


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
