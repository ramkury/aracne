#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>


using namespace std;

namespace aracne{

struct SpiderLst{
    string url;
    vector<SpiderLst> lst = vector<SpiderLst> ();
    string show();
    string show(string);
    char * showC();
};

class Spider{
private:
    string host;
    string url;

    map<string, vector<string>> tree;
    vector<string> lstURLsfrom(string);
    string responseReqURL(string);
    void lstAll(string url);
    struct SpiderLst showSpider(string, vector<string>);
public:
    Spider(string, string);
    struct SpiderLst showSpider();
    void lstAll();
};

}