#ifndef HTTPHEADER_H
#define HTTPHEADER_H

#include <iterator>
#include <ostream>
#include <sstream>
#include <vector>

#include "StringList.h"
#include "StringMap.h"

using std::ostream;
using std::ostream_iterator;
using std::stringstream;
using std::vector;

typedef StringMap HttpHeaders;

inline
ostream& operator << ( std::ostream& outs, const HttpHeaders& headers ) {
  StringList v;
  for(auto &[fst, snd] : headers) {
    v.emplace_back("{" + fst + ": " + snd + "}");
  }

  stringstream s;
  std::copy(v.begin(), v.end(), ostream_iterator<String>(s, ", "));
  return outs << "HttpHeaders = [" << s.str() << "]";
}


#endif // HTTPHEADER_H