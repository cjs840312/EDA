#include <iostream>
#include <termios.h>
#include <stdlib.h>
#include "cmdReader.h"
#include "help_function.h"

using namespace std;

int main(int argc, char** argv)
{
   CmdParser cmd;
   ifstream dof;

   if (argc == 3)   // -File <doFile>
   {
      if (myStrNCmp("-File", argv[1], 2))
      {
         if (!cmd.openDofile(argv[2]))
         {
            cerr << "Error: cannot open file \"" << argv[2] << "\"!!\n";
            exit(-1);
         }
      }
      else {
         cerr << "Error: unknown argument \"" << argv[1] << "\"!!\n";
         exit(-1);
      }
   }
   else if (argc != 1)
   {
      cerr << "Error: illegal number of argument (" << argc << ")!!\n";
      exit(-1);
   }
   
   cmd.readCmd();  // press "Ctrl-d" to break
   cout << endl;  // a blank line between each command

   return 0;
}