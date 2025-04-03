#include "Image.h"

#include <glib.h>

#include <iostream>
using namespace std;

Image::Image() {
}

Image Image::fromUri(const String &resource) {
    GError *err = nullptr;
    GFile *f = g_file_new_for_uri(resource.c_str());

    Image img;
    img.pixbuf = nullptr;

    GFileInputStream *fis = g_file_read(f, nullptr, &err);
    if(err != nullptr) {
        cout << err->message << endl;
    } else {
        err = nullptr; 

        img.pixbuf = gdk_pixbuf_new_from_stream(G_INPUT_STREAM(fis), nullptr, &err);
        if(err != nullptr) {
            img.pixbuf = nullptr;
            cout << err->message << endl;
        }
    }

    g_object_unref(f);
    return img;
}

void Image::scale(int width, int height, Image::InterpType type) {
    if(pixbuf != nullptr) {
        GdkInterpType interp;

        switch(type) {
            default:
            case Image::INTERP_NEAREST:
                interp = GdkInterpType::GDK_INTERP_NEAREST;
                break;

            case Image::INTERP_TILES:
                interp = GdkInterpType::GDK_INTERP_TILES;
                break;

            case Image::INTERP_BILINEAR:
                interp = GdkInterpType::GDK_INTERP_BILINEAR;
                break;

            case Image::INTERP_HYPER:
                interp = GdkInterpType::GDK_INTERP_HYPER;
                break;
        }

        GdkPixbuf *dest = gdk_pixbuf_scale_simple(pixbuf, width, height, interp);
        g_object_unref(pixbuf);
        pixbuf = dest;
    }
}

int Image::getWidth() const {
    if(pixbuf) {
        return gdk_pixbuf_get_width(pixbuf);
    }
    return 0;
}

int Image::getHeight() const {
    if(pixbuf) {
        return gdk_pixbuf_get_height(pixbuf);
    }
    return 0;
}