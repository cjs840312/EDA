all : dir bin/bmatch
	@echo "Compile complete !!"

dir :
	@echo    "checking directories ..."
	@mkdir -p bin obj lib output

bin/bmatch : library obj/main.o obj/help_function.o
	@echo -n " > linking object file ...         "
	@g++ -O3  -o $@ obj/main.o obj/help_function.o -Llib -lGate -lCmd -lSat
	@echo "Success !!"

obj/main.o : src/main.cpp src/cmd/cmd.h src/util/help_function.h src/util/myUsage.h src/gate/CirMgr.h
	@echo -n " > compilng main.cpp ...           "
	@g++ -O3 -c $< -o $@
	@echo "Success !!"


obj/help_function.o : src/util/help_function.cpp 
	@echo -n " > compilng help_function.cpp ...  "
	@g++ -O3 -c $< -o $@
	@echo "Success !!"

library :
	@echo    "checking libCmd.a ...           "
	@cd src/cmd ;make -f cmd.make --no-print-directory --silent;

	@echo    "checking libSat.a ...           "
	@cd src/sat ;make -f sat.make --no-print-directory --silent;

	@echo    "checking libGate.a ...          "
	@cd src/gate ;make -f gate.make --no-print-directory --silent;

clean :
	@echo -n "cleaning bin/ obj/ lib/ ...        "
	@rm -f bin/* obj/* lib/*
	@echo "Success !!"
