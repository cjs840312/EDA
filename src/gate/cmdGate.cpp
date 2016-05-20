#include <iomanip>
#include <string>
#include <vector>
#include "../util/help_function.h"
#include "cmdGate.h"

using namespace std;

bool
initGateCmd()
{
   if (!(cmdMgr->regCmd("Read"   , 1, new ReadCmd)))
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
      // TODO ...






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
   cout << setw(15) << left << "Read: "
        << "read and parse input file " << endl;
}
