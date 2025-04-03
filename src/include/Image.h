#ifndef IMAGE_H
#define IMAGE_H

#include "String.h"
#include <gdk-pixbuf/gdk-pixbuf.h>

class Image {
    public:
        enum InterpType {
            INTERP_NEAREST = 0,
            INTERP_TILES,
            INTERP_BILINEAR,
            INTERP_HYPER
        };

        void scale(int, int, Image::InterpType type = Image::INTERP_BILINEAR);
        
        static Image fromUri(const String &);
        int getWidth() const;
        int getHeight() const;

    private:
        Image();
        GdkPixbuf *pixbuf;
};

#endif // IMAGE_H