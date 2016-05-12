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
obj/main.o : src/main.cpp src/cmd.h src/help_function.h
	@echo -n " > compilng main.cpp ...          "
	@g++ -c $< -o $@
	@echo "Success !!"
obj/cmdPublic.o : src/cmdPublic.cpp src/key_def.h src/cmd.h
	@echo -n " > compilng cmdPublic.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/baseCommand.o : src/baseCommand.cpp src/key_def.h src/cmd.h
	@echo -n " > compilng baseCommand.cpp ...   "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/cmdPrivate.o : src/cmdPrivate.cpp src/cmd.h
	@echo -n " > compilng cmdPrivate.cpp ...    "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/key_def.o : src/key_def.cpp src/key_def.h
	@echo -n " > compilng key_def.cpp ...       "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/help_function.o : src/help_function.cpp 
	@echo -n " > compilng help_function.cpp ... "
	@g++ -c $< -o $@
	@echo "Success !!"

obj/cmdCommon.o: src/cmdCommon.cpp src/cmdCommon.h
	@echo -n " > compilng cmdCommon.cpp ...     "
	@g++ -c $< -o $@
	@echo "Success !!"

clean :
	@echo -n "deleting binary file ...          "
	@rm -f bin/*
	@echo "Success !!"

	@echo -n "deleting object file ...          " 
	@rm -f obj/*
	@echo "Success !!"
