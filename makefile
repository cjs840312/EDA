all : mkdir bin/cmd

mkdir :
	mkdir -p bin
	mkdir -p obj

bin/cmd : obj/main.o obj/cmdReader.o obj/key_def.o  obj/help_function.o
	g++ obj/main.o obj/key_def.o obj/cmdReader.o obj/help_function.o -o $@

obj/main.o : src/main.cpp src/cmdReader.h src/help_function.h
	g++ -c $< -o $@

obj/cmdReader.o : src/cmdReader.cpp src/key_def.h src/cmdReader.h 
	g++ -c $< -o $@

obj/key_def.o : src/key_def.cpp src/key_def.h
	g++ -c $< -o $@

obj/help_function.o: src/help_function.cpp 
	g++ -c $< -o $@
clean :
	rm -f bin/* obj/* 
