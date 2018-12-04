#include "utils.h"
#include <cstdio>
#include <cstdlib>

namespace aracne {

void error(const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(-1);
}

vector<string> getLinksAuxLoop(string text, string lmtBeg, string lmtEnd){
  vector<string> result;

  size_t begPos = text.find(lmtBeg);
  size_t endPos;

  while(begPos!=std::string::npos){
    endPos = text.find(lmtEnd, begPos+lmtBeg.length());

    result.push_back(text.substr(begPos+lmtBeg.length(), endPos-(begPos+lmtBeg.length())));

    begPos = text.find(lmtBeg);
  }
}

struct VecSfont getURLsFromString(string s) {

  struct VecSfont result;

  result.hrefS = getLinksAuxLoop(s, "href='", "'");

  result.hrefD = getLinksAuxLoop(s, "href=\"", "\"");

  result.srcS = getLinksAuxLoop(s, "src='", "\"");

  result.srcD = getLinksAuxLoop(s, "src=\"", "\"");

  return result;
}


}  // namespace aracne