#include <cassert>
//#include <cstdlib>
#include "cmd.h"
#include "help_function.h"

using namespace std;

//----------------------------------------------------------------------
//    Member Function for class Parser
//----------------------------------------------------------------------
bool
CmdParser::openDofile(const string& dof)
{
   _dofile = new ifstream(dof.c_str());   
   _dofileStack.push(_dofile);
   if(_dofile->fail() || _dofileStack.size()>10)
   {    
    _dofileStack.pop();
    delete _dofile;
    if(_dofileStack.empty())
      _dofile=0;
    else
      _dofile=_dofileStack.top();
    return false;
   }

   return true;
}

void
CmdParser::closeDofile()
{   
   assert(_dofile != 0);
   _dofileStack.pop();
   _dofile->close();
   delete _dofile;
   if(_dofileStack.empty())
      _dofile=0;
    else
      _dofile=_dofileStack.top();
}

void
CmdParser::closeOutput()
{   
   assert(_MatchOut != 0);
   _MatchOut->close();
   delete _MatchOut;
}

bool
CmdParser::openOutput(const string& out)
{
   fstream f(out.c_str());
   if(f.is_open())
      return false;
   else
   {
      _MatchOut = new ofstream(out.c_str());
      return true;
   }

}

bool
CmdParser::regCmd(const string& cmd, unsigned nCmp, CmdExec* e)
{
  
   // Make sure cmd hasn't been registered and won't cause ambiguity
   string str = cmd;
   unsigned s = str.size();
   if (s < nCmp) return false;
   while (true) 
   {
      if (getCmd(str)) return false;
      if (s == nCmp) break;
      str.resize(--s);
   }
   
   // Change the first nCmp characters to upper case to facilitate
   //    case-insensitive comparison later.
   // The strings stored in _cmdMap are all upper case
   //
   assert(str.size() == nCmp);  // str is now mandCmd
   string& mandCmd = str;
   for (unsigned i = 0; i < nCmp; ++i)
      mandCmd[i] = toupper(mandCmd[i]);
   string optCmd = cmd.substr(nCmp);
   
   assert(e != 0);
   e->setOptCmd(optCmd);
   
   // insert (mandCmd, e) to _cmdMap; return false if insertion fails.
   return (_cmdMap.insert(CmdRegPair(mandCmd, e))).second;
}

// Return false on "quit" or if excetion happens
CmdExecStatus
CmdParser::execOneCmd()
{
   bool newCmd = false;
   if (_dofile != 0)
      newCmd = readCmd(*_dofile);
   else
      newCmd = readCmd(cin);

   // execute the command
   if (newCmd) 
   {
      string option;

      cout<<endl;

      CmdExec* e = parseCmd(option);
      if (e != 0)
         return e->exec(option);
   }
   return CMD_EXEC_NOP;
}

void
CmdParser::printHelps() const
{
  for(CmdMap::const_iterator it=_cmdMap.begin();it!=_cmdMap.end();it++)
    (*it).second->help();
}

void
CmdParser::printHistory(int nPrint) const
{
   assert(_tempCmdStored == false);
   
   if (_history.empty()) 
     cout << "Empty command history!!" << endl;
   
   int s = _history.size();
   if ((nPrint < 0) || (nPrint > s))
      nPrint = s;
   for (int i = s - nPrint; i < s; ++i)
      cout << "   " << i << ": " << _history[i] << endl;
}

CmdExec*
CmdParser::parseCmd(string& option)
{
    
   assert(_tempCmdStored == false);
   assert(!_history.empty());
   string str = _history.back();
   assert(str[0] != 0 && str[0] != ' ');
   
   string cmd;
   size_t rest_pos=myStrGetTok(str,cmd);
   
   if(rest_pos!=string::npos)
     option=str.substr(rest_pos);
     
   CmdExec* e=getCmd(cmd);
   
   if(e==0) { cerr<<"Illegal command!! \""<<cmd<<"\""<<endl; }
   
   return e;
}

CmdExec*
CmdParser::getCmd(string cmd)
{
	CmdExec* e = 0;

  string mandCmd=cmd;
  for(int i=0;i<cmd.size();i++)
     mandCmd[i]=toupper(mandCmd[i]);

  while(!mandCmd.empty())
  {
    CmdMap::iterator it=_cmdMap.find(mandCmd);
    if(it!=_cmdMap.end())
    {
      string rc=(*it).first+(*it).second->getOptCmd(); 
      if(myStrNCmp(rc, cmd, mandCmd.size()))
      {
        e = (*it).second;
        break;
      }
      else
        return 0;
    }
    mandCmd.resize(mandCmd.size()-1);
  }
  return e;
   
}
