CPP=g++
FLAGS=--std=c++11 -g
LIB_SOURCE=./cpp-scratch-generator.hpp ./def-macro.inc ./undef-macro.inc

all: run-test-procedure

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
	
build/boilerplate: ./tests/boilerplate.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) boilerplate.cpp -o ../build/boilerplate 
	
build/test-operators: ./tests/test-operators.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-operators.cpp -o ../build/test-operators

build/test-control: ./tests/test-control.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-control.cpp -o ../build/test-control

build/test-list: ./tests/test-list.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-list.cpp -o ../build/test-list
	
build/test-procedure: ./tests/test-procedure.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-procedure.cpp -o ../build/test-procedure
	
build/test-cin-prompt: ./tests/test-cin-prompt.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-cin-prompt.cpp -o ../build/test-cin-prompt
	
build/play: ./tests/play.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) play.cpp -o ../build/play
	
build-all: \
	build/boilerplate \
	build/test-operators \
	build/test-control \
	build/test-list \
	build/test-procedure \
	build/test-cin-prompt \
	build/play
	
	@echo "=== DONE ==="

run-test-operators: build/test-operators
	@echo "=== Running ==="
	./build/test-operators
	make zip-temp
	
run-test-control: build/test-control
	@echo "=== Running ==="
	./build/test-control
	make zip-temp
	
run-test-list: build/test-list
	@echo "=== Running ==="
	./build/test-list
	make zip-temp

run-test-procedure: build/test-procedure
	@echo "=== Running ==="
	./build/test-procedure
	make zip-temp
	
run-test-cin-prompt: build/test-cin-prompt
	./build/test-cin-prompt
	
run-play-cli: build/play
	./build/play
	scrapec --json project.json
	scrape project.scrape
