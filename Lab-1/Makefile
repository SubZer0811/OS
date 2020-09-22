all: cp mysort multisort smartsort

cp: src/cp.c
	gcc src/cp.c -o cp
	ln -s cp rm

mysort: src/mysort.c
	gcc src/mysort.c -o mysort

multisort: src/multisort.cpp
	g++ src/multisort.cpp -o multisort

smartsort: src/smartsort.cpp
	g++ src/smartsort.cpp -o smartsort

clean:
	rm cp rm mysort multisort smartsort