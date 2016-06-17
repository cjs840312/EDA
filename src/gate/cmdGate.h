#ifndef CMD_GATE_H
#define CMD_GATE_H

#include "../cmd/cmd.h"

CmdClass(ReadCmd);
CmdClass(PrintCmd);
CmdClass(OptimizeCmd);
CmdClass(SimulateCmd);
CmdClass(MatchCmd);
CmdClass(FECgroupCmd);

#endif 
