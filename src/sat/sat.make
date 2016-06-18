all : ../../lib/libSat.a

../../lib/libSat.a : ../../obj/File.o ../../obj/Proof.o ../../obj/Solver.o
	@echo -n " > making library libCmd.a ...     "
	@ar -rcs $@ $^
	@echo "Success !!\n"

../../obj/File.o: File.cpp File.h
	@echo -n " > compilng File.cpp ...           "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/Proof.o: Proof.cpp Proof.h Sort.h
	@echo -n " > compilng Proof.cpp ...          "
	@g++ -c $< -o $@
	@echo "Success !!"

../../obj/Solver.o : Solver.cpp Solver.h Sort.h
	@echo -n " > compilng Solver.cpp ...         "
	@g++ -c $< -o $@
	@echo "Success !!"