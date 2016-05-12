#ifndef HELP_H
#define HELP_H

using namespace std;

int myStrNCmp(const string&, const string&, unsigned);
size_t myStrGetTok(const string&, string& , size_t=0,const char=' ');
//int myStr2Tok(const string& , vector<string>& , int=0);
bool myStr2Int(const string& , int& );
bool isValidVarName(const string& );


#endif