#include <iostream>
#include "BrowserSocket.h"
#include "HttpRequest.h"
#include "InternetSocket.h"
#include "Spider.h"

#define BUF_SIZE (1024 * 1024)

using namespace aracne;

int main(int argc, char const *argv[]) {
  char *buffer = new char[BUF_SIZE];
  std::cout << "Starting" << std::endl;
  int port = argc > 1 ? atoi(argv[argc - 1]) : 8228;
#ifndef MY_DEBUG_SPIDER
  BrowserSocket ss;
  ss.Initialize(port);
  while (true) {
    ss.AwaitConnection();

    int n = ss.ReadRequest(buffer, BUF_SIZE);
    if (n < 5) {
      std::cout << "Request too small (" << n << " bytes)" << std::endl;
      continue;
    }
    buffer[n] = '\0';
    std::cout << "Request:" << std::endl << buffer << std::endl;

    HttpRequest request(buffer);

    // std::cout << "Rebuilt request: " << std::endl << request.ToString() <<
    // std::endl;

    InternetSocket is;
    int response_size = is.SendRequest(request, buffer, BUF_SIZE);

    buffer[response_size] = '\0';
    std::cout << "Response: " << std::endl << buffer << std::endl;

    ss.SendResponse(buffer, response_size);
  }

  delete[] buffer;

#else
  // Spider sp = Spider("http://www.columbia.edu/~fdc/sample.html","columbia.edu");
  Spider sp = Spider(
      "http://userwww.sfsu.edu/infoarts/technical/howto/wilson.javascript.exampls.html",
      "userwww.sfsu.edu");
  // Spider sp = Spider("http://help.websiteos.com/websiteos/websiteos.html#example_of_a_simple_html_page.htm","http://help.websiteos.com");
  cout << "Maping Spider\n" << endl;
  sp.lstAll();
  struct SpiderLst spLst = sp.showSpider();
  spLst.show();

#endif

  return 0;
}
