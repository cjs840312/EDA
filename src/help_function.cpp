#include <string>
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

/*
int myStrNCmp(const string& s1, const string& s2, unsigned n)
{
   assert(n > 0);
   unsigned n2 = s2.size();
   unsigned n1 = s1.size();

   if (n2 == 0) return -1;

   assert(n1 >= n);

   for (unsigned i = 0; i < n1; ++i)
   {
      if (i == n2)
         return (i < n)? 1 : 0;
      char ch1 = (isupper(s1[i]))? tolower(s1[i]) : s1[i];
      char ch2 = (isupper(s2[i]))? tolower(s2[i]) : s2[i];
      if (ch1 != ch2)
         return (ch1 - ch2);
   }
   return (n1 - n2);
}
*/