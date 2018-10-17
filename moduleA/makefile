cc = gcc

../release/libclass.so : ../release/modulea.o
	$(cc) -fPIC -shared ../release/modulea.o -o ../release/libclass.so

../release/modulea.o : modulea.c modulea.h ../main.h
	$(cc) -fPIC -I ./ -I ../ -c modulea.c -o ../release/modulea.o


