# TODO: Write a window makefile script
unixall:
	mkdir -p bin
	g++ main.cpp funcs.cpp -o bin/calcpp -std=c++11
	./bin/calcpp


