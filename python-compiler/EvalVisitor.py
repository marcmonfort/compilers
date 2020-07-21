if __name__ is not None and "." in __name__:
    from .ExprParser import ExprParser
    from .ExprVisitor import ExprVisitor
else:
    from ExprParser import ExprParser
    from ExprVisitor import ExprVisitor
class EvalVisitor(ExprVisitor):
    
    symTable = dict()
    
    def visitRoot(self, ctx:ExprParser.RootContext):
        n = next(ctx.getChildren())
        self.visit(n)
        #print(self.visit(n))
        
    """ def visitExpr(self, ctx:ExprParser.ExprContext):
        l = [n for n in ctx.getChildren()]        
        if len(l) == 1:
            return int(l[0].getText())
        elif len(l) == 3:
            return self.visit(l[0]) + self.visit(l[2]) """
    
    def visitArithmetic(self, ctx:ExprParser.ArithmeticContext):
        l = [n for n in ctx.getChildren()]

        if ctx.ADD():
            return self.visit(l[0]) + self.visit(l[2])
        elif ctx.SUB():
            return self.visit(l[0]) - self.visit(l[2])
        elif ctx.MUL():
            return self.visit(l[0]) * self.visit(l[2])
        elif ctx.DIV():
            return self.visit(l[0]) / self.visit(l[2])
        elif ctx.POW():
            return self.visit(l[0]) ** self.visit(l[2])
    
    def visitRelational(self, ctx:ExprParser.RelationalContext):
        l = [n for n in ctx.getChildren()]
        if ctx.EQ():
            return self.visit(l[0]) == self.visit(l[2])
        elif ctx.NEQ():
            return self.visit(l[0]) != self.visit(l[2])
        elif ctx.LT():
            return self.visit(l[0]) < self.visit(l[2])
        elif ctx.LTE():
            return self.visit(l[0]) <= self.visit(l[2])
        elif ctx.GT():
            return self.visit(l[0]) > self.visit(l[2])
        elif ctx.GTE():
            return self.visit(l[0]) >= self.visit(l[2])

    def visitExprIdent(self, ctx:ExprParser.ExprIdentContext):
        return self.symTable.get(str(ctx.ID()))
    
    def visitValue(self, ctx:ExprParser.ValueContext):
        #print(ctx.NUM().getText())
        n = next(ctx.getChildren())
        return int(n.getText())
    
    def visitAssignStmt(self, ctx:ExprParser.AssignStmtContext):
        self.symTable[str(ctx.ID())] = self.visit(ctx.expr())
    
    def visitWriteExpr(self, ctx:ExprParser.WriteExprContext):
        print(self.visit(ctx.expr()))
        
    def visitReadStmt(self, ctx:ExprParser.ReadStmtContext):
        self.symTable[str(ctx.ID())] = int(input())

    def visitIfStmt(self, ctx:ExprParser.IfStmtContext):
        if self.visit(ctx.expr()):
            self.visit(ctx.statements())
        
    def visitWhileStmt(self, ctx:ExprParser.WhileStmtContext):
        while self.visit(ctx.expr()):
            self.visit(ctx.statements())
