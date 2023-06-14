g++ -c ./Client/source/Client.cpp -o ./Client/build/client.o

g++ ./Client/build/Client.o -o ./client/build/client.exe -lole32 -loleaut32 -luser32

pause