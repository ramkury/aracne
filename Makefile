main: src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp src/Spider.cpp include/BrowserSocket.h include/HttpRequest.h include/Spider.h
	g++ -g -I include --std=gnu++11 src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp src/Spider.cpp -o aracne.out 
