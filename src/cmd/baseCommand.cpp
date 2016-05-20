#include <cstdlib>
#include "cmd.h"
#include "../util/help_function.h"
#include "cassert"

using namespace std;

int
CmdExec::myStr2Tok(const string& s, vector<string>& tokens)
{
   string token;
   size_t pos = myStrGetTok(s, token);
   while (token.size())
   {
      tokens.push_back(token);
      pos = myStrGetTok(s, token, pos);
   }
   
   return tokens.size();
}

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
                  target.push_back(tokens[i]);
                  tokens.erase(tokens.begin()+i);
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

/*
bool
CmdExec::lexSingleOption
(const string& option, string& token, bool optional) const
{
   size_t n = myStrGetTok(option, token);
   if (!optional) 
   {
      if (token.size() == 0) 
      {
         errorOption(CMD_OPT_MISSING, "");
         return false;
      }
   }

   if (n != string::npos)
   {
      errorOption(CMD_OPT_EXTRA, option.substr(n));
      return false;
   }
   return true;
}

// if nOpts is specified (!= 0), the number of tokens must be exactly = nOpts
// Otherwise, return false.
//
bool
CmdExec::lexOptions
(const string& option, vector<string>& tokens, size_t nOpts) const
{
   string token;
   size_t n = myStrGetTok(option, token);
   while (token.size())
   {
      tokens.push_back(token);
      n = myStrGetTok(option, token, n);
   }
   if (nOpts != 0) 
   {
      if (tokens.size() < nOpts)
      {
         errorOption(CMD_OPT_MISSING, "");
         return false;
      }
      if (tokens.size() > nOpts)
      {
         errorOption(CMD_OPT_EXTRA, tokens[nOpts]);
         return false;
      }
   }
   return true;
}*/

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