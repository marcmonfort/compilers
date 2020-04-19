if __name__ is not None and "." in __name__:
    from .ExprParser import ExprParser
    from .ExprVisitor import ExprVisitor
else:
    from ExprParser import ExprParser
    from ExprVisitor import ExprVisitor
class TreeVisitor(ExprVisitor):
    def __init__(self):
        self.nivell = 0

    def visitValue(self, ctx:ExprParser.ValueContext):
        n = next(ctx.getChildren())
        print("  " * self.nivell +
            ExprParser.symbolicNames[n.getSymbol().type] +
            '(' +n.getText() + ')')
        self.nivell -= 1
        
    def visitArithmetic(self, ctx:ExprParser.ArithmeticContext):

        #print(ctx.getChild(1)) == ExprParser.literalNames[ctx.op.type] #+,-
        #print(ctx.getText()) #1+2
        #print(ctx.expr(1).getText()) #imprime el valor de expr correcto

        """ if ctx.op.type == ExprParser.MUL:   #funciona
            print("hola")"""

        print('  ' *  self.nivell + 
              ExprParser.symbolicNames[ctx.op.type] +
              '('+str(ctx.getChild(1))+')')
        self.nivell += 1
        self.visit(ctx.expr(0))
        self.nivell += 1
        self.visit(ctx.expr(1))
        self.nivell -= 1
    


"""     
    def visitExpr(self, ctx:ExprParser.ExprContext):
        if ctx.getChildCount() == 1:
            n = next(ctx.getChildren())
            print("  " * self.nivell +
                  ExprParser.symbolicNames[n.getSymbol().type] +
                  '(' +n.getText() + ')')
            self.nivell -= 1
        elif ctx.getChildCount() == 3:
            print('  ' *  self.nivell + 'MES(+)')
            self.nivell += 1
            self.visit(ctx.expr(0))
            self.nivell += 1
            self.visit(ctx.expr(1))
            self.nivell -= 1 
"""