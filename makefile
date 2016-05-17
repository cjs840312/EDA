all : bin obj bin/bmatch
	@echo "\nCompiling complete !!\n"

bin :
	@echo -n " > making directory \"bin\" ...   "
	@mkdir bin
	@echo "Success !!"
obj :
	@echo -n " > making directory \"obj\" ...   "
	@mkdir obj
	@echo "Success !!"

bin/bmatch : obj/main.o obj/cmdPublic.o obj/cmdPrivate.o obj/baseCommand.o obj/key_def.o  obj/help_function.o obj/cmdCommon.o
	@echo -n " > linking object file ...        "
	@g++  $^ -o $@
	@echo "Success !!"

obj/main.o : src/main.cpp src/cmd/cmd.h src/cmd/help_function.h
	@echo -n " > compilng main.cpp ...          "
	@g++ -c $< -o $@
	@echo "Success !!"
	
obj/cmdPublic.o : src/cmd/cmdPublic.cpp src/cmd/key_def.h src/cmd/cmd.h
	@echo -n " > compilng cmdPublic.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/baseCommand.o : src/cmd/baseCommand.cpp src/cmd/key_def.h src/cmd/cmd.h
	@echo -n " > compilng baseCommand.cpp ...   "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/cmdPrivate.o : src/cmd/cmdPrivate.cpp src/cmd/cmd.h
	@echo -n " > compilng cmdPrivate.cpp ...    "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/key_def.o : src/cmd/key_def.cpp src/cmd/key_def.h
	@echo -n " > compilng key_def.cpp ...       "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/help_function.o : src/cmd/help_function.cpp 
	@echo -n " > compilng help_function.cpp ... "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/cmdCommon.o: src/cmd/cmdCommon.cpp src/cmd/cmdCommon.h
	@echo -n " > compilng cmdCommon.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/File.o: src/sat/File.cpp src/sat/File.h
	@echo -n " > compilng File.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/Proof.o: src/sat/Proof.cpp src/sat/Proof.h
	@echo -n " > compilng Proof.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/Solver.o : src/sat/Solver.cpp src/sat/Solver.h
	@echo -n " > compilng Solver.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

clean :
	@echo -n "deleting binary file ...          "
	@rm -f bin/*
	@echo "Success !!"

	@echo -n "deleting object file ...          " 
	@rm -f obj/*
	@echo "Success !!"
