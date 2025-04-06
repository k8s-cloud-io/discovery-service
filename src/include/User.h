#ifndef USER_H
#define USER_H

#include "String.h"
#include "Xdg.h"

class User {
    public:
         explicit User(int id = -1);

         static User current();

         [[nodiscard]] String getName() const;
         [[nodiscard]] String getHomeDirectory() const;
         [[nodiscard]] int getId() const;
         [[nodiscard]] String getDirectory(XdgDirectory) const;

    private:
         int id;
};

#endif //USER_H
