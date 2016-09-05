all : ../../lib/libGate.a

../../lib/libGate.a : ../../obj/gates.o ../../obj/cmdGate.o ../../obj/parse.o ../../obj/circuit.o \
					 ../../obj/simulate.o ../../obj/match.o ../../obj/sat.o \
								../../obj/pairs.o
	echo -n " > making library libCmd.a ...     "
	ar -rcs $@ $^
	echo "Success !!"

../../obj/gates.o : gates.cpp gate_def.h
	echo -n " > compilng gates.cpp ...          "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/cmdGate.o : cmdGate.cpp cmdGate.h CirMgr.h ../util/help_function.h
	echo -n " > compilng cmdGate.cpp ...        "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/parse.o : parse.cpp CirMgr.h
	echo -n " > compilng parse.cpp ...          "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/circuit.o : circuit.cpp CirMgr.h
	echo -n " > compilng circuit.cpp ...        "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/simulate.o : simulate.cpp CirMgr.h ../util/hash.h
	echo -n " > compilng simulate.cpp ...       "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/match.o : match.cpp CirMgr.h
	echo -n " > compilng match.cpp ...          "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/pairs.o : pairs.cpp CirMgr.h
	echo -n " > compilng pairs.cpp ...          "
	g++ -O3 -c $< -o $@
	echo "Success !!"

../../obj/sat.o : sat.cpp CirMgr.h ../sat/sat.h
	echo -n " > compilng sat.cpp ...            "
	g++ -O3 -c $< -o $@
	echo "Success !!"
