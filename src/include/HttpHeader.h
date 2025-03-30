#ifndef HTTPHEADER
#define HTTPHEADER

#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "StringMap.h"

using std::ostream;
using std::ostream_iterator;
using std::string;
using std::stringstream;
using std::vector;

typedef StringMap HttpHeaders;

inline
ostream& operator << ( std::ostream& outs, HttpHeaders headers ) {
  vector<string> v;
  for(HttpHeaders::iterator it = headers.begin(); it != headers.end(); ++it) {
    v.push_back("{" + it->first + ": " + it->second + "}");
  }

  stringstream s;
  std::copy(v.begin(), v.end(), ostream_iterator<string>(s, ", "));
  return outs << "HttpHeaders = [" << s.str() << "]";
}


#endif // HTTPHEADER_H