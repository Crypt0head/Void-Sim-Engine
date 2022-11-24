all: snakegame-build lifegame-build tests-build run-tests

lifegame-build:
	g++ -fdiagnostics-color=always -g -v source/* -o bin/Life.out -lboost_program_options -lpthread

snakegame-build:
	g++ -fdiagnostics-color=always -g -v source/* -o bin/Snake.out -lboost_program_options -lpthread

tests-build:
	g++ -fdiagnostics-color=always -g -v source/V* tests/*.cpp -o bin/test.out -lboost_program_options -lpthread

run-tests: tests-build
	./bin/test.out

run-lifegame: lifegame-build
	./bin/Life.out

run-snakegame: snakegame-build
	./bin/Snake.out

clear-all:
	rm -f bin/*