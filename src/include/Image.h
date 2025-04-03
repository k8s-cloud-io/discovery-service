#ifndef IMAGE_H
#define IMAGE_H

#include "String.h"
#include "ByteArray.h"
#include <gdk-pixbuf/gdk-pixbuf.h>

class Image {
    public:
        enum InterpType {
            INTERP_NEAREST = 0,
            INTERP_TILES,
            INTERP_BILINEAR,
            INTERP_HYPER
        };

        void scale(int, int, InterpType type = INTERP_BILINEAR);
        
        static Image fromUri(const String &);
        [[nodiscard]] ByteArray getBytes() const;
        [[nodiscard]] int getWidth() const;
        [[nodiscard]] int getHeight() const;

    private:
        Image();
        GdkPixbuf *pixbuf;
};

#endif // IMAGE_H