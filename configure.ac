#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
# AC_PROG_MKDIR_P

# Checks for libraries.
AC_CHECK_LIB(curl, curl_easy_init)
AC_CHECK_LIB(curl, curl_easy_setopt)
AC_CHECK_LIB(curl, curl_easy_getinfo)
AC_CHECK_LIB(curl, curl_easy_nextheader)
AC_CHECK_LIB(xml2, xmlReadDoc)
AC_CHECK_LIB(xml2, xmlStrcmp)
AC_CHECK_LIB(xml2, xmlGetProp)
AC_CHECK_LIB(sqlite3, sqlite3_open)

# Checks for header files.
AC_CHECK_HEADERS([curl/curl.h])
AC_CHECK_HEADERS([libxml/xmlreader.h])
AC_CHECK_HEADERS([sqlite3.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
