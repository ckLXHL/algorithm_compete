clean:
	rm main

build:
	clang++ *.cpp --std=c++11 -o main

run:build
	./main