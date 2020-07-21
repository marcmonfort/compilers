import sys
from antlr4 import *
from ExprLexer import ExprLexer
from ExprParser import ExprParser
from TreeVisitor import TreeVisitor
from EvalVisitor import EvalVisitor


#input_stream = InputStream(input('? '))
#input_stream = StdinStream()
input_stream = FileStream(sys.argv[1])


lexer = ExprLexer(input_stream)
token_stream = CommonTokenStream(lexer)
parser = ExprParser(token_stream)
tree = parser.root() 
#print(tree.toStringTree(recog=parser))

""" visitor = TreeVisitor()
visitor.visit(tree) """

visitor2 = EvalVisitor()
visitor2.visit(tree)