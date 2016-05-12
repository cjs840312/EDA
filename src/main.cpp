#include <iostream>
#include <stdlib.h>
#include "cmd/cmd.h"
#include "cmd/help_function.h"
using namespace std;

extern bool initCommonCmd();

CmdParser* cmdMgr = new CmdParser("cmd> ");

int main(int argc, char** argv)
{
   ifstream dof;

   if(argc == 4)  // bmatch <cir1.v> <cir2.v> <match.out>
   {
   	 //  TODO...

   	 //  Read circuit


   	//Output
   	if (!cmdMgr->openOutput(argv[2]))
		{
		  cerr << "File \""<<argv[3] <<"\" has already existed !!\n";
		  exit(-1);
		}

		//  Auto process




		cmdMgr->closeOutput();		
		return 0;
   }
   else if (argc == 3)   // -File <doFile>
   {
      if (myStrNCmp("-File", argv[1], 2))
      {
         if (!cmdMgr->openDofile(argv[2]))
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
   
   if (!initCommonCmd())
      return 1;

   system("clear");
   cout<<"********************************************************************************"<<endl
       <<"* Program       : CAD contest                                                  *"<<endl
       <<"* Group         : NTU_LTCP                                                     *"<<endl
       <<"* Author        : Chen, Jia-Shiuan                                             *"<<endl
       <<"* Version       : Alpha                                                        *"<<endl
       <<"* Last modified : 2016.05.11                                                   *"<<endl
       <<"* Description   :                                                              *"<<endl
       <<"********************************************************************************"<<endl;
   CmdExecStatus status = CMD_EXEC_DONE;
   while (status != CMD_EXEC_QUIT) 
   {
      status = cmdMgr->execOneCmd();
      cout << endl;
   }

   return 0;
}