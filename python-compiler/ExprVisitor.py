# Generated from Expr.g by ANTLR 4.8
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .ExprParser import ExprParser
else:
    from ExprParser import ExprParser

# This class defines a complete generic visitor for a parse tree produced by ExprParser.

class ExprVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by ExprParser#root.
    def visitRoot(self, ctx:ExprParser.RootContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#statements.
    def visitStatements(self, ctx:ExprParser.StatementsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#assignStmt.
    def visitAssignStmt(self, ctx:ExprParser.AssignStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#writeExpr.
    def visitWriteExpr(self, ctx:ExprParser.WriteExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#readStmt.
    def visitReadStmt(self, ctx:ExprParser.ReadStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#ifStmt.
    def visitIfStmt(self, ctx:ExprParser.IfStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#whileStmt.
    def visitWhileStmt(self, ctx:ExprParser.WhileStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#exprIdent.
    def visitExprIdent(self, ctx:ExprParser.ExprIdentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#arithmetic.
    def visitArithmetic(self, ctx:ExprParser.ArithmeticContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#relational.
    def visitRelational(self, ctx:ExprParser.RelationalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#parenthesis.
    def visitParenthesis(self, ctx:ExprParser.ParenthesisContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by ExprParser#value.
    def visitValue(self, ctx:ExprParser.ValueContext):
        return self.visitChildren(ctx)



del ExprParser