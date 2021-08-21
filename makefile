CPP=g++
FLAGS=--std=c++11

clean:
	rm -rf build/*
	rm -rf ./project.json
	rm -rf ./*.zip
	rm -rf ./*.sb3

zip-temp:
	zip ./temp.zip ./project.json
	cp ./temp.zip ./temp.sb3
	
check-source: cpp-scratch-generator.hpp
	$(CPP) $(FLAG) cpp-scratch-generator.hpp -c -o ./build/cpp-scratch-generator.o
	
build/boilerplate: ./tests/boilerplate.cpp ./cpp-scratch-generator.hpp
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) boilerplate.cpp -o ../build/boilerplate 
	
build/test-operators: ./tests/test-operators.cpp ./cpp-scratch-generator.hpp
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-operators.cpp -o ../build/test-operators


# this part might change depend on what I am writing
run: build/test-operators
	@echo "=== Running ==="
	./build/test-operators
	make zip-temp

