all : dir bin/bmatch
	@echo "\nCompile complete !!\n"

dir :
	@echo    " > checking directories ...        "
	@mkdir -p bin obj lib output

bin/bmatch : obj/main.o library
	@echo -n " > linking object file ...         "
	@g++  $< -o $@  -Llib -lCmd -lSat -lGate
	@echo "Success !!"

obj/main.o : src/main.cpp src/cmd/cmd.h src/util/help_function.h src/util/myUsage.h src/gate/CirMgr.h
	@echo -n " > compilng main.cpp ...           "
	@g++ -c $< -o $@
	@echo "Success !!"

library :
	@echo    " > checking libCmd.a ...           "
	@cd src/cmd ;make -f make.cmd --no-print-directory --silent;

	@echo    " > checking libSat.a ...           "
	@cd src/sat ;make -f make.sat --no-print-directory --silent;

	@echo    " > checking libGate.a ...          "
	@cd src/gate ;make -f make.gate --no-print-directory --silent;

clean :
	@echo -n "cleaning bin/ obj/ lib/ ...        "
	@rm -f bin/* obj/* lib/*
	@echo "Success !!"
