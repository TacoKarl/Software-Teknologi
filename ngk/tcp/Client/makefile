CXX=g++

EXE=client.exe

${EXE}: file_client.o iknlib.o
	${CXX} -o ${EXE} file_client.o iknlib.o

clean:
	rm *.o ${EXE}