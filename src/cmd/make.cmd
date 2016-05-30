all : ../../lib/libCmd.a

../../lib/libCmd.a : ../../obj/cmdPublic.o ../../obj/baseCommand.o ../../obj/cmdPrivate.o ../../obj/key_def.o ../../obj/cmdCommon.o
	echo -n " > making library libCmd.a ...     "
	ar -rcs $@ $^
	echo "Success !!\n"

../../obj/cmdPublic.o : cmdPublic.cpp key_def.h cmd.h ../util/help_function.h
	echo -n " > compilng cmdPublic.cpp ...      "
	g++ -c $< -o $@
	echo "Success !!"

../../obj/baseCommand.o : baseCommand.cpp key_def.h cmd.h
	echo -n " > compilng baseCommand.cpp ...    "
	g++ -c $< -o $@
	echo "Success !!"

../../obj/cmdPrivate.o : cmdPrivate.cpp cmd.h ../util/help_function.h
	echo -n " > compilng cmdPrivate.cpp ...     "
	g++ -c $< -o $@
	echo "Success !!"

../../obj/key_def.o : key_def.cpp key_def.h
	echo -n " > compilng key_def.cpp ...        "
	g++ -c $< -o $@
	echo "Success !!"

../../obj/cmdCommon.o: cmdCommon.cpp cmdCommon.h ../util/myUsage.h
	echo -n " > compilng cmdCommon.cpp ...      "
	g++ -c $< -o $@
	echo "Success !!"
