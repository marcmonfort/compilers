
// Generated from Asl.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, ASSIGN = 10, PLUS = 11, SUB = 12, MUL = 13, DIV = 14, 
    MOD = 15, EQ = 16, NEQ = 17, GT = 18, GTE = 19, LT = 20, LTE = 21, AND = 22, 
    OR = 23, NOT = 24, VAR = 25, INT = 26, FLOAT = 27, BOOL = 28, CHAR = 29, 
    ARRAY = 30, IF = 31, THEN = 32, ELSE = 33, ENDIF = 34, WHILE = 35, ENDWHILE = 36, 
    FUNC = 37, ENDFUNC = 38, RETURN = 39, READ = 40, WRITE = 41, MAX = 42, 
    FOR = 43, IN = 44, RANGE = 45, ENDFOR = 46, A_MAX = 47, INTVAL = 48, 
    FLOATVAL = 49, CHARVAL = 50, BOOLVAL = 51, ID = 52, STRING = 53, COMMENT = 54, 
    WS = 55
  };

  AslLexer(antlr4::CharStream *input);
  ~AslLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

