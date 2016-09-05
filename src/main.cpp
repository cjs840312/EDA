
#include <iostream>
#include <stdlib.h>
#include "cmd/cmd.h"
#include "util/help_function.h"
#include "util/myUsage.h"
#include "gate/CirMgr.h"
using namespace std;

extern bool initCommonCmd();
extern bool initGateCmd();

CmdParser* cmdMgr = new CmdParser("cmd> ");
MyUsage* myusage;
CirMgr* cirMgr = new CirMgr();

int main(int argc, char** argv)
{
   ifstream dof;

   if(argc == 4)  // bmatch <cir1.v> <cir2.v> <match.out>
   {
     //  Read circuit

      cirMgr= new CirMgr();
      
      ifstream fin1( argv[1]);
      if( !fin1.is_open() || !cirMgr->parse(fin1,1))
      {
         cout<<"Read input file 1 \""<<argv[1]<<"\" failed" << endl;
         return 1;
      }
      
      cout << "Read input file 1 \""<<argv[1]<<"\" successfully" << endl;

      ifstream fin2( argv[2]);
      if( !fin2.is_open() || !cirMgr->parse(fin2,2))
      {
         cout<<"Read input file 2 \""<<argv[2]<<"\" failed" << endl;
         return 1;
      }

      cout << "Read input file 2 \""<<argv[2]<<"\" successfully" << endl;

      cirMgr->set_output(string(argv[3]));
      cirMgr->GO();

      

    //Output
    /*
    if (!cmdMgr->openOutput(argv[2]))
    {
      cerr << "File \""<<argv[3] <<"\" has already existed !!\n";
      exit(-1);
    }
    cmdMgr->closeOutput();    
    */
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
   
   if (!initCommonCmd() || !initGateCmd())
   {
      cerr << "Registering \"init\" commands fails... exiting" << endl;
      return 1;
   }

   system("clear");
   cout<<"********************************************************************************"<<endl
       <<"* Program       : CAD contest - NP3                                            *"<<endl
       <<"* Group         : NTU_LTCP                                                     *"<<endl
       <<"* Author        : J.S Chen , C.Y Peng , C.W Tsai , D.Y Liu                     *"<<endl
       <<"* Version       : Alpha                                                        *"<<endl
       <<"* Last modified : 2016.06.03                                                   *"<<endl
       <<"* Description   :                                                              *"<<endl
       <<"********************************************************************************"<<endl;

   myusage = new MyUsage();
   
   CmdExecStatus status = CMD_EXEC_DONE;
   while (status != CMD_EXEC_QUIT) 
   {
      myusage->start();
      status = cmdMgr->execOneCmd();
      cout << endl;
      myusage->stop();
   }

   return 0;
}
