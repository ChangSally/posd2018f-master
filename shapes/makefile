.PHONY: clean

bin/ut_shape: test/ut_shape.cpp src/circle.h src/rectangle.h
	g++ -std=c++11 test/ut_shape.cpp -o bin/ut_shape -lgtest

clean:
	rm bin/ut_shape
