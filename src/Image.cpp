#include "Image.h"
#include <glib.h>
#include <HttpRequest.h>
#include <iostream>
using namespace std;

Image::Image()
    :pixbuf(nullptr){
}

Image Image::fromUri(const String &resource) {
    GError *err = nullptr;

    const HttpRequest req(HttpRequest::GET, resource);
    const auto *response = req.exec();
    const ByteArray data = response->getBody();

    Image img;
    img.pixbuf = nullptr;

    err = nullptr;
    GInputStream *stream = g_memory_input_stream_new_from_data(data.data(), static_cast<long>(data.size()), nullptr);
    img.pixbuf = gdk_pixbuf_new_from_stream(stream, nullptr, &err);

    if(err != nullptr) {
        img.pixbuf = nullptr;
        cout << "error while reading image from stream: " << err->message << endl;
    }
    return img;
}

void Image::scale(const int width, const int height, const InterpType type) {
    if(pixbuf != nullptr) {
        GdkInterpType interp;

        switch(type) {
            default:
            case INTERP_NEAREST:
                interp = GDK_INTERP_NEAREST;
                break;

            case INTERP_TILES:
                interp = GDK_INTERP_TILES;
                break;

            case INTERP_BILINEAR:
                interp = GDK_INTERP_BILINEAR;
                break;

            case INTERP_HYPER:
                interp = GDK_INTERP_HYPER;
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

ByteArray Image::getBytes() const {
    ByteArray arr;
    if(pixbuf != nullptr) {
        arr = reinterpret_cast<const char *>(gdk_pixbuf_get_pixels(pixbuf));
    }
    return arr;
}
