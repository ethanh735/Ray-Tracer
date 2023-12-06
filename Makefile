all:
	g++ -std=c++20 -g ./*.cpp -Wall -o raytrace;

run:
	./raytrace;

clean:
	rm -f raytrace;
