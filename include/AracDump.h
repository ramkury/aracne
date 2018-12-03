#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <iostream>
#include <stdlib.h>
#include "utils.h"

using namespace std;

namespace aracne{

class AracDump{
private:
    string url, host, dldPath;
    void verifyLinks(VecSfont & links);
    void updateHTML(string html, VecSfont links);
public:

    int startDump();
    AracDump(string, string);
    ~AracDump();
};

}