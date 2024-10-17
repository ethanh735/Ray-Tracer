SRCS = $(shell find ./ -type f -name *.cpp)

all:
	g++ -std=c++20 -g $(SRCS) -Wall -O2 -o raytrace;

run:
	./raytrace > outputs/book2/2.6.ppm;

clean:
	rm -f raytrace;
