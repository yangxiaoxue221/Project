cc = gcc

../release/libstudent.so : ../release/moduleb.o
	$(cc) -fPIC -shared ../release/moduleb.o -o ../release/libstudent.so

../release/moduleb.o : moduleb.c moduleb.h ../main.h
	$(cc) -fPIC -I ./ -I ../ -c moduleb.c -o ../release/moduleb.o

