g++ -c ./server/source/component.cpp -o ./server/build/component.o
g++ -c ./server/source/main.cpp -o ./server/build/main.o

g++ -shared ./server/build/component.o ./server/build/main.o -o ./dll/server.dll -Wl,--kill-at -lole32 -loleaut32 -luser32

pause

