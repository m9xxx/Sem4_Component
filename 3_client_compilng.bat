g++ -c ./client/source/client.cpp -o ./client/build/client.o
g++ -c ./client/source/wrapper.cpp -o ./client/build/wrapper.o

g++ ./client/build/client.o ./client/build/wrapper.o -o ./client/build/client.exe -lole32 -loleaut32 -luser32
pause