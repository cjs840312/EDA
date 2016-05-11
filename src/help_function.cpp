#include <string>
#include <vector>
#include <cassert>
using namespace std;
 
bool myStrNCmp(const string& s1, const string& s2, unsigned n)
{
   assert(n > 0);
   unsigned n2 = s2.size();
   unsigned n1 = s1.size();

   if (n2 == 0 || n2>n1 )
      return false;

   assert(n1 >= n);

   for (unsigned i = 0; i < n1; ++i)
   {
      if (i == n2)
         return i >= n ;
      char ch1 = (isupper(s1[i]))? tolower(s1[i]) : s1[i];
      char ch2 = (isupper(s2[i]))? tolower(s2[i]) : s2[i];
      if (ch1 != ch2)
         return false;
   }
   return true;
}

size_t myStrGetTok(const string& str, string& tok, size_t pos=0,const char del=' ')
{
   size_t begin = str.find_first_not_of(del, pos);
   if (begin == string::npos) { tok = ""; return begin; }
   size_t end = str.find_first_of(del, begin);
   tok = str.substr(begin, end - begin);
   return end;
}

// Convert string "str" to integer "num". Return false if str does not appear
// to be a number
bool myStr2Int(const string& str, int& num)
{
   num = 0;
   size_t i = 0;
   int sign = 1;
   if (str[0] == '-') { sign = -1; i = 1; }
   bool valid = false;
   for (; i < str.size(); ++i) 
   {
      if (isdigit(str[i])) 
      {
         num *= 10;
         num += int(str[i] - '0');
         valid = true;
      }
      else return false;
   }
   num *= sign;
   return valid;
}