#ifndef CMD_READER_H
#define CMD_READER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include "key_def.h"
using namespace std;

//----------------------------------------------------------------------
//    Forward Declaration
//----------------------------------------------------------------------

class CmdExec;
class CmdParser;

//----------------------------------------------------------------------
//    External declaration
//----------------------------------------------------------------------
extern CmdParser* cmdMgr;

//----------------------------------------------------------------------
//    command execution status
//----------------------------------------------------------------------
enum CmdExecStatus
{
   CMD_EXEC_DONE  = 0,
   CMD_EXEC_ERROR = 1,
   CMD_EXEC_QUIT  = 2,
   CMD_EXEC_NOP   = 3
};

enum CmdOptionError
{
   CMD_OPT_MISSING    = 0,
   CMD_OPT_EXTRA      = 1,
   CMD_OPT_ILLEGAL    = 2,
   CMD_OPT_FOPEN_FAIL = 3
};


//----------------------------------------------------------------------
//    Base class : CmdExec
//----------------------------------------------------------------------

class CmdExec
{
public:
   CmdExec() {}
   virtual ~CmdExec() {}

   virtual CmdExecStatus exec(const string&) = 0;
   virtual void usage(ostream&) const = 0;
   virtual void help() const = 0;

   void setOptCmd(const string& str) { _optCmd = str; }
   const string& getOptCmd() const { return _optCmd; }

protected:
   int myStr2Tok(const string& s, vector<string>& tokens);
   bool getParameter(vector<string>&, vector<string>&, string="", size_t=0, size_t=0);
/*   bool lexSingleOption(const string&, string&, bool = true) const;
   bool lexOptions(const string&, vector<string>&, size_t = 0) const;
*/
   CmdExecStatus errorOption(CmdOptionError , const string&) const;

private:
   string            _optCmd;
};

#define CmdClass(T)                           \
class T: public CmdExec                       \
{                                             \
public:                                       \
   T() {}                                     \
   ~T() {}                                    \
   CmdExecStatus exec(const string& option);  \
   void usage(ostream& os) const;             \
   void help() const;                         \
}                                             \


//----------------------------------------------------------------------
//    Base class : CmdParser
//----------------------------------------------------------------------


class CmdParser
{

typedef map<const string, CmdExec*>   CmdMap;
typedef pair<const string, CmdExec*>  CmdRegPair;

#define READ_BUF_SIZE    65536
#define TAB_POSITION     8
#define PG_OFFSET        10

public:
   CmdParser(const string& p) : 
        _prompt(p), 
        _dofile(0),
        _readBufPtr(_readBuf),
        _readBufEnd(_readBuf),
        _historyIdx(0),
        _tempCmdStored(false){}
  ~CmdParser() {}

   bool openDofile(const string& dof);
   void closeDofile();

   bool regCmd(const string&, unsigned, CmdExec*);
   CmdExec* getCmd(string);
   CmdExecStatus execOneCmd();
   
   void printHelps() const;
   void printHistory(int nPrint = -1) const;
   

private:
  
   void resetBufAndPrintPrompt()
   {
    _readBufPtr = _readBufEnd = _readBuf;
    *_readBufPtr = 0;
    printPrompt();
   }
   void printPrompt() const { cout << _prompt; }
   
   bool readCmd(istream&);
   CmdExec* parseCmd(string&);
   void listCmd(const string&);
   void reprintCmd();
   
   bool moveBufPtr(char* const);
   bool deleteChar();
   void insertChar(char, int = 1);
   void deleteLine();
   void moveToHistory(int index);
   void addHistory();
   void retrieveHistory();

   // Data members
   char             _readBuf[READ_BUF_SIZE]; // save the current line input
                                             // be consistent as shown on the screen
   char*            _readBufPtr;             // point to the cursor position
                                             // also be the insert and delete point
   char*            _readBufEnd;             // end of string position of _readBuf
                                             // make sure *_readBufEnd = 0
   const            string _prompt;          // command prompt
   
   ifstream*        _dofile;                 // for command script
   CmdMap           _cmdMap;                 // map from string to command
   stack<ifstream*> _dofileStack;            // For recursive dofile calling
   vector<string>   _history;                // oldest:_history[0],latest:_hist.back()
   int              _historyIdx;             // (1) Position to insert history string
                                             //     i.e. _historyIdx = _history.size()
                                             // (2) When up/down/pgUp/pgDn is pressed,
                                             //     position to history to retrieve
   bool             _tempCmdStored;          // When up/pgUp is pressed, current line
                                             // will be stored in _history and
                                             // _tempCmdStored will be true.
                                             // Reset to false when new command added
};
#endif // CMD_PARSER_H
