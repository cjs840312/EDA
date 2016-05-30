#include <iomanip>
#include <cstring>
#include <vector>
#include "../util/help_function.h"
#include "cmdGate.h"
#include "CirMgr.h"

using namespace std;

extern CirMgr* cirMgr;

bool
initGateCmd()
{
   if ( !(cmdMgr->regCmd("Read" , 1, new ReadCmd)) ||
        !(cmdMgr->regCmd("Print" , 1, new PrintCmd))     )
      return false;
   return true;
}


//----------------------------------------------------------------------
//    Read < string File1 > < string File2 >
//----------------------------------------------------------------------
CmdExecStatus
ReadCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>2)
      return errorOption(CMD_OPT_EXTRA, tokens[2]);
   else if(getParameter(tokens, target, 2))
   {
      delete cirMgr;
      cirMgr= new CirMgr();

      ifstream fin1( target[0].c_str());
      if( !fin1.is_open() || !cirMgr->parse(fin1,1))
      {
         cout<<"Read input file 1 \""<<target[0]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }
      
      cout << "Read input file 1 \""<<target[0]<<"\" successfully" << endl;

      ifstream fin2( target[1].c_str());
      if( !fin2.is_open() || !cirMgr->parse(fin2,2))
      {
         cout<<"Read input file 2 \""<<target[1]<<"\" failed" << endl;
         return CMD_EXEC_ERROR;
      }

      cout << "Read input file 2 \""<<target[1]<<"\" successfully" << endl;
   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
ReadCmd::usage(ostream& os) const
{
   os << "Usage: Read < string File1 > < string File2 >" << endl;
}

void
ReadCmd::help() const
{
   cout << setw(10) << left << "Read"
        << ": read and parse input file " << endl;
}


//----------------------------------------------------------------------
//    Print [ 1 | 2 ]
//----------------------------------------------------------------------
CmdExecStatus
PrintCmd::exec(const string& option)
{
   vector<string> tokens,target ;
   myStr2Tok(option,tokens);

   if(tokens.size()>1)
      return errorOption(CMD_OPT_EXTRA, tokens[1]);
   else if(tokens.empty())
   {
      cirMgr->printcircuit(1);
      cout<<endl;
      cirMgr->printcircuit(2);
   }
   else if(getParameter(tokens, target))
   {
      if(myStrNCmp("1",target[0],1))
         cirMgr->printcircuit(1);
      else if(myStrNCmp("2",target[0],1))
         cirMgr->printcircuit(2);
      else
         return errorOption( CMD_OPT_ILLEGAL,target[0] );
   }
   else
      return CMD_EXEC_ERROR;
   return CMD_EXEC_DONE;
}

void
PrintCmd::usage(ostream& os) const
{
   os << "Usage: Print [ 1 | 2 ]" << endl;
}

void
PrintCmd::help() const
{
   cout << setw(10) << left << "Print"
        << ": print the DFS list of the circuit(s) " << endl;
}