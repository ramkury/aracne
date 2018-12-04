#include "AracDump.h"
#include "HttpUtils.h"

namespace aracne {

AracDump::AracDump(string domain, string urlReq) {
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
  dldPath = "../../AracDump/";
}

int AracDump::startDump() { 
  string body = bodyResponseReqURL(host, url);

  auto links = getURLsFromString(body);

  verifyLinks(links);




}

void verifyLinkLst(vector<string> &lst, string host){
  
  for(auto& i : lst){
    if(i.find("http://")!=std::string::npos){
      if(i.find(host)==std::string::npos){
        i.erase();
      }else{
        i = i.substr(i.find(host)+host.length());
      }
    }
  }
  
}

void AracDump::verifyLinks(VecSfont & links){

  verifyLinkLst(links.srcS, host);
  verifyLinkLst(links.srcD, host);
  verifyLinkLst(links.hrefS, host);
  verifyLinkLst(links.hrefD, host);   

}

void AracDump::updateHTML(string body, VecSfont links){

}

AracDump::~AracDump() {
  const string msg = "rm -r -f " + dldPath;
  system(msg.c_str());
}

}  // namespace aracne