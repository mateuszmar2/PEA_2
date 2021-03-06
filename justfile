alias r := run
alias b := build

# only run
run:
    rlwrap ./Main

# compile and run
build:
	clear
	g++ -o Main Main.cpp Towns.cpp Simulated_Annealing.cpp Tabu_Search.cpp TSP_Algorithm.cpp -O2
	just run

# run with valgrind
valgrind:
	clear
	g++ -g -o Main Main.cpp Towns.cpp Simulated_Annealing.cpp Tabu_Search.cpp TSP_Algorithm.cpp -Wall
	valgrind --track-origins=yes ./Main

# run with valgrind and full check for leak
valgrindleak:
	clear
	g++ -g -o Main Main.cpp Towns.cpp Simulated_Annealing.cpp Tabu_Search.cpp TSP_Algorithm.cpp -Wall
	valgrind --leak-check=full ./Main