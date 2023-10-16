#include "TgaData.h"

TgaData::TgaData(unsigned char* _pixelData, Header _header, int _size) {
    pixelData = _pixelData;
    header = _header;
    size = _size;
}

unsigned char * TgaData::getPixelData() {
    return pixelData;
}

TgaData::Header TgaData::getHeader() {
    return header;
}

int TgaData::getSize() {
    return size;
}
