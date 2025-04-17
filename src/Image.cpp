#include <fstream>
#include <iostream>
#include <glib.h>
#include "File.h"
#include "HttpRequest.h"
#include "Image.h"
using std::ifstream;
using std::cout;
using std::endl;

Image::Image()
    :pixbuf(nullptr){
}

Image::~Image() {
    if (pixbuf) {
        g_object_unref(pixbuf);
        pixbuf = nullptr;
    }
}

Image Image::fromUri(const String &uri) {
    if (uri.find("http://") == 0 || uri.find("https://") == 0 || uri.find("ftp://") == 0) {
        const HttpRequest req(HttpRequest::GET, uri);
        const auto *response = req.exec();
        if (response->getStatusCode() == 200) {
            const ByteArray data = response->getBody();
            return fromBytes(data);
        }
        cout << "Image::fromUri - unable to download from uri " << uri;
        cout << ": HTTP CODE = " << response->getStatusCode() << endl;
    }

    if (uri.find("file://") == 0) {
        const String name = uri.substr(strlen("file://"));
        if(File::exists(name)) {
            const File f(name);
            const ByteArray bytes = f.getBytes();
            return fromBytes(bytes);
        }
        cout << "Image::fromUri - local file " << name << " does not exist" << endl;
    }

    Image img;
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

Image Image::fromBytes(const ByteArray &data) {
    Image img;
    img.pixbuf = nullptr;

    GError *err = nullptr;
    GInputStream *stream = g_memory_input_stream_new_from_data(
        data.data(),
        static_cast<long>(data.size()),
        nullptr
    );
    img.pixbuf = gdk_pixbuf_new_from_stream(stream, nullptr, &err);

    if(err != nullptr) {
        img.pixbuf = nullptr;
        cout << "Image::fromBytes - error while reading image from bytes: " << err->message << endl;
    }
    return img;
}