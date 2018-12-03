main: src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp src/Spider.cpp src/InternetSocket.cpp src/utils.cpp  src/HttpUtils.cpp src/AracDump.cpp include/BrowserSocket.h include/HttpRequest.h include/Spider.h include/InternetSocket.h include/utils.h include/HttpUtils.h include/AracDump.h
	g++ -g -I include --std=gnu++11 src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp src/Spider.cpp src/InternetSocket.cpp src/utils.cpp -o aracne.out 

debug: src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp src/Spider.cpp src/InternetSocket.cpp src/utils.cpp  src/HttpUtils.cpp src/AracDump.cpp include/BrowserSocket.h include/HttpRequest.h include/Spider.h include/InternetSocket.h include/utils.h include/HttpUtils.h include/AracDump.h
	g++ -g -I include --std=gnu++11 -D MY_DEBUG_SPIDER src/aracne.cpp src/BrowserSocket.cpp src/HttpRequest.cpp src/Spider.cpp src/InternetSocket.cpp src/utils.cpp src/HttpUtils.cpp src/AracDump.cpp -o aracne.out 
