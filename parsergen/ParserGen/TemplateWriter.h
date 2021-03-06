#pragma once

#include <HashMap.h>

class TemplateWriter;

class KeywordHandler {
public:
  virtual void handleKeyword(TemplateWriter &writer, String &line) const = 0;
};

class KeywordTrigger {
private:
  String              m_verboseString;
  KeywordHandler     &m_handler;

public:
  KeywordTrigger(KeywordHandler &handler, const String &verboseString);

  inline const KeywordHandler &getHandler() const {
    return m_handler;
  }

  inline const String &getVerboseString() const {
    return m_verboseString;
  }
};

class TemplateWriter {
private:
  String                         m_templateName;
  String                         m_implOutputDir;
  String                         m_headerOutputDir;
  bool                           m_verbose;
  MarginFile                    *m_output;
  StringHashMap<KeywordTrigger*> m_keywords;
  StringHashMap<String>          m_macroes;
  SourcePositionWithName         m_currentPos;
  String getKeyword(const TCHAR *dollar);
  String replaceMacroes(const TCHAR *line);
  void closeOutput();
public:
  TemplateWriter(const String &templateName, const String &implOutputDir, const String &headerOutputDir, bool verbose);
  ~TemplateWriter();
  void addKeywordHandler(const String &keyword, KeywordHandler &handler, const String &verboseString="");
  void addMacro(const String &macro, const String &value);
  void generateOutput();

  inline const String &getImplOutputDir() const {
    return m_implOutputDir;
  }

  inline const String &getHeaderOutputDir() const {
    return m_headerOutputDir;
  }

  inline MarginFile &getOutput() {
    return *m_output;
  }

  inline const SourcePositionWithName &getPos() const {
    return m_currentPos;
  }

  inline int getLineNumber() const {
    return getPos().getLineNumber();
  }

  void openOutput(const String &fileName);
};

class SourceTextWriter : public KeywordHandler {
private:
  SourceText  m_sourceText;
  bool        m_lineDirectives;
  void writeLineDirective(MarginFile &f, int lineNumber);
public:
  SourceTextWriter(const SourceText &sourceText, bool lineDirectives = false);
  void handleKeyword(TemplateWriter &writer, String &line) const;
};

class NewFileHandler : public KeywordHandler {
public:
  void handleKeyword(TemplateWriter &writer, String &line) const;
};

void writeSourceText(   MarginFile &f, const SourceText &sourceText, const SourcePositionWithName &pos, bool lineDirective);
void writeLineDirective(MarginFile &f, const String &sourceName, int lineNumber);
