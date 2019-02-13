all: $(patsubst %.cpp, %.out, $(wildcard *.cpp))

%.out: %.cpp Makefile
	g++ $< -o $@ -std=c++11

clean:
	rm *.out