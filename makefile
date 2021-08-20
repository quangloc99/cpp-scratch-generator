CPP=g++
FLAGS=--std=c++11

clean:
	rm -rf build/*
	rm -rf ./project.json
	rm -rf ./*.zip
	rm -rf ./*.sb3

build/boilerplate: ./tests/boilerplate.cpp ./cpp-scratch-generator.hpp
	cd ./tests/; $(CPP) $(FLAGS) boilerplate.cpp -o ../build/boilerplate 

zip-temp:
	zip ./temp.zip ./project.json
	cp ./temp.zip ./temp.sb3
	
check-source: cpp-scratch-generator.hpp
	$(CPP) $(FLAG) cpp-scratch-generator.hpp -c -o ./build/cpp-scratch-generator.o

# this part might change depend on what I am writing
run: build/boilerplate
	./build/boilerplate
	make zip-temp

