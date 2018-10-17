cc = gcc

./release/main: main.c
	make -C ./moduleA
	make -C ./moduleB
	$(cc) -o ./release/main main.c -I ./ -L ./release -Wl,-rpath=./release/ -lclass -lstudent

clean:
	rm -rf ./release/*.o
