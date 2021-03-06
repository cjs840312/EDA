all : ../../lib/libSat.a

../../lib/libSat.a : ../../obj/File.o ../../obj/Proof.o ../../obj/Solver.o
	@echo -n " > making library libCmd.a ...     "
	@ar -rcs $@ $^
	@echo "Success !!"

../../obj/File.o: File.cpp File.h
	@echo -n " > compilng File.cpp ...           "
	@g++ -O3 -c $< -o $@
	@echo "Success !!"

../../obj/Proof.o: Proof.cpp Proof.h Sort.h
	@echo -n " > compilng Proof.cpp ...          "
	@g++ -O3 -c $< -o $@
	@echo "Success !!"

../../obj/Solver.o : Solver.cpp Solver.h Sort.h
	@echo -n " > compilng Solver.cpp ...         "
	@g++ -O3 -c $< -o $@
	@echo "Success !!"
