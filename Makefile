clean: clean.c clean.h data_processing.c data_processing.h
	gcc -o clean clean.c data_processing.c