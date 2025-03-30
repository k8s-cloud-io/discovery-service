#ifndef HTTPHEADER
#define HTTPHEADER

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
ostream& operator << ( std::ostream& outs, HttpHeaders headers ) {
  StringList v;
  for(HttpHeaders::iterator it = headers.begin(); it != headers.end(); ++it) {
    v.push_back("{" + it->first + ": " + it->second + "}");
  }

  stringstream s;
  std::copy(v.begin(), v.end(), ostream_iterator<String>(s, ", "));
  return outs << "HttpHeaders = [" << s.str() << "]";
}


#endif // HTTPHEADER_H