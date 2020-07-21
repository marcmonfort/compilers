// Generated from /home/hammer/fib-upc/cl/NASA/examen/asl/Asl.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class AslParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		ASSIGN=10, PLUS=11, SUB=12, MUL=13, DIV=14, MOD=15, EQ=16, NEQ=17, GT=18, 
		GTE=19, LT=20, LTE=21, AND=22, OR=23, NOT=24, VAR=25, INT=26, FLOAT=27, 
		BOOL=28, CHAR=29, ARRAY=30, IF=31, THEN=32, ELSE=33, ENDIF=34, WHILE=35, 
		ENDWHILE=36, FUNC=37, ENDFUNC=38, RETURN=39, READ=40, WRITE=41, SUM=42, 
		FILTER=43, INTO=44, USING=45, MAX=46, FOR=47, IN=48, RANGE=49, ENDFOR=50, 
		A_MAX=51, INTVAL=52, FLOATVAL=53, CHARVAL=54, BOOLVAL=55, ID=56, STRING=57, 
		COMMENT=58, WS=59;
	public static final int
		RULE_program = 0, RULE_function = 1, RULE_parameters = 2, RULE_declarations = 3, 
		RULE_variable_decl = 4, RULE_type = 5, RULE_array_type = 6, RULE_basic_type = 7, 
		RULE_statements = 8, RULE_statement = 9, RULE_left_expr = 10, RULE_expr = 11, 
		RULE_ident = 12;
	public static final String[] ruleNames = {
		"program", "function", "parameters", "declarations", "variable_decl", 
		"type", "array_type", "basic_type", "statements", "statement", "left_expr", 
		"expr", "ident"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'('", "')'", "':'", "','", "'['", "']'", "'of'", "';'", "'do'", 
		"'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'=='", "'!='", "'>'", "'>='", 
		"'<'", "'<='", "'and'", "'or'", "'not'", "'var'", "'int'", "'float'", 
		"'bool'", "'char'", "'array'", "'if'", "'then'", "'else'", "'endif'", 
		"'while'", "'endwhile'", "'func'", "'endfunc'", "'return'", "'read'", 
		"'write'", "'sum'", "'filter'", "'into'", "'using'", "'max_'", "'for'", 
		"'in'", "'range'", "'endfor'", "'.max'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, "ASSIGN", 
		"PLUS", "SUB", "MUL", "DIV", "MOD", "EQ", "NEQ", "GT", "GTE", "LT", "LTE", 
		"AND", "OR", "NOT", "VAR", "INT", "FLOAT", "BOOL", "CHAR", "ARRAY", "IF", 
		"THEN", "ELSE", "ENDIF", "WHILE", "ENDWHILE", "FUNC", "ENDFUNC", "RETURN", 
		"READ", "WRITE", "SUM", "FILTER", "INTO", "USING", "MAX", "FOR", "IN", 
		"RANGE", "ENDFOR", "A_MAX", "INTVAL", "FLOATVAL", "CHARVAL", "BOOLVAL", 
		"ID", "STRING", "COMMENT", "WS"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Asl.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public AslParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(AslParser.EOF, 0); }
		public List<FunctionContext> function() {
			return getRuleContexts(FunctionContext.class);
		}
		public FunctionContext function(int i) {
			return getRuleContext(FunctionContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(27); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(26);
				function();
				}
				}
				setState(29); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==FUNC );
			setState(31);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionContext extends ParserRuleContext {
		public TerminalNode FUNC() { return getToken(AslParser.FUNC, 0); }
		public TerminalNode ID() { return getToken(AslParser.ID, 0); }
		public ParametersContext parameters() {
			return getRuleContext(ParametersContext.class,0);
		}
		public DeclarationsContext declarations() {
			return getRuleContext(DeclarationsContext.class,0);
		}
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode ENDFUNC() { return getToken(AslParser.ENDFUNC, 0); }
		public Basic_typeContext basic_type() {
			return getRuleContext(Basic_typeContext.class,0);
		}
		public FunctionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_function; }
	}

	public final FunctionContext function() throws RecognitionException {
		FunctionContext _localctx = new FunctionContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_function);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(33);
			match(FUNC);
			setState(34);
			match(ID);
			setState(35);
			match(T__0);
			setState(36);
			parameters();
			setState(37);
			match(T__1);
			setState(40);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__2) {
				{
				setState(38);
				match(T__2);
				setState(39);
				basic_type();
				}
			}

			setState(42);
			declarations();
			setState(43);
			statements();
			setState(44);
			match(ENDFUNC);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ParametersContext extends ParserRuleContext {
		public List<TerminalNode> ID() { return getTokens(AslParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(AslParser.ID, i);
		}
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public ParametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameters; }
	}

	public final ParametersContext parameters() throws RecognitionException {
		ParametersContext _localctx = new ParametersContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_parameters);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(59);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__1:
				{
				}
				break;
			case ID:
				{
				setState(47);
				match(ID);
				setState(48);
				match(T__2);
				setState(49);
				type();
				setState(56);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__3) {
					{
					{
					setState(50);
					match(T__3);
					setState(51);
					match(ID);
					setState(52);
					match(T__2);
					setState(53);
					type();
					}
					}
					setState(58);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclarationsContext extends ParserRuleContext {
		public List<Variable_declContext> variable_decl() {
			return getRuleContexts(Variable_declContext.class);
		}
		public Variable_declContext variable_decl(int i) {
			return getRuleContext(Variable_declContext.class,i);
		}
		public DeclarationsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declarations; }
	}

	public final DeclarationsContext declarations() throws RecognitionException {
		DeclarationsContext _localctx = new DeclarationsContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_declarations);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(64);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==VAR) {
				{
				{
				setState(61);
				variable_decl();
				}
				}
				setState(66);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Variable_declContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(AslParser.VAR, 0); }
		public List<TerminalNode> ID() { return getTokens(AslParser.ID); }
		public TerminalNode ID(int i) {
			return getToken(AslParser.ID, i);
		}
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public Variable_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variable_decl; }
	}

	public final Variable_declContext variable_decl() throws RecognitionException {
		Variable_declContext _localctx = new Variable_declContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_variable_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(67);
			match(VAR);
			setState(68);
			match(ID);
			setState(73);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__3) {
				{
				{
				setState(69);
				match(T__3);
				setState(70);
				match(ID);
				}
				}
				setState(75);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(76);
			match(T__2);
			setState(77);
			type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TypeContext extends ParserRuleContext {
		public Basic_typeContext basic_type() {
			return getRuleContext(Basic_typeContext.class,0);
		}
		public Array_typeContext array_type() {
			return getRuleContext(Array_typeContext.class,0);
		}
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_type);
		try {
			setState(81);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case INT:
			case FLOAT:
			case BOOL:
			case CHAR:
				enterOuterAlt(_localctx, 1);
				{
				setState(79);
				basic_type();
				}
				break;
			case ARRAY:
				enterOuterAlt(_localctx, 2);
				{
				setState(80);
				array_type();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Array_typeContext extends ParserRuleContext {
		public TerminalNode ARRAY() { return getToken(AslParser.ARRAY, 0); }
		public TerminalNode INTVAL() { return getToken(AslParser.INTVAL, 0); }
		public Basic_typeContext basic_type() {
			return getRuleContext(Basic_typeContext.class,0);
		}
		public Array_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_array_type; }
	}

	public final Array_typeContext array_type() throws RecognitionException {
		Array_typeContext _localctx = new Array_typeContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_array_type);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(83);
			match(ARRAY);
			setState(84);
			match(T__4);
			setState(85);
			match(INTVAL);
			setState(86);
			match(T__5);
			setState(87);
			match(T__6);
			setState(88);
			basic_type();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Basic_typeContext extends ParserRuleContext {
		public TerminalNode INT() { return getToken(AslParser.INT, 0); }
		public TerminalNode FLOAT() { return getToken(AslParser.FLOAT, 0); }
		public TerminalNode BOOL() { return getToken(AslParser.BOOL, 0); }
		public TerminalNode CHAR() { return getToken(AslParser.CHAR, 0); }
		public Basic_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_basic_type; }
	}

	public final Basic_typeContext basic_type() throws RecognitionException {
		Basic_typeContext _localctx = new Basic_typeContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_basic_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(90);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << INT) | (1L << FLOAT) | (1L << BOOL) | (1L << CHAR))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementsContext extends ParserRuleContext {
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public StatementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statements; }
	}

	public final StatementsContext statements() throws RecognitionException {
		StatementsContext _localctx = new StatementsContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_statements);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(95);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << IF) | (1L << WHILE) | (1L << RETURN) | (1L << READ) | (1L << WRITE) | (1L << FOR) | (1L << ID))) != 0)) {
				{
				{
				setState(92);
				statement();
				}
				}
				setState(97);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
	 
		public StatementContext() { }
		public void copyFrom(StatementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ForRangeContext extends StatementContext {
		public TerminalNode FOR() { return getToken(AslParser.FOR, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode IN() { return getToken(AslParser.IN, 0); }
		public TerminalNode RANGE() { return getToken(AslParser.RANGE, 0); }
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode ENDFOR() { return getToken(AslParser.ENDFOR, 0); }
		public ForRangeContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class ProcCallContext extends StatementContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public ProcCallContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class WriteExprContext extends StatementContext {
		public TerminalNode WRITE() { return getToken(AslParser.WRITE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public WriteExprContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class WhileStmtContext extends StatementContext {
		public TerminalNode WHILE() { return getToken(AslParser.WHILE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public StatementsContext statements() {
			return getRuleContext(StatementsContext.class,0);
		}
		public TerminalNode ENDWHILE() { return getToken(AslParser.ENDWHILE, 0); }
		public WhileStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class IfStmtContext extends StatementContext {
		public TerminalNode IF() { return getToken(AslParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode THEN() { return getToken(AslParser.THEN, 0); }
		public List<StatementsContext> statements() {
			return getRuleContexts(StatementsContext.class);
		}
		public StatementsContext statements(int i) {
			return getRuleContext(StatementsContext.class,i);
		}
		public TerminalNode ENDIF() { return getToken(AslParser.ENDIF, 0); }
		public TerminalNode ELSE() { return getToken(AslParser.ELSE, 0); }
		public IfStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class ReadStmtContext extends StatementContext {
		public TerminalNode READ() { return getToken(AslParser.READ, 0); }
		public Left_exprContext left_expr() {
			return getRuleContext(Left_exprContext.class,0);
		}
		public ReadStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class AssignStmtContext extends StatementContext {
		public Left_exprContext left_expr() {
			return getRuleContext(Left_exprContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(AslParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public AssignStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class ReturnStmtContext extends StatementContext {
		public TerminalNode RETURN() { return getToken(AslParser.RETURN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ReturnStmtContext(StatementContext ctx) { copyFrom(ctx); }
	}
	public static class WriteStringContext extends StatementContext {
		public TerminalNode WRITE() { return getToken(AslParser.WRITE, 0); }
		public TerminalNode STRING() { return getToken(AslParser.STRING, 0); }
		public WriteStringContext(StatementContext ctx) { copyFrom(ctx); }
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_statement);
		int _la;
		try {
			setState(170);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				_localctx = new AssignStmtContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(98);
				left_expr();
				setState(99);
				match(ASSIGN);
				setState(100);
				expr(0);
				setState(101);
				match(T__7);
				}
				break;
			case 2:
				_localctx = new ForRangeContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(103);
				match(FOR);
				setState(104);
				expr(0);
				setState(105);
				match(IN);
				setState(106);
				match(RANGE);
				setState(107);
				match(T__0);
				setState(116);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << PLUS) | (1L << SUB) | (1L << NOT) | (1L << SUM) | (1L << FILTER) | (1L << MAX) | (1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL) | (1L << ID))) != 0)) {
					{
					setState(108);
					expr(0);
					setState(113);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__3) {
						{
						{
						setState(109);
						match(T__3);
						setState(110);
						expr(0);
						}
						}
						setState(115);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(118);
				match(T__1);
				setState(119);
				match(T__8);
				setState(120);
				statements();
				setState(121);
				match(ENDFOR);
				}
				break;
			case 3:
				_localctx = new IfStmtContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(123);
				match(IF);
				setState(124);
				expr(0);
				setState(125);
				match(THEN);
				setState(126);
				statements();
				setState(129);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==ELSE) {
					{
					setState(127);
					match(ELSE);
					setState(128);
					statements();
					}
				}

				setState(131);
				match(ENDIF);
				}
				break;
			case 4:
				_localctx = new WhileStmtContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(133);
				match(WHILE);
				setState(134);
				expr(0);
				setState(135);
				match(T__8);
				setState(136);
				statements();
				setState(137);
				match(ENDWHILE);
				}
				break;
			case 5:
				_localctx = new ProcCallContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(139);
				ident();
				setState(140);
				match(T__0);
				setState(149);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << PLUS) | (1L << SUB) | (1L << NOT) | (1L << SUM) | (1L << FILTER) | (1L << MAX) | (1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL) | (1L << ID))) != 0)) {
					{
					setState(141);
					expr(0);
					setState(146);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__3) {
						{
						{
						setState(142);
						match(T__3);
						setState(143);
						expr(0);
						}
						}
						setState(148);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(151);
				match(T__1);
				setState(152);
				match(T__7);
				}
				break;
			case 6:
				_localctx = new ReturnStmtContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(154);
				match(RETURN);
				setState(156);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << PLUS) | (1L << SUB) | (1L << NOT) | (1L << SUM) | (1L << FILTER) | (1L << MAX) | (1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL) | (1L << ID))) != 0)) {
					{
					setState(155);
					expr(0);
					}
				}

				setState(158);
				match(T__7);
				}
				break;
			case 7:
				_localctx = new ReadStmtContext(_localctx);
				enterOuterAlt(_localctx, 7);
				{
				setState(159);
				match(READ);
				setState(160);
				left_expr();
				setState(161);
				match(T__7);
				}
				break;
			case 8:
				_localctx = new WriteExprContext(_localctx);
				enterOuterAlt(_localctx, 8);
				{
				setState(163);
				match(WRITE);
				setState(164);
				expr(0);
				setState(165);
				match(T__7);
				}
				break;
			case 9:
				_localctx = new WriteStringContext(_localctx);
				enterOuterAlt(_localctx, 9);
				{
				setState(167);
				match(WRITE);
				setState(168);
				match(STRING);
				setState(169);
				match(T__7);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Left_exprContext extends ParserRuleContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Left_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_left_expr; }
	}

	public final Left_exprContext left_expr() throws RecognitionException {
		Left_exprContext _localctx = new Left_exprContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_left_expr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(172);
			ident();
			setState(177);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__4) {
				{
				setState(173);
				match(T__4);
				setState(174);
				expr(0);
				setState(175);
				match(T__5);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class ArrayMaxContext extends ExprContext {
		public Token op;
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode A_MAX() { return getToken(AslParser.A_MAX, 0); }
		public ArrayMaxContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class MaxContext extends ExprContext {
		public Token op;
		public TerminalNode MAX() { return getToken(AslParser.MAX, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public MaxContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Function_callContext extends ExprContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public Function_callContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ArithmeticContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode MUL() { return getToken(AslParser.MUL, 0); }
		public TerminalNode DIV() { return getToken(AslParser.DIV, 0); }
		public TerminalNode MOD() { return getToken(AslParser.MOD, 0); }
		public TerminalNode PLUS() { return getToken(AslParser.PLUS, 0); }
		public TerminalNode SUB() { return getToken(AslParser.SUB, 0); }
		public ArithmeticContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class SumContext extends ExprContext {
		public Token op;
		public TerminalNode SUM() { return getToken(AslParser.SUM, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public SumContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class UnaryContext extends ExprContext {
		public Token op;
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode NOT() { return getToken(AslParser.NOT, 0); }
		public TerminalNode PLUS() { return getToken(AslParser.PLUS, 0); }
		public TerminalNode SUB() { return getToken(AslParser.SUB, 0); }
		public UnaryContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ParenthesisContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ParenthesisContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class LogicalContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode AND() { return getToken(AslParser.AND, 0); }
		public TerminalNode OR() { return getToken(AslParser.OR, 0); }
		public LogicalContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class FilterContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode INTO() { return getToken(AslParser.INTO, 0); }
		public TerminalNode USING() { return getToken(AslParser.USING, 0); }
		public TerminalNode FILTER() { return getToken(AslParser.FILTER, 0); }
		public FilterContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ExprIdentContext extends ExprContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public ExprIdentContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class RelationalContext extends ExprContext {
		public Token op;
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode EQ() { return getToken(AslParser.EQ, 0); }
		public TerminalNode NEQ() { return getToken(AslParser.NEQ, 0); }
		public TerminalNode GT() { return getToken(AslParser.GT, 0); }
		public TerminalNode GTE() { return getToken(AslParser.GTE, 0); }
		public TerminalNode LTE() { return getToken(AslParser.LTE, 0); }
		public TerminalNode LT() { return getToken(AslParser.LT, 0); }
		public RelationalContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class Array_indexContext extends ExprContext {
		public IdentContext ident() {
			return getRuleContext(IdentContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Array_indexContext(ExprContext ctx) { copyFrom(ctx); }
	}
	public static class ValueContext extends ExprContext {
		public TerminalNode INTVAL() { return getToken(AslParser.INTVAL, 0); }
		public TerminalNode FLOATVAL() { return getToken(AslParser.FLOATVAL, 0); }
		public TerminalNode BOOLVAL() { return getToken(AslParser.BOOLVAL, 0); }
		public TerminalNode CHARVAL() { return getToken(AslParser.CHARVAL, 0); }
		public ValueContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 22;
		enterRecursionRule(_localctx, 22, RULE_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(242);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				{
				_localctx = new ParenthesisContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(180);
				match(T__0);
				setState(181);
				expr(0);
				setState(182);
				match(T__1);
				}
				break;
			case 2:
				{
				_localctx = new FilterContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(184);
				((FilterContext)_localctx).op = match(FILTER);
				setState(185);
				expr(0);
				setState(186);
				match(INTO);
				setState(187);
				expr(0);
				setState(188);
				match(USING);
				setState(189);
				expr(14);
				}
				break;
			case 3:
				{
				_localctx = new MaxContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(191);
				((MaxContext)_localctx).op = match(MAX);
				setState(192);
				match(T__0);
				setState(201);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << PLUS) | (1L << SUB) | (1L << NOT) | (1L << SUM) | (1L << FILTER) | (1L << MAX) | (1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL) | (1L << ID))) != 0)) {
					{
					setState(193);
					expr(0);
					setState(198);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__3) {
						{
						{
						setState(194);
						match(T__3);
						setState(195);
						expr(0);
						}
						}
						setState(200);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(203);
				match(T__1);
				}
				break;
			case 4:
				{
				_localctx = new SumContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(204);
				((SumContext)_localctx).op = match(SUM);
				setState(205);
				match(T__0);
				setState(216);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
				case 1:
					{
					setState(214);
					_errHandler.sync(this);
					_la = _input.LA(1);
					if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << PLUS) | (1L << SUB) | (1L << NOT) | (1L << SUM) | (1L << FILTER) | (1L << MAX) | (1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL) | (1L << ID))) != 0)) {
						{
						setState(206);
						expr(0);
						setState(211);
						_errHandler.sync(this);
						_la = _input.LA(1);
						while (_la==T__3) {
							{
							{
							setState(207);
							match(T__3);
							setState(208);
							expr(0);
							}
							}
							setState(213);
							_errHandler.sync(this);
							_la = _input.LA(1);
						}
						}
					}

					}
					break;
				}
				setState(218);
				match(T__1);
				}
				break;
			case 5:
				{
				_localctx = new Array_indexContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(219);
				ident();
				setState(220);
				match(T__4);
				setState(221);
				expr(0);
				setState(222);
				match(T__5);
				}
				break;
			case 6:
				{
				_localctx = new Function_callContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(224);
				ident();
				setState(225);
				match(T__0);
				setState(234);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << PLUS) | (1L << SUB) | (1L << NOT) | (1L << SUM) | (1L << FILTER) | (1L << MAX) | (1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL) | (1L << ID))) != 0)) {
					{
					setState(226);
					expr(0);
					setState(231);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__3) {
						{
						{
						setState(227);
						match(T__3);
						setState(228);
						expr(0);
						}
						}
						setState(233);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(236);
				match(T__1);
				}
				break;
			case 7:
				{
				_localctx = new UnaryContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(238);
				((UnaryContext)_localctx).op = _input.LT(1);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << PLUS) | (1L << SUB) | (1L << NOT))) != 0)) ) {
					((UnaryContext)_localctx).op = (Token)_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(239);
				expr(8);
				}
				break;
			case 8:
				{
				_localctx = new ValueContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(240);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << INTVAL) | (1L << FLOATVAL) | (1L << CHARVAL) | (1L << BOOLVAL))) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				break;
			case 9:
				{
				_localctx = new ExprIdentContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(241);
				ident();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(263);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,25,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(261);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,24,_ctx) ) {
					case 1:
						{
						_localctx = new ArithmeticContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(244);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(245);
						((ArithmeticContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << MUL) | (1L << DIV) | (1L << MOD))) != 0)) ) {
							((ArithmeticContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(246);
						expr(8);
						}
						break;
					case 2:
						{
						_localctx = new ArithmeticContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(247);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(248);
						((ArithmeticContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !(_la==PLUS || _la==SUB) ) {
							((ArithmeticContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(249);
						expr(7);
						}
						break;
					case 3:
						{
						_localctx = new RelationalContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(250);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(251);
						((RelationalContext)_localctx).op = _input.LT(1);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << EQ) | (1L << NEQ) | (1L << GT) | (1L << GTE) | (1L << LT) | (1L << LTE))) != 0)) ) {
							((RelationalContext)_localctx).op = (Token)_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(252);
						expr(6);
						}
						break;
					case 4:
						{
						_localctx = new LogicalContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(253);
						if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
						setState(254);
						((LogicalContext)_localctx).op = match(AND);
						setState(255);
						expr(5);
						}
						break;
					case 5:
						{
						_localctx = new LogicalContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(256);
						if (!(precpred(_ctx, 3))) throw new FailedPredicateException(this, "precpred(_ctx, 3)");
						setState(257);
						((LogicalContext)_localctx).op = match(OR);
						setState(258);
						expr(4);
						}
						break;
					case 6:
						{
						_localctx = new ArrayMaxContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(259);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(260);
						((ArrayMaxContext)_localctx).op = match(A_MAX);
						}
						break;
					}
					} 
				}
				setState(265);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,25,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class IdentContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(AslParser.ID, 0); }
		public IdentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ident; }
	}

	public final IdentContext ident() throws RecognitionException {
		IdentContext _localctx = new IdentContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_ident);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(266);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 11:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 7);
		case 1:
			return precpred(_ctx, 6);
		case 2:
			return precpred(_ctx, 5);
		case 3:
			return precpred(_ctx, 4);
		case 4:
			return precpred(_ctx, 3);
		case 5:
			return precpred(_ctx, 13);
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3=\u010f\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\3\2\6\2\36\n\2\r\2\16\2\37\3\2\3\2\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\5\3+\n\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3"+
		"\4\3\4\3\4\7\49\n\4\f\4\16\4<\13\4\5\4>\n\4\3\5\7\5A\n\5\f\5\16\5D\13"+
		"\5\3\6\3\6\3\6\3\6\7\6J\n\6\f\6\16\6M\13\6\3\6\3\6\3\6\3\7\3\7\5\7T\n"+
		"\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\t\3\t\3\n\7\n`\n\n\f\n\16\nc\13\n\3\13"+
		"\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\7\13r\n\13"+
		"\f\13\16\13u\13\13\5\13w\n\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13"+
		"\3\13\3\13\3\13\5\13\u0084\n\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13"+
		"\3\13\3\13\3\13\3\13\3\13\7\13\u0093\n\13\f\13\16\13\u0096\13\13\5\13"+
		"\u0098\n\13\3\13\3\13\3\13\3\13\3\13\5\13\u009f\n\13\3\13\3\13\3\13\3"+
		"\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13\5\13\u00ad\n\13\3\f\3\f\3"+
		"\f\3\f\3\f\5\f\u00b4\n\f\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3"+
		"\r\3\r\3\r\3\r\3\r\3\r\7\r\u00c7\n\r\f\r\16\r\u00ca\13\r\5\r\u00cc\n\r"+
		"\3\r\3\r\3\r\3\r\3\r\3\r\7\r\u00d4\n\r\f\r\16\r\u00d7\13\r\5\r\u00d9\n"+
		"\r\5\r\u00db\n\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\7\r\u00e8"+
		"\n\r\f\r\16\r\u00eb\13\r\5\r\u00ed\n\r\3\r\3\r\3\r\3\r\3\r\3\r\5\r\u00f5"+
		"\n\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3"+
		"\r\7\r\u0108\n\r\f\r\16\r\u010b\13\r\3\16\3\16\3\16\2\3\30\17\2\4\6\b"+
		"\n\f\16\20\22\24\26\30\32\2\b\3\2\34\37\4\2\r\16\32\32\3\2\669\3\2\17"+
		"\21\3\2\r\16\3\2\22\27\2\u012d\2\35\3\2\2\2\4#\3\2\2\2\6=\3\2\2\2\bB\3"+
		"\2\2\2\nE\3\2\2\2\fS\3\2\2\2\16U\3\2\2\2\20\\\3\2\2\2\22a\3\2\2\2\24\u00ac"+
		"\3\2\2\2\26\u00ae\3\2\2\2\30\u00f4\3\2\2\2\32\u010c\3\2\2\2\34\36\5\4"+
		"\3\2\35\34\3\2\2\2\36\37\3\2\2\2\37\35\3\2\2\2\37 \3\2\2\2 !\3\2\2\2!"+
		"\"\7\2\2\3\"\3\3\2\2\2#$\7\'\2\2$%\7:\2\2%&\7\3\2\2&\'\5\6\4\2\'*\7\4"+
		"\2\2()\7\5\2\2)+\5\20\t\2*(\3\2\2\2*+\3\2\2\2+,\3\2\2\2,-\5\b\5\2-.\5"+
		"\22\n\2./\7(\2\2/\5\3\2\2\2\60>\3\2\2\2\61\62\7:\2\2\62\63\7\5\2\2\63"+
		":\5\f\7\2\64\65\7\6\2\2\65\66\7:\2\2\66\67\7\5\2\2\679\5\f\7\28\64\3\2"+
		"\2\29<\3\2\2\2:8\3\2\2\2:;\3\2\2\2;>\3\2\2\2<:\3\2\2\2=\60\3\2\2\2=\61"+
		"\3\2\2\2>\7\3\2\2\2?A\5\n\6\2@?\3\2\2\2AD\3\2\2\2B@\3\2\2\2BC\3\2\2\2"+
		"C\t\3\2\2\2DB\3\2\2\2EF\7\33\2\2FK\7:\2\2GH\7\6\2\2HJ\7:\2\2IG\3\2\2\2"+
		"JM\3\2\2\2KI\3\2\2\2KL\3\2\2\2LN\3\2\2\2MK\3\2\2\2NO\7\5\2\2OP\5\f\7\2"+
		"P\13\3\2\2\2QT\5\20\t\2RT\5\16\b\2SQ\3\2\2\2SR\3\2\2\2T\r\3\2\2\2UV\7"+
		" \2\2VW\7\7\2\2WX\7\66\2\2XY\7\b\2\2YZ\7\t\2\2Z[\5\20\t\2[\17\3\2\2\2"+
		"\\]\t\2\2\2]\21\3\2\2\2^`\5\24\13\2_^\3\2\2\2`c\3\2\2\2a_\3\2\2\2ab\3"+
		"\2\2\2b\23\3\2\2\2ca\3\2\2\2de\5\26\f\2ef\7\f\2\2fg\5\30\r\2gh\7\n\2\2"+
		"h\u00ad\3\2\2\2ij\7\61\2\2jk\5\30\r\2kl\7\62\2\2lm\7\63\2\2mv\7\3\2\2"+
		"ns\5\30\r\2op\7\6\2\2pr\5\30\r\2qo\3\2\2\2ru\3\2\2\2sq\3\2\2\2st\3\2\2"+
		"\2tw\3\2\2\2us\3\2\2\2vn\3\2\2\2vw\3\2\2\2wx\3\2\2\2xy\7\4\2\2yz\7\13"+
		"\2\2z{\5\22\n\2{|\7\64\2\2|\u00ad\3\2\2\2}~\7!\2\2~\177\5\30\r\2\177\u0080"+
		"\7\"\2\2\u0080\u0083\5\22\n\2\u0081\u0082\7#\2\2\u0082\u0084\5\22\n\2"+
		"\u0083\u0081\3\2\2\2\u0083\u0084\3\2\2\2\u0084\u0085\3\2\2\2\u0085\u0086"+
		"\7$\2\2\u0086\u00ad\3\2\2\2\u0087\u0088\7%\2\2\u0088\u0089\5\30\r\2\u0089"+
		"\u008a\7\13\2\2\u008a\u008b\5\22\n\2\u008b\u008c\7&\2\2\u008c\u00ad\3"+
		"\2\2\2\u008d\u008e\5\32\16\2\u008e\u0097\7\3\2\2\u008f\u0094\5\30\r\2"+
		"\u0090\u0091\7\6\2\2\u0091\u0093\5\30\r\2\u0092\u0090\3\2\2\2\u0093\u0096"+
		"\3\2\2\2\u0094\u0092\3\2\2\2\u0094\u0095\3\2\2\2\u0095\u0098\3\2\2\2\u0096"+
		"\u0094\3\2\2\2\u0097\u008f\3\2\2\2\u0097\u0098\3\2\2\2\u0098\u0099\3\2"+
		"\2\2\u0099\u009a\7\4\2\2\u009a\u009b\7\n\2\2\u009b\u00ad\3\2\2\2\u009c"+
		"\u009e\7)\2\2\u009d\u009f\5\30\r\2\u009e\u009d\3\2\2\2\u009e\u009f\3\2"+
		"\2\2\u009f\u00a0\3\2\2\2\u00a0\u00ad\7\n\2\2\u00a1\u00a2\7*\2\2\u00a2"+
		"\u00a3\5\26\f\2\u00a3\u00a4\7\n\2\2\u00a4\u00ad\3\2\2\2\u00a5\u00a6\7"+
		"+\2\2\u00a6\u00a7\5\30\r\2\u00a7\u00a8\7\n\2\2\u00a8\u00ad\3\2\2\2\u00a9"+
		"\u00aa\7+\2\2\u00aa\u00ab\7;\2\2\u00ab\u00ad\7\n\2\2\u00acd\3\2\2\2\u00ac"+
		"i\3\2\2\2\u00ac}\3\2\2\2\u00ac\u0087\3\2\2\2\u00ac\u008d\3\2\2\2\u00ac"+
		"\u009c\3\2\2\2\u00ac\u00a1\3\2\2\2\u00ac\u00a5\3\2\2\2\u00ac\u00a9\3\2"+
		"\2\2\u00ad\25\3\2\2\2\u00ae\u00b3\5\32\16\2\u00af\u00b0\7\7\2\2\u00b0"+
		"\u00b1\5\30\r\2\u00b1\u00b2\7\b\2\2\u00b2\u00b4\3\2\2\2\u00b3\u00af\3"+
		"\2\2\2\u00b3\u00b4\3\2\2\2\u00b4\27\3\2\2\2\u00b5\u00b6\b\r\1\2\u00b6"+
		"\u00b7\7\3\2\2\u00b7\u00b8\5\30\r\2\u00b8\u00b9\7\4\2\2\u00b9\u00f5\3"+
		"\2\2\2\u00ba\u00bb\7-\2\2\u00bb\u00bc\5\30\r\2\u00bc\u00bd\7.\2\2\u00bd"+
		"\u00be\5\30\r\2\u00be\u00bf\7/\2\2\u00bf\u00c0\5\30\r\20\u00c0\u00f5\3"+
		"\2\2\2\u00c1\u00c2\7\60\2\2\u00c2\u00cb\7\3\2\2\u00c3\u00c8\5\30\r\2\u00c4"+
		"\u00c5\7\6\2\2\u00c5\u00c7\5\30\r\2\u00c6\u00c4\3\2\2\2\u00c7\u00ca\3"+
		"\2\2\2\u00c8\u00c6\3\2\2\2\u00c8\u00c9\3\2\2\2\u00c9\u00cc\3\2\2\2\u00ca"+
		"\u00c8\3\2\2\2\u00cb\u00c3\3\2\2\2\u00cb\u00cc\3\2\2\2\u00cc\u00cd\3\2"+
		"\2\2\u00cd\u00f5\7\4\2\2\u00ce\u00cf\7,\2\2\u00cf\u00da\7\3\2\2\u00d0"+
		"\u00d5\5\30\r\2\u00d1\u00d2\7\6\2\2\u00d2\u00d4\5\30\r\2\u00d3\u00d1\3"+
		"\2\2\2\u00d4\u00d7\3\2\2\2\u00d5\u00d3\3\2\2\2\u00d5\u00d6\3\2\2\2\u00d6"+
		"\u00d9\3\2\2\2\u00d7\u00d5\3\2\2\2\u00d8\u00d0\3\2\2\2\u00d8\u00d9\3\2"+
		"\2\2\u00d9\u00db\3\2\2\2\u00da\u00d8\3\2\2\2\u00da\u00db\3\2\2\2\u00db"+
		"\u00dc\3\2\2\2\u00dc\u00f5\7\4\2\2\u00dd\u00de\5\32\16\2\u00de\u00df\7"+
		"\7\2\2\u00df\u00e0\5\30\r\2\u00e0\u00e1\7\b\2\2\u00e1\u00f5\3\2\2\2\u00e2"+
		"\u00e3\5\32\16\2\u00e3\u00ec\7\3\2\2\u00e4\u00e9\5\30\r\2\u00e5\u00e6"+
		"\7\6\2\2\u00e6\u00e8\5\30\r\2\u00e7\u00e5\3\2\2\2\u00e8\u00eb\3\2\2\2"+
		"\u00e9\u00e7\3\2\2\2\u00e9\u00ea\3\2\2\2\u00ea\u00ed\3\2\2\2\u00eb\u00e9"+
		"\3\2\2\2\u00ec\u00e4\3\2\2\2\u00ec\u00ed\3\2\2\2\u00ed\u00ee\3\2\2\2\u00ee"+
		"\u00ef\7\4\2\2\u00ef\u00f5\3\2\2\2\u00f0\u00f1\t\3\2\2\u00f1\u00f5\5\30"+
		"\r\n\u00f2\u00f5\t\4\2\2\u00f3\u00f5\5\32\16\2\u00f4\u00b5\3\2\2\2\u00f4"+
		"\u00ba\3\2\2\2\u00f4\u00c1\3\2\2\2\u00f4\u00ce\3\2\2\2\u00f4\u00dd\3\2"+
		"\2\2\u00f4\u00e2\3\2\2\2\u00f4\u00f0\3\2\2\2\u00f4\u00f2\3\2\2\2\u00f4"+
		"\u00f3\3\2\2\2\u00f5\u0109\3\2\2\2\u00f6\u00f7\f\t\2\2\u00f7\u00f8\t\5"+
		"\2\2\u00f8\u0108\5\30\r\n\u00f9\u00fa\f\b\2\2\u00fa\u00fb\t\6\2\2\u00fb"+
		"\u0108\5\30\r\t\u00fc\u00fd\f\7\2\2\u00fd\u00fe\t\7\2\2\u00fe\u0108\5"+
		"\30\r\b\u00ff\u0100\f\6\2\2\u0100\u0101\7\30\2\2\u0101\u0108\5\30\r\7"+
		"\u0102\u0103\f\5\2\2\u0103\u0104\7\31\2\2\u0104\u0108\5\30\r\6\u0105\u0106"+
		"\f\17\2\2\u0106\u0108\7\65\2\2\u0107\u00f6\3\2\2\2\u0107\u00f9\3\2\2\2"+
		"\u0107\u00fc\3\2\2\2\u0107\u00ff\3\2\2\2\u0107\u0102\3\2\2\2\u0107\u0105"+
		"\3\2\2\2\u0108\u010b\3\2\2\2\u0109\u0107\3\2\2\2\u0109\u010a\3\2\2\2\u010a"+
		"\31\3\2\2\2\u010b\u0109\3\2\2\2\u010c\u010d\7:\2\2\u010d\33\3\2\2\2\34"+
		"\37*:=BKSasv\u0083\u0094\u0097\u009e\u00ac\u00b3\u00c8\u00cb\u00d5\u00d8"+
		"\u00da\u00e9\u00ec\u00f4\u0107\u0109";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}