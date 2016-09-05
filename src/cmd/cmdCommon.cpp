#include <iomanip>
#include <string>
#include <vector>
#include "../util/help_function.h"
#include "cmdCommon.h"
#include "../util/myUsage.h"

using namespace std;

extern MyUsage* myusage;

bool
initCommonCmd()
{
   if (!(cmdMgr->regCmd("Quit"   , 1, new QuitCmd)       &&
         cmdMgr->regCmd("HIStory", 3, new HistoryCmd)    &&
         cmdMgr->regCmd("HELp"   , 3, new HelpCmd)       &&
         cmdMgr->regCmd("DOfile" , 2, new DofileCmd)     &&    
         cmdMgr->regCmd("Usage"  , 1, new UsageCmd)         ))     
      return false;
   return true;
}


//----------------------------------------------------------------------
//    HELp [(string cmd)]
//----------------------------------------------------------------------
CmdExecStatus
HelpCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>1)
      return errorOption(CMD_OPT_EXTRA, tokens[1]);
   else if(tokens.empty())
      cmdMgr->printHelps();
   else if(getParameter(tokens, target))
   {
      CmdExec* e = cmdMgr->getCmd(target[0]);
      if (!e) 
         return errorOption(CMD_OPT_ILLEGAL, target[0]);
      e->usage(cout);
   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
HelpCmd::usage(ostream& os) const
{
   os << "Usage: HELp [(string cmd)]" << endl;
}

void
HelpCmd::help() const
{
   cout << setw(10) << left << "HELp"
        << ": print this help message" << endl;
}

//----------------------------------------------------------------------
//    Quit [-Force]
//----------------------------------------------------------------------
CmdExecStatus
QuitCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>1)
      return errorOption(CMD_OPT_EXTRA, tokens[1]);
   else if(tokens.empty())
   {
      cout << "Are you sure to quit (Yes/No)? ";
      char str[1024];
      cin.getline(str, 1024);
      string ss = string(str);
      size_t s = ss.find_first_not_of(' ', 0);
      if (s != string::npos)
      {
         ss = ss.substr(s);
         if (myStrNCmp("Yes", ss, 1))
            return CMD_EXEC_QUIT;  // ready to quit
         else if (!myStrNCmp("No", ss, 1))      
            cout<<"Error: Illegal command!! "<<endl;
      }
   }
   else if(getParameter(tokens, target))
   {
      if (!myStrNCmp("-Forced", target[0], 2))
         return errorOption(CMD_OPT_ILLEGAL, target[0]);
      else
         return CMD_EXEC_QUIT;  // ready to quit
   }
   else
      return CMD_EXEC_ERROR;

   return CMD_EXEC_DONE;   
}

void
QuitCmd::usage(ostream& os) const
{
   os << "Usage: Quit [-Force]" << endl;
}

void
QuitCmd::help() const
{
   cout << setw(10) << left << "Quit"
        << ": quit the execution" << endl;
}

//----------------------------------------------------------------------
//    HIStory [(int nPrint)]
//----------------------------------------------------------------------
CmdExecStatus
HistoryCmd::exec(const string& option)
{
   vector<string> tokens,target ;   
   myStr2Tok(option,tokens);
   int nPrint = -1;

   if(tokens.size()>1)
      return errorOption(CMD_OPT_EXTRA, tokens[1]);
   else if(tokens.empty())
      cmdMgr->printHistory();
   else if(getParameter(tokens, target))
   {
      if (!myStr2Int(target[0], nPrint))
         return errorOption(CMD_OPT_ILLEGAL, target[0]);
      else
         cmdMgr->printHistory(nPrint);
   }
   else
      return CMD_EXEC_ERROR;

   return CMD_EXEC_DONE;
}

void
HistoryCmd::usage(ostream& os) const
{
   os << "Usage: HIStory [(int nPrint)]" << endl;
}

void
HistoryCmd::help() const
{
   cout << setw(10) << left << "HIStory"
        << ": print command history" << endl;
}


//----------------------------------------------------------------------
//    DOfile <(string file)>
//----------------------------------------------------------------------
// TODO: You DON'T need to modify this function!
//       But you should modify CmdParser::openDofile(), etc, in order
//       to support the following features.
//
// Supported features
// (1) mcalc> dofile do1
//     mcalc> ...        <== some other commands
//     mcalc> dofile do2 <== there is a "dofile do1" in do2
//     mcalc>          
// (2) mcalc> dofile t
//     Error: cannot open file "t"!!
//     mcalc> dofile do <== can open a dofile "do" after failing to open "t"
//     mcalc>          
// (3) If a dofile xx contains a line "dofile xx" calling itself,
//     where xx may or may not exist...  (recursive dofiles)
//     (Let the max recursion depth = 1024)
//
CmdExecStatus
DofileCmd::exec(const string& option)
{     
   vector<string> tokens,target ;   
   myStr2Tok(option,tokens);
   int nPrint = -1;

   if(tokens.size()>1)
      return errorOption(CMD_OPT_EXTRA, tokens[1]);
   else if(getParameter(tokens, target))
   {
      if (!cmdMgr->openDofile(target[0]))
         return errorOption(CMD_OPT_FOPEN_FAIL, target[0]);
   }
   else
      return CMD_EXEC_ERROR;

   return CMD_EXEC_DONE;
}

void
DofileCmd::usage(ostream& os) const
{  
   os << "Usage: DOfile <(string file)>" << endl;
}  
      
void
DofileCmd::help() const
{
   cout << setw(10) << left << "DOfile"
        << ": execute the commands in the dofile" << endl;
}


//----------------------------------------------------------------------
//    Usage [ -Time | -Memory ]
//----------------------------------------------------------------------
CmdExecStatus
UsageCmd::exec(const string& option)
{
   
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>1)
      return errorOption(CMD_OPT_EXTRA, tokens[1]);
   else if(tokens.empty())
      myusage->report(true,true);
   else if(getParameter(tokens, target))
   {
      if (myStrNCmp("-Time", target[0], 2))
         myusage->report(true,false);
      else if(myStrNCmp("-Memory", target[0], 2))
         myusage->report(false,true);
   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
UsageCmd::usage(ostream& os) const
{
   os << "Usage: Usage [ -Time | -Memory ]" << endl;
}

void
UsageCmd::help() const
{
   cout << setw(10) << left << "Usage"
        << ": show time and memory usage" << endl;
}
