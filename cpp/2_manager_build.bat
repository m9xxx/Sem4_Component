g++ -c ./source/manager/Manager.cpp -o ./build/manager/manager.o

g++ -shared ./build/manager/manager.o -o ./build/manager/manager.dll -Wl,--kill-at

pause