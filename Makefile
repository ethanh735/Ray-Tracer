all:
	g++ -std=c++20 -g ./*.cpp -Wall -Wextra -Werror -o raytrace;

run:
	./raytrace > outputs/7.ppm;

clean:
	rm -f raytrace;