#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace aracne{

struct VecSfont{
    vector<string> hrefS, hrefD, srcS, srcD;
};

void error(const char *message);
VecSfont getURLsFromString(string s);

}