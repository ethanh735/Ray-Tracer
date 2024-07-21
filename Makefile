all:
	g++ -std=c++20 -g ./*.cpp -Wall -O2 -o raytrace;

run:
	./raytrace > outputs/11.5.ppm;

clean:
	rm -f raytrace;