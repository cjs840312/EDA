#include <cstdlib>
#include "cmd.h"
#include "../util/help_function.h"
#include "cassert"

using namespace std;

bool
CmdExec::getParameter(vector<string>& tokens,vector<string>& target, size_t num, string parameter, size_t size)
{
   assert(target.empty());
   if(parameter == "")
   {
      if(tokens.size()>=num)
      {
         for(int i=0; i < num ; i++)
         {
            target.push_back(tokens[0]);
            tokens.erase(tokens.begin());
         }
         return true;
      }   
      else
         errorOption(CMD_OPT_MISSING,"");
   }
   else
   {
      for(int i=0; i < tokens.size() ; i++)
      {
         if(myStrNCmp(parameter, tokens[i], size))
         {  
            if(tokens.size()-1-i >= num)
            {
               for(int j=0; j < num ; j++)
               {
                  target.push_back(tokens[i+1]);
                  tokens.erase(tokens.begin()+i+1);
               }
               return true;
            }
            else
            {
               errorOption(CMD_OPT_MISSING, tokens[tokens.size()-1]);
               break;
            }
         }
      }      
   }

   return false;
}


CmdExecStatus
CmdExec::errorOption(CmdOptionError err, const string& opt) const
{
   switch (err)
   {
      case CMD_OPT_MISSING:
			cerr << "Error: Missing option";
			if (opt.size()) cerr << " after (" << opt << ")";
			cerr << "!!" << endl;
			break;

      case CMD_OPT_EXTRA:
         cerr << "Error: Extra option!! (" << opt << ")" << endl;
     		break;

      case CMD_OPT_ILLEGAL:
         cerr << "Error: Illegal option!! (" << opt << ")" << endl;
      	break;

      case CMD_OPT_FOPEN_FAIL:
         cerr << "Error: cannot open file \"" << opt << "\"!!" << endl;
      	break;

      default:
         cerr << "Error: Unknown option error type!! (" << err << ")" << endl;
      	exit(-1);
   }
   return CMD_EXEC_ERROR;
}
