
main: main.cc wait.hh
	g++ main.cc -o main -std=c++17

clean:
	rm main *.o
