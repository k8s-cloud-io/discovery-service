#ifndef HTTP_HEADER_H
#define HTTP_HEADER_H

#include <algorithm>
#include <iterator>
#include <ostream>
#include <sstream>
#include "StringList.h"
#include "StringMap.h"
using std::copy;
using std::ostream;
using std::ostream_iterator;
using std::stringstream;

typedef StringMap HttpHeaders;

inline
ostream& operator << ( ostream& outs, const HttpHeaders& headers ) {
  StringList v;
  for(auto &[fst, snd] : headers) {
    v.emplace_back("{" + fst + ": " + snd + "}");
  }

  stringstream s;
  ::copy(v.begin(), v.end(), ostream_iterator<String>(s, ", "));
  return outs << "HttpHeaders = [" << s.str() << "]";
}


#endif // HTTP_HEADER_H