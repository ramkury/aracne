#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>


using namespace std;


struct SpiderLst{
    string url;
    vector<SpiderLst> lst = vector<SpiderLst> ();
};

class Spider{
private:
    string host;
    string url;

    map<string, vector<string>> tree;
    vector<string> lstURLsfrom(string);
    string responseReqURL(string);
    void lstAll(string url);
public:
    Spider(string, string);
    struct SpiderLst showSpider(string, vector<string>);
};