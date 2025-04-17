#ifndef IMAGE_H
#define IMAGE_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include "ByteArray.h"
#include "String.h"

class Image final {
    public:
        enum InterpType {
            INTERP_NEAREST = 0,
            INTERP_TILES,
            INTERP_BILINEAR,
            INTERP_HYPER
        };
        ~Image();
        void scale(int, int, InterpType type = INTERP_BILINEAR);
        
        static Image fromUri(const String &);
        static Image fromBytes(const ByteArray &);

        [[nodiscard]] ByteArray getBytes() const;
        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;

    private:
        Image();
        GdkPixbuf *pixbuf;
};

#endif // IMAGE_H