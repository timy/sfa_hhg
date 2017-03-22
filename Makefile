all:
	g++ libhhg.cc -O3 -fPIC -c -o libhhg.o
	g++ libhhg.o -O3 -shared -o libhhg.so
	g++ main.cc -O3 -c -o main.o
	g++ main.o -O3 -L. -lhhg -o test
	g++ main_full.cc -O3 -o app

clean:
	rm -f *.o *.so
