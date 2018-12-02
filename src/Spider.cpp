#include "Spider.h"

Spider::Spider(string url, string host){
    if(url.find(host)==std::string::npos)
        url = url;
    else
        url = url.substr(url.find(host));

    host = host;
}

struct SpiderLst Spider::showSpider(string url, vector<string> previousNode = vector<string>()){
    struct SpiderLst showTree;
    
    showTree.url = url;

    for(auto &u:previousNode){
        if(u==url){
            return showTree;
        }
    }

    for(auto &t:tree[url]){
        previousNode.push_back(url);
        showTree.lst.push_back(showSpider(t, previousNode));
    }

    return showTree;
}

vector<string> Spider::lstURLsfrom(string url){

    vector<string> urlLst;
    string temp;
    
    string body = responseReqURL(url);
    
    size_t begRef, endRef;

    begRef = body.find("href=\"");

    while(begRef!=std::string::npos){
        endRef = body.find("\"", begRef+6);
        if(endRef==std::string::npos){
            cout<<"SPIDER ERROR! While searching href"<<endl;
            exit(8); // spider error = 8
        }
        temp = body.substr(begRef+6, endRef-(begRef+6));

        if(temp.find("http://")==std::string::npos){
            if(temp[0]=='/'){
                urlLst.push_back(url+temp);
            }else{
                urlLst.push_back(temp);
            }
        }else if(temp.find(host)!=std::string::npos){
            temp = temp.substr(temp.find(host)+host.length());
        }
        begRef = body.find("href=\"", endRef+1);
    }

    return urlLst;

}

void Spider::lstAll(string url){
    if(tree.find(url)==tree.end()){
        vector<string> urlLst = lstURLsfrom(url);
        tree[url] = urlLst;
        
        for(auto &u:urlLst){
            lstAll(u);
        }
        
    }
}


string Spider::responseReqURL(string url){
    //host+url

    
}
