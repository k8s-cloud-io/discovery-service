#ifndef FILE_H
#define FILE_H

#include <string>
using std::string;

class File {
    public:
        File(const string &);
        virtual ~File(){}
        string getAbsolutePath() const;
        string getDirectory();

        static bool exists(const string &);
        static bool isDirectory(const string &);

    private:
        File();
        string path;
};

#endif