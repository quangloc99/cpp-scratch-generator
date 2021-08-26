CPP=g++
FLAGS=--std=c++11 -g
LIB_SOURCE=./cpp-scratch-generator.hpp ./def-macro.inc ./undef-macro.inc

all: run-test-procedure

clean:
	mkdir -p build
	mkdir -p out
	rm -rf build/*
	rm -rf out/*
	rm -rf ./project.json
	rm -rf ./*.zip
	rm -rf ./*.sb3
	rm -rf ./tests/*.wav
	rm -rf ./tests/*.svg
	rm -rf ./tests/*.sb3
	rm -rf ./tests/*.zip
	rm -rf ./tests/*.json

check-source: cpp-scratch-generator.hpp
	$(CPP) $(FLAG) cpp-scratch-generator.hpp -c -o ./build/cpp-scratch-generator.o
	
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
	
build/test-forbidden-keywords: ./tests/test-forbidden-keywords.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) test-forbidden-keywords.cpp -o ../build/test-forbidden-keywords
	
build/play: ./tests/play.cpp $(LIB_SOURCE)
	@echo "=== Building ==="
	cd ./tests/; $(CPP) $(FLAGS) play.cpp -o ../build/play
	
build-all: \
	build/test-cin-prompt \
	build/test-control \
	build/test-forbidden-keywords \
	build/test-list \
	build/test-operators \
	build/test-procedure \
	build/play
	
	@echo "=== DONE ==="

run-test-operators: build/test-operators
	@echo "=== Running ==="
	./build/test-operators ./out
	zip ./out/test-operators.sb3 ./out/project.json
	
run-test-control: build/test-control
	@echo "=== Running ==="
	./build/test-control ./out
	zip ./out/test-control.sb3 ./out/project.json
	
run-test-list: build/test-list
	@echo "=== Running ==="
	./build/test-list ./out
	zip ./out/test-list.sb3 ./out/project.json

run-test-procedure: build/test-procedure
	@echo "=== Running ==="
	./build/test-procedure ./out
	zip ./out/test-procedure.sb3 ./out/project.json
	
run-test-cin-prompt: build/test-cin-prompt
	@echo "=== Running ==="
	./build/test-cin-prompt ./out
	
run-test-forbidden-keywords: build/test-forbidden-keywords
	@echo "=== Running ==="
	./build/test-forbidden-keywords
	
run-all-test: \
	run-test-cin-prompt \
	run-test-control \
	run-test-forbidden-keywords \
	run-test-list \
	run-test-operators \
	run-test-procedure
	
	@echo "=== DONE ==="
	
run-play-cli: build/play
	./build/play
	scrapec --json project.json
	scrape project.scrape
	
