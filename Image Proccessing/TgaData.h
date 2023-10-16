#include <iostream>
#include <fstream>
using namespace std;

class TgaData {
public:
    struct Header{
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };
    TgaData(unsigned char* _pixelData, Header _header, int _size);
    unsigned char* getPixelData();
    Header getHeader();
    int getSize();
private:
    Header header;
    unsigned char* pixelData;
    int size;
};
