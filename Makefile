all:
	g++ -std=c++20 -g ./*.cpp -Wall -Wextra -Werror -O2 -o raytrace;

run:
	./raytrace > outputs/9.4.ppm;

clean:
	rm -f raytrace;