main: src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp include/BrowserSocket.h include/HttpRequest.h
	g++ -g -I include src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp -o aracne.out 