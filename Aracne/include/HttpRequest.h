#pragma once

#include <map>
#include <string>

namespace aracne {

class HttpRequest {
 public:
  std::string method;
  std::string url;
  std::string version;
  std::map<std::string, std::string> header;
  HttpRequest();
  HttpRequest(std::string, std::string);
  HttpRequest(char* request);
  void Parse(char* request);
  std::string ToString();
};

}  // namespace aracne