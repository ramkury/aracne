#include "Spider.h"
#include "HttpRequest.h"
#include "InternetSocket.h"
#ifdef MY_DEBUG_SPIDER
#include "ColorMacro.h"
#endif

namespace aracne {

void SpiderLst::show(string level_indent) {
  cout << level_indent << url << endl;
  level_indent = "     " + level_indent;
  for (auto &s : lst) {
    s.show(level_indent);
  }
}

void SpiderLst::show() {
  cout << url << endl;
  string level_indent = "   +-- ";
  for (auto &s : lst) {
    s.show(level_indent);
  }
}

Spider::Spider(
    string urlReq,
    string domain) {  // domain can have "http://" but can NOT end with '/'
  // #ifdef MY_DEBUG_SPIDER
  //     cout<< BoldTextBlue << "\n ---- Contrutor Spider ---- "<< TextDefault
  //     << endl;
  // #endif

  if (url.find(domain) == std::string::npos)
    url = urlReq;
  else
    url = urlReq.substr(urlReq.find(domain) + domain.length());

  if (domain.find("http://") == std::string::npos)
    host = domain;
  else
    host = domain.substr(domain.find("http://") + 7);

  for (auto &a : url) {
    a = tolower(a);
  }
  for (auto &a : domain) {
    a = tolower(a);
  }

  // #ifdef MY_DEBUG_SPIDER
  //     cout<<"URL armazenada\t"<<url<<endl;
  //     cout<<"HOST armazeando\t"<<host<<endl;
  //     cout<< BoldTextBlue << " ---- Contrutor Spider ---- \n"<< TextDefault
  //     << endl;
  // #endif
}

struct SpiderLst Spider::showSpider(
    string url, vector<string> previousNode = vector<string>()) {
  struct SpiderLst showTree;

  showTree.url = url;

  for (auto &u : previousNode) {
    if (u == url) {
      return showTree;
    }
  }

  for (auto &t : tree[url]) {
    previousNode.push_back(url);
    showTree.lst.push_back(showSpider(t, previousNode));
  }

  return showTree;
}

struct SpiderLst Spider::showSpider() {
  return showSpider(url);
}

vector<string> Spider::lstURLsfrom(string url) {
  // #ifdef MY_DEBUG_SPIDER
  //     cout<< BoldTextBlue << "\n ---- Dentro da lstURLsfrom ---- "<<
  //     TextDefault << endl;
  // #endif

  vector<string> urlLst;
  string temp;

  string body = responseReqURL(url);
  // #ifdef MY_DEBUG_SPIDER
  //     cout<< "BODY:\n"<< body << endl;
  // #endif
  size_t begRef, endRef;

  begRef = body.find("href=\"");

  while (begRef != std::string::npos) {
    endRef = body.find("\"", begRef + 6);
    if (endRef == std::string::npos) {
      cout << "SPIDER ERROR! While searching href" << endl;
      exit(8);  // spider error = 8
    }
    temp = body.substr(begRef + 6, endRef - (begRef + 6));
    // #ifdef MY_DEBUG_SPIDER
    //     cout<< "href:\t"<< temp << endl;
    // #endif
    if (temp.find("http://") == std::string::npos) {
      if (temp[0] == '/') {
        urlLst.push_back(url + temp);
      } else {
        urlLst.push_back(temp);
      }
    } else if (temp.find(host) != std::string::npos) {
      // #ifdef MY_DEBUG_SPIDER
      //     cout<< "href com host:\t"<< temp << endl;
      //     cout<<"\t"<< "host length: " host.length() << endl;
      //     cout<<"\t"<< "host: " host << endl;
      // #endif
      urlLst.push_back(temp.substr(temp.find(host) + host.length()));
    }
    begRef = body.find("href=\"", endRef + 1);
  }

  // #ifdef MY_DEBUG_SPIDER
  //     cout<< BoldTextBlue << " ---- Dentro da lstURLsfrom ---- \n"<<
  //     TextDefault << endl;
  // #endif

  return urlLst;
}

void Spider::lstAll(string url) {
  if (tree.find(url) == tree.end()) {
    vector<string> urlLst = lstURLsfrom(url);
    tree[url] = urlLst;

    for (auto &u : urlLst) {
      lstAll(u);
    }
  }
}

void Spider::lstAll() { lstAll(url); }

string Spider::responseReqURL(string url) {
  // #ifdef MY_DEBUG_SPIDER
  //     cout<< BoldTextBlue << "\n ---- Dentro da responseReqURL ---- "<<
  //     TextDefault << endl;
  // #endif
  InternetSocket socket;

  if (url.find(host) == std::string::npos) {
    if (url[0] == '/')
      url = host + url;
    else
      url = host + "/" + url;
  }

  if (url.find("http://") == std::string::npos) {
    url = "http://" + url;
  }

  // #ifdef MY_DEBUG_SPIDER
  //     cout << "URL\t" << url << endl;
  // #endif

  HttpRequest req = HttpRequest(host, url);

  char buffer[(1024 * 1024)];

  int len = socket.SendRequest(req, buffer, (1024 * 1024));

  buffer[len] = '\0';

// #ifdef MY_DEBUG_SPIDER
//   cout << "\nHTTP Request to string:\n" << req.ToString() << endl;
// #endif

  string body = string(buffer);
  // #ifdef MY_DEBUG_SPIDER
  //     cout<<"Response:\n"<< body << endl;
  // #endif
  body = body.substr(body.find("\r\n\r\n") + 4);

  for (auto &b : body) {
    b = tolower(b);
  }

  // #ifdef MY_DEBUG_SPIDER
  //     cout<<"\nBODY:\n"<< body << endl;
  // #endif

  // #ifdef MY_DEBUG_SPIDER
  //     cout<< BoldTextBlue << " ---- Dentro da responseReqURL ---- \n"<<
  //     TextDefault << endl;
  // #endif
  return body;
}
}  // namespace aracne