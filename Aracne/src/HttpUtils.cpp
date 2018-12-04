#include "HttpUtils.h"

namespace aracne{

string bodyResponseReqURL(string host, string url) {
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

    HttpRequest req = HttpRequest(host, url);

    char buffer[(1024 * 1024)];

    int len = socket.SendRequest(req, buffer, (1024 * 1024));

    buffer[len] = '\0';

    string body = string(buffer);

    body = body.substr(body.find("\r\n\r\n") + 4);

    for (auto &b : body) {
        b = tolower(b);
    }

    return body;
}

}