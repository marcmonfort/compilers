// Generated from /home/hammer/fib-upc/cl/compilers/practica/asl/Asl.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class AslLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		ASSIGN=10, PLUS=11, SUB=12, MUL=13, DIV=14, MOD=15, EQ=16, NEQ=17, GT=18, 
		GTE=19, LT=20, LTE=21, AND=22, OR=23, NOT=24, VAR=25, INT=26, FLOAT=27, 
		BOOL=28, CHAR=29, ARRAY=30, IF=31, THEN=32, ELSE=33, ENDIF=34, WHILE=35, 
		ENDWHILE=36, FUNC=37, ENDFUNC=38, RETURN=39, READ=40, WRITE=41, A_MAX=42, 
		INTVAL=43, FLOATVAL=44, CHARVAL=45, BOOLVAL=46, ID=47, STRING=48, COMMENT=49, 
		WS=50;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
		"ASSIGN", "PLUS", "SUB", "MUL", "DIV", "MOD", "EQ", "NEQ", "GT", "GTE", 
		"LT", "LTE", "AND", "OR", "NOT", "VAR", "INT", "FLOAT", "BOOL", "CHAR", 
		"ARRAY", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "ENDWHILE", "FUNC", "ENDFUNC", 
		"RETURN", "READ", "WRITE", "A_MAX", "INTVAL", "FLOATVAL", "CHARVAL", "BOOLVAL", 
		"ID", "STRING", "ESC_SEQ", "COMMENT", "WS"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'('", "')'", "':'", "','", "'['", "']'", "'of'", "';'", "'do'", 
		"'='", "'+'", "'-'", "'*'", "'/'", "'%'", "'=='", "'!='", "'>'", "'>='", 
		"'<'", "'<='", "'and'", "'or'", "'not'", "'var'", "'int'", "'float'", 
		"'bool'", "'char'", "'array'", "'if'", "'then'", "'else'", "'endif'", 
		"'while'", "'endwhile'", "'func'", "'endfunc'", "'return'", "'read'", 
		"'write'", "'.max'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, "ASSIGN", 
		"PLUS", "SUB", "MUL", "DIV", "MOD", "EQ", "NEQ", "GT", "GTE", "LT", "LTE", 
		"AND", "OR", "NOT", "VAR", "INT", "FLOAT", "BOOL", "CHAR", "ARRAY", "IF", 
		"THEN", "ELSE", "ENDIF", "WHILE", "ENDWHILE", "FUNC", "ENDFUNC", "RETURN", 
		"READ", "WRITE", "A_MAX", "INTVAL", "FLOATVAL", "CHARVAL", "BOOLVAL", 
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


	public AslLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Asl.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\64\u0155\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64"+
		"\t\64\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\b\3\t"+
		"\3\t\3\n\3\n\3\n\3\13\3\13\3\f\3\f\3\r\3\r\3\16\3\16\3\17\3\17\3\20\3"+
		"\20\3\21\3\21\3\21\3\22\3\22\3\22\3\23\3\23\3\24\3\24\3\24\3\25\3\25\3"+
		"\26\3\26\3\26\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\31\3\31\3\31\3\31\3"+
		"\32\3\32\3\32\3\32\3\33\3\33\3\33\3\33\3\34\3\34\3\34\3\34\3\34\3\34\3"+
		"\35\3\35\3\35\3\35\3\35\3\36\3\36\3\36\3\36\3\36\3\37\3\37\3\37\3\37\3"+
		"\37\3\37\3 \3 \3 \3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3#\3#\3#\3#\3#\3"+
		"#\3$\3$\3$\3$\3$\3$\3%\3%\3%\3%\3%\3%\3%\3%\3%\3&\3&\3&\3&\3&\3\'\3\'"+
		"\3\'\3\'\3\'\3\'\3\'\3\'\3(\3(\3(\3(\3(\3(\3(\3)\3)\3)\3)\3)\3*\3*\3*"+
		"\3*\3*\3*\3+\3+\3+\3+\3+\3,\6,\u010a\n,\r,\16,\u010b\3-\6-\u010f\n-\r"+
		"-\16-\u0110\3-\3-\6-\u0115\n-\r-\16-\u0116\3.\3.\3.\5.\u011c\n.\3.\3."+
		"\3/\3/\3/\3/\3/\3/\3/\3/\3/\5/\u0129\n/\3\60\3\60\7\60\u012d\n\60\f\60"+
		"\16\60\u0130\13\60\3\61\3\61\3\61\7\61\u0135\n\61\f\61\16\61\u0138\13"+
		"\61\3\61\3\61\3\62\3\62\3\62\3\63\3\63\3\63\3\63\7\63\u0143\n\63\f\63"+
		"\16\63\u0146\13\63\3\63\5\63\u0149\n\63\3\63\3\63\3\63\3\63\3\64\6\64"+
		"\u0150\n\64\r\64\16\64\u0151\3\64\3\64\2\2\65\3\3\5\4\7\5\t\6\13\7\r\b"+
		"\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26"+
		"+\27-\30/\31\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(O)Q*S"+
		"+U,W-Y.[/]\60_\61a\62c\2e\63g\64\3\2\t\4\2))^^\5\2C\\aac|\6\2\62;C\\a"+
		"ac|\4\2$$^^\n\2$$))^^ddhhppttvv\4\2\f\f\17\17\5\2\13\f\17\17\"\"\2\u015e"+
		"\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2"+
		"\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2"+
		"\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2"+
		"\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2"+
		"\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3"+
		"\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2"+
		"\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2"+
		"U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3"+
		"\2\2\2\2e\3\2\2\2\2g\3\2\2\2\3i\3\2\2\2\5k\3\2\2\2\7m\3\2\2\2\to\3\2\2"+
		"\2\13q\3\2\2\2\rs\3\2\2\2\17u\3\2\2\2\21x\3\2\2\2\23z\3\2\2\2\25}\3\2"+
		"\2\2\27\177\3\2\2\2\31\u0081\3\2\2\2\33\u0083\3\2\2\2\35\u0085\3\2\2\2"+
		"\37\u0087\3\2\2\2!\u0089\3\2\2\2#\u008c\3\2\2\2%\u008f\3\2\2\2\'\u0091"+
		"\3\2\2\2)\u0094\3\2\2\2+\u0096\3\2\2\2-\u0099\3\2\2\2/\u009d\3\2\2\2\61"+
		"\u00a0\3\2\2\2\63\u00a4\3\2\2\2\65\u00a8\3\2\2\2\67\u00ac\3\2\2\29\u00b2"+
		"\3\2\2\2;\u00b7\3\2\2\2=\u00bc\3\2\2\2?\u00c2\3\2\2\2A\u00c5\3\2\2\2C"+
		"\u00ca\3\2\2\2E\u00cf\3\2\2\2G\u00d5\3\2\2\2I\u00db\3\2\2\2K\u00e4\3\2"+
		"\2\2M\u00e9\3\2\2\2O\u00f1\3\2\2\2Q\u00f8\3\2\2\2S\u00fd\3\2\2\2U\u0103"+
		"\3\2\2\2W\u0109\3\2\2\2Y\u010e\3\2\2\2[\u0118\3\2\2\2]\u0128\3\2\2\2_"+
		"\u012a\3\2\2\2a\u0131\3\2\2\2c\u013b\3\2\2\2e\u013e\3\2\2\2g\u014f\3\2"+
		"\2\2ij\7*\2\2j\4\3\2\2\2kl\7+\2\2l\6\3\2\2\2mn\7<\2\2n\b\3\2\2\2op\7."+
		"\2\2p\n\3\2\2\2qr\7]\2\2r\f\3\2\2\2st\7_\2\2t\16\3\2\2\2uv\7q\2\2vw\7"+
		"h\2\2w\20\3\2\2\2xy\7=\2\2y\22\3\2\2\2z{\7f\2\2{|\7q\2\2|\24\3\2\2\2}"+
		"~\7?\2\2~\26\3\2\2\2\177\u0080\7-\2\2\u0080\30\3\2\2\2\u0081\u0082\7/"+
		"\2\2\u0082\32\3\2\2\2\u0083\u0084\7,\2\2\u0084\34\3\2\2\2\u0085\u0086"+
		"\7\61\2\2\u0086\36\3\2\2\2\u0087\u0088\7\'\2\2\u0088 \3\2\2\2\u0089\u008a"+
		"\7?\2\2\u008a\u008b\7?\2\2\u008b\"\3\2\2\2\u008c\u008d\7#\2\2\u008d\u008e"+
		"\7?\2\2\u008e$\3\2\2\2\u008f\u0090\7@\2\2\u0090&\3\2\2\2\u0091\u0092\7"+
		"@\2\2\u0092\u0093\7?\2\2\u0093(\3\2\2\2\u0094\u0095\7>\2\2\u0095*\3\2"+
		"\2\2\u0096\u0097\7>\2\2\u0097\u0098\7?\2\2\u0098,\3\2\2\2\u0099\u009a"+
		"\7c\2\2\u009a\u009b\7p\2\2\u009b\u009c\7f\2\2\u009c.\3\2\2\2\u009d\u009e"+
		"\7q\2\2\u009e\u009f\7t\2\2\u009f\60\3\2\2\2\u00a0\u00a1\7p\2\2\u00a1\u00a2"+
		"\7q\2\2\u00a2\u00a3\7v\2\2\u00a3\62\3\2\2\2\u00a4\u00a5\7x\2\2\u00a5\u00a6"+
		"\7c\2\2\u00a6\u00a7\7t\2\2\u00a7\64\3\2\2\2\u00a8\u00a9\7k\2\2\u00a9\u00aa"+
		"\7p\2\2\u00aa\u00ab\7v\2\2\u00ab\66\3\2\2\2\u00ac\u00ad\7h\2\2\u00ad\u00ae"+
		"\7n\2\2\u00ae\u00af\7q\2\2\u00af\u00b0\7c\2\2\u00b0\u00b1\7v\2\2\u00b1"+
		"8\3\2\2\2\u00b2\u00b3\7d\2\2\u00b3\u00b4\7q\2\2\u00b4\u00b5\7q\2\2\u00b5"+
		"\u00b6\7n\2\2\u00b6:\3\2\2\2\u00b7\u00b8\7e\2\2\u00b8\u00b9\7j\2\2\u00b9"+
		"\u00ba\7c\2\2\u00ba\u00bb\7t\2\2\u00bb<\3\2\2\2\u00bc\u00bd\7c\2\2\u00bd"+
		"\u00be\7t\2\2\u00be\u00bf\7t\2\2\u00bf\u00c0\7c\2\2\u00c0\u00c1\7{\2\2"+
		"\u00c1>\3\2\2\2\u00c2\u00c3\7k\2\2\u00c3\u00c4\7h\2\2\u00c4@\3\2\2\2\u00c5"+
		"\u00c6\7v\2\2\u00c6\u00c7\7j\2\2\u00c7\u00c8\7g\2\2\u00c8\u00c9\7p\2\2"+
		"\u00c9B\3\2\2\2\u00ca\u00cb\7g\2\2\u00cb\u00cc\7n\2\2\u00cc\u00cd\7u\2"+
		"\2\u00cd\u00ce\7g\2\2\u00ceD\3\2\2\2\u00cf\u00d0\7g\2\2\u00d0\u00d1\7"+
		"p\2\2\u00d1\u00d2\7f\2\2\u00d2\u00d3\7k\2\2\u00d3\u00d4\7h\2\2\u00d4F"+
		"\3\2\2\2\u00d5\u00d6\7y\2\2\u00d6\u00d7\7j\2\2\u00d7\u00d8\7k\2\2\u00d8"+
		"\u00d9\7n\2\2\u00d9\u00da\7g\2\2\u00daH\3\2\2\2\u00db\u00dc\7g\2\2\u00dc"+
		"\u00dd\7p\2\2\u00dd\u00de\7f\2\2\u00de\u00df\7y\2\2\u00df\u00e0\7j\2\2"+
		"\u00e0\u00e1\7k\2\2\u00e1\u00e2\7n\2\2\u00e2\u00e3\7g\2\2\u00e3J\3\2\2"+
		"\2\u00e4\u00e5\7h\2\2\u00e5\u00e6\7w\2\2\u00e6\u00e7\7p\2\2\u00e7\u00e8"+
		"\7e\2\2\u00e8L\3\2\2\2\u00e9\u00ea\7g\2\2\u00ea\u00eb\7p\2\2\u00eb\u00ec"+
		"\7f\2\2\u00ec\u00ed\7h\2\2\u00ed\u00ee\7w\2\2\u00ee\u00ef\7p\2\2\u00ef"+
		"\u00f0\7e\2\2\u00f0N\3\2\2\2\u00f1\u00f2\7t\2\2\u00f2\u00f3\7g\2\2\u00f3"+
		"\u00f4\7v\2\2\u00f4\u00f5\7w\2\2\u00f5\u00f6\7t\2\2\u00f6\u00f7\7p\2\2"+
		"\u00f7P\3\2\2\2\u00f8\u00f9\7t\2\2\u00f9\u00fa\7g\2\2\u00fa\u00fb\7c\2"+
		"\2\u00fb\u00fc\7f\2\2\u00fcR\3\2\2\2\u00fd\u00fe\7y\2\2\u00fe\u00ff\7"+
		"t\2\2\u00ff\u0100\7k\2\2\u0100\u0101\7v\2\2\u0101\u0102\7g\2\2\u0102T"+
		"\3\2\2\2\u0103\u0104\7\60\2\2\u0104\u0105\7o\2\2\u0105\u0106\7c\2\2\u0106"+
		"\u0107\7z\2\2\u0107V\3\2\2\2\u0108\u010a\4\62;\2\u0109\u0108\3\2\2\2\u010a"+
		"\u010b\3\2\2\2\u010b\u0109\3\2\2\2\u010b\u010c\3\2\2\2\u010cX\3\2\2\2"+
		"\u010d\u010f\4\62;\2\u010e\u010d\3\2\2\2\u010f\u0110\3\2\2\2\u0110\u010e"+
		"\3\2\2\2\u0110\u0111\3\2\2\2\u0111\u0112\3\2\2\2\u0112\u0114\7\60\2\2"+
		"\u0113\u0115\4\62;\2\u0114\u0113\3\2\2\2\u0115\u0116\3\2\2\2\u0116\u0114"+
		"\3\2\2\2\u0116\u0117\3\2\2\2\u0117Z\3\2\2\2\u0118\u011b\7)\2\2\u0119\u011c"+
		"\5c\62\2\u011a\u011c\n\2\2\2\u011b\u0119\3\2\2\2\u011b\u011a\3\2\2\2\u011c"+
		"\u011d\3\2\2\2\u011d\u011e\7)\2\2\u011e\\\3\2\2\2\u011f\u0120\7v\2\2\u0120"+
		"\u0121\7t\2\2\u0121\u0122\7w\2\2\u0122\u0129\7g\2\2\u0123\u0124\7h\2\2"+
		"\u0124\u0125\7c\2\2\u0125\u0126\7n\2\2\u0126\u0127\7u\2\2\u0127\u0129"+
		"\7g\2\2\u0128\u011f\3\2\2\2\u0128\u0123\3\2\2\2\u0129^\3\2\2\2\u012a\u012e"+
		"\t\3\2\2\u012b\u012d\t\4\2\2\u012c\u012b\3\2\2\2\u012d\u0130\3\2\2\2\u012e"+
		"\u012c\3\2\2\2\u012e\u012f\3\2\2\2\u012f`\3\2\2\2\u0130\u012e\3\2\2\2"+
		"\u0131\u0136\7$\2\2\u0132\u0135\5c\62\2\u0133\u0135\n\5\2\2\u0134\u0132"+
		"\3\2\2\2\u0134\u0133\3\2\2\2\u0135\u0138\3\2\2\2\u0136\u0134\3\2\2\2\u0136"+
		"\u0137\3\2\2\2\u0137\u0139\3\2\2\2\u0138\u0136\3\2\2\2\u0139\u013a\7$"+
		"\2\2\u013ab\3\2\2\2\u013b\u013c\7^\2\2\u013c\u013d\t\6\2\2\u013dd\3\2"+
		"\2\2\u013e\u013f\7\61\2\2\u013f\u0140\7\61\2\2\u0140\u0144\3\2\2\2\u0141"+
		"\u0143\n\7\2\2\u0142\u0141\3\2\2\2\u0143\u0146\3\2\2\2\u0144\u0142\3\2"+
		"\2\2\u0144\u0145\3\2\2\2\u0145\u0148\3\2\2\2\u0146\u0144\3\2\2\2\u0147"+
		"\u0149\7\17\2\2\u0148\u0147\3\2\2\2\u0148\u0149\3\2\2\2\u0149\u014a\3"+
		"\2\2\2\u014a\u014b\7\f\2\2\u014b\u014c\3\2\2\2\u014c\u014d\b\63\2\2\u014d"+
		"f\3\2\2\2\u014e\u0150\t\b\2\2\u014f\u014e\3\2\2\2\u0150\u0151\3\2\2\2"+
		"\u0151\u014f\3\2\2\2\u0151\u0152\3\2\2\2\u0152\u0153\3\2\2\2\u0153\u0154"+
		"\b\64\2\2\u0154h\3\2\2\2\16\2\u010b\u0110\u0116\u011b\u0128\u012e\u0134"+
		"\u0136\u0144\u0148\u0151\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}