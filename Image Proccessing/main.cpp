#include <iostream>
#include <fstream>
#include "TgaData.h"
using namespace std;

TgaData readData(string fileName){
    ifstream file(fileName, ios_base::binary);
    TgaData::Header header;
    file.read(&header.idLength, 1);
    file.read(&header.colorMapType, 1);
    file.read(&header.dataTypeCode, 1);
    file.read((char*)&header.colorMapOrigin, 2);
    file.read((char*)&header.colorMapLength, 2);
    file.read(&header.colorMapDepth, 1);
    file.read((char*)&header.xOrigin, 2);
    file.read((char*)&header.yOrigin, 2);
    file.read((char*)&header.width, 2);
    file.read((char*)&header.height, 2);
    file.read(&header.bitsPerPixel, 1);
    file.read(&header.imageDescriptor, 1);
    int size = 3 * header.width * header.height;
    unsigned char* pixelData = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        file.read((char*)&pixelData[i], 1);
    }
    TgaData data(pixelData, header, size);
    return data;
}

void writeData(string fileName, TgaData data, unsigned char* pixelData){
    ofstream file(fileName + ".tga", ios_base::binary);
    TgaData::Header header = data.getHeader();
    file.write(&header.idLength, 1);
    file.write(&header.colorMapType, 1);
    file.write(&header.dataTypeCode, 1);
    file.write((char*)&header.colorMapOrigin, 2);
    file.write((char*)&header.colorMapLength, 2);
    file.write(&header.colorMapDepth, 1);
    file.write((char*)&header.xOrigin, 2);
    file.write((char*)&header.yOrigin, 2);
    file.write((char*)&header.width, 2);
    file.write((char*)&header.height, 2);
    file.write(&header.bitsPerPixel, 1);
    file.write(&header.imageDescriptor, 1);
    int size = 3 * header.width * header.height;
    for (int i = 0; i < size; i++) {
        file.write((char*)&pixelData[i], 1);
    }
}

/*bool compare(TgaData file1, TgaData file2){
    if(file1.getHeader().idLength != file2.getHeader().idLength){
        return false;
    }
    if(file1.getHeader().colorMapType != file2.getHeader().colorMapType){
        return false;
    }
    if(file1.getHeader().dataTypeCode != file2.getHeader().dataTypeCode){
        return false;
    }
    if(file1.getHeader().colorMapOrigin != file2.getHeader().colorMapOrigin){
        return false;
    }
    if(file1.getHeader().colorMapLength != file2.getHeader().colorMapLength){
        return false;
    }
    if(file1.getHeader().colorMapDepth != file2.getHeader().colorMapDepth){
        return false;
    }
    if(file1.getHeader().xOrigin != file2.getHeader().xOrigin){
        return false;
    }
    if(file1.getHeader().yOrigin != file2.getHeader().yOrigin){
        return false;
    }
    if(file1.getHeader().width != file2.getHeader().width){
        return false;
    }
    if(file1.getHeader().height != file2.getHeader().height){
        return false;
    }
    if(file1.getHeader().bitsPerPixel != file2.getHeader().bitsPerPixel){
        return false;
    }
    if(file1.getHeader().imageDescriptor != file2.getHeader().imageDescriptor){
        return false;
    }
    for(int i = 0; i < file1.getSize(); i++){
        if(file1.getPixelData()[i] != file2.getPixelData()[i]){
            return false;
        }
    }
    return true;
}*/

void multiply(int size, unsigned char* firstTgaPixels, unsigned char* secondTgaPixels, unsigned char*& blendedPixels){
    for (int i = 0; i < size; i++) {
        float pixel1 = (float)firstTgaPixels[i];
        float pixel2 = (float)secondTgaPixels[i];
        pixel1 /= 255;
        pixel2 /= 255;
        float pixelBlend = (pixel1 * pixel2 * 255)+.5f;
        blendedPixels[i] = (unsigned char)pixelBlend;
    }
}

void screen(int size, unsigned char* firstTgaPixels, unsigned char* secondTgaPixels, unsigned char*& blendedPixels){
    for (int i = 0; i < size; i++) {
        float pixel1 = (float)firstTgaPixels[i];
        float pixel2 = (float)secondTgaPixels[i];
        pixel1 /= 255;
        pixel2 /= 255;
        float pixelBlend = ((1 - (1 - pixel1)*(1 - pixel2)) * 255)+.5f;
        blendedPixels[i] = (unsigned char)pixelBlend;
    }
}

void overlay(int size, unsigned char* firstTgaPixels, unsigned char* secondTgaPixels, unsigned char*& blendedPixels){
    float pixelBlend;
    for (int i = 0; i < size; i++) {
        float pixel1 = (float)firstTgaPixels[i];
        float pixel2 = (float)secondTgaPixels[i];
        pixel1 /= 255;
        pixel2 /= 255;
        if (pixel2 <= .5) {
            pixelBlend = (2 * pixel1*pixel2 * 255)+.5f;
            if(pixelBlend < 0){
                pixelBlend = 0;
            }
            else if(pixelBlend > 255){
                pixelBlend = 255;
            }
            blendedPixels[i] = (unsigned char)pixelBlend;
        }
        else {
            pixelBlend = 1 - 2 * (1 - pixel1)*(1 - pixel2);
            pixelBlend *= 255;
            pixelBlend += .5f;
            if(pixelBlend < 0){
                pixelBlend = 0;
            }
            else if(pixelBlend > 255){
                pixelBlend = 255;
            }
            blendedPixels[i] = (unsigned char)pixelBlend;
        }
    }
}

void subtract(int size, unsigned char* firstTgaPixels, unsigned char* secondTgaPixels, unsigned char*& blendedPixels){
    for (int i = 0; i < size; i++) {
        int pixel1 = (int)firstTgaPixels[i];
        int pixel2 = (int)secondTgaPixels[i];
        int pixelBlend = pixel2 - pixel1;
        if(pixelBlend < 0){
            pixelBlend = 0;
        }
        else if(pixelBlend > 255){
            pixelBlend = 255;
        }
        blendedPixels[i] = (unsigned char)pixelBlend;
    }
}

void add(int size, int start, int amount, unsigned char*& blendedPixels){
    for (int i = start; i < size; i += 3) {
        int pixel = blendedPixels[i];
        pixel += amount;
        if(pixel < 0){
            pixel = 0;
        }
        else if(pixel > 255){
            pixel = 255;
        }
        blendedPixels[i] = pixel;
    }
}

void scale(int size, int start, int scaleFactor, unsigned char*& blendedPixels){
    for (int i = start; i < size; i += 3) {
        int pixel = blendedPixels[i];
        pixel *= scaleFactor;
        if(pixel < 0){
            pixel = 0;
        }
        else if(pixel > 255){
            pixel = 255;
        }
        blendedPixels[i] = pixel;
    }
}

void channelSeparator(int size, int start, unsigned char* firstTgaPixels, unsigned char*& blendedPixels){
    int index = 0;
    for (int i = start; i < size; i += 3) {
        blendedPixels[index] = firstTgaPixels[i];
        blendedPixels[index + 1] = firstTgaPixels[i];
        blendedPixels[index + 2] = firstTgaPixels[i];
        index += 3;
    }
}

int main() {
    unsigned char* firstTgaPixels;
    unsigned char* secondTgaPixels;
    unsigned char* thirdTgaPixels;
    unsigned char* blendedPixels;

    //part 1
    TgaData layer1 = readData("input/layer1.tga");
    TgaData pattern1 = readData("input/pattern1.tga");
    firstTgaPixels = layer1.getPixelData();
    secondTgaPixels = pattern1.getPixelData();
    blendedPixels = new unsigned char[layer1.getSize()];
    multiply(layer1.getSize(), firstTgaPixels, secondTgaPixels, blendedPixels);
    writeData("output/part1", layer1, blendedPixels);

    //part 2
    TgaData layer2 = readData("input/layer2.tga");
    TgaData car = readData("input/car.tga");
    firstTgaPixels = layer2.getPixelData();
    secondTgaPixels = car.getPixelData();
    blendedPixels = new unsigned char[layer2.getSize()];
    subtract(layer2.getSize(), firstTgaPixels, secondTgaPixels, blendedPixels);
    writeData("output/part2", layer2, blendedPixels);

    //part 3
    TgaData pattern2 = readData("input/pattern2.tga");
    TgaData text = readData("input/text.tga");
    firstTgaPixels = layer1.getPixelData();
    secondTgaPixels = pattern2.getPixelData();
    blendedPixels = new unsigned char[layer2.getSize()];
    multiply(layer1.getSize(), firstTgaPixels, secondTgaPixels, blendedPixels);
    thirdTgaPixels = text.getPixelData();
    screen(layer1.getSize(), blendedPixels, thirdTgaPixels, blendedPixels);
    writeData("output/part3", layer1, blendedPixels);

    //part 4
    TgaData circles = readData("input/circles.tga");
    firstTgaPixels = layer2.getPixelData();
    secondTgaPixels = circles.getPixelData();
    blendedPixels = new unsigned char[layer2.getSize()];
    multiply(layer2.getSize(), firstTgaPixels, secondTgaPixels, blendedPixels);
    thirdTgaPixels = pattern2.getPixelData();
    subtract(layer2.getSize(), thirdTgaPixels, blendedPixels, blendedPixels);
    writeData("output/part4", layer2, blendedPixels);

    //part 5
    firstTgaPixels = layer1.getPixelData();
    secondTgaPixels = pattern1.getPixelData();
    blendedPixels = new unsigned char[layer1.getSize()];
    overlay(layer1.getSize(), firstTgaPixels, secondTgaPixels, blendedPixels);
    writeData("output/part5", layer1, blendedPixels);

    //part 6
    blendedPixels = new unsigned char[car.getSize()];
    for (int i = 0; i < car.getSize(); i++) {
        blendedPixels[i] = car.getPixelData()[i];
    }
    add(car.getSize(), 1, 200, blendedPixels);
    writeData("output/part6", car, blendedPixels);

    //part 7
    blendedPixels = new unsigned char[car.getSize()];
    for (int i = 0; i < car.getSize(); i++) {
        blendedPixels[i] = car.getPixelData()[i];
    }
    scale(car.getSize(), 2, 4, blendedPixels);
    scale(car.getSize(), 0, 0, blendedPixels);
    writeData("output/part7", car, blendedPixels);

    //part 8
    blendedPixels = new unsigned char[car.getSize()];
    for (int i = 0; i < car.getSize(); i++) {
        blendedPixels[i] = car.getPixelData()[i];
    }
    channelSeparator(car.getSize(), 2, blendedPixels, blendedPixels);
    writeData("output/part8_r", car, blendedPixels);
    for (int i = 0; i < car.getSize(); i++) {
        blendedPixels[i] = car.getPixelData()[i];
    }
    channelSeparator(car.getSize(), 1, blendedPixels, blendedPixels);
    writeData("output/part8_g", car, blendedPixels);
    for (int i = 0; i < car.getSize(); i++) {
        blendedPixels[i] = car.getPixelData()[i];
    }
    channelSeparator(car.getSize(), 0, blendedPixels, blendedPixels);
    writeData("output/part8_b", car, blendedPixels);

    //part 9
    TgaData layer_red = readData("input/layer_red.tga");
    TgaData layer_green = readData("input/layer_green.tga");
    TgaData layer_blue = readData("input/layer_blue.tga");
    firstTgaPixels = layer_red.getPixelData();
    secondTgaPixels = layer_green.getPixelData();
    thirdTgaPixels = layer_blue.getPixelData();
    blendedPixels = new unsigned char[layer_red.getSize()];
    for(int i = 2; i < layer_red.getSize(); i+=3){
        blendedPixels[i] = firstTgaPixels[i];
    }
    for(int i = 1; i < layer_green.getSize(); i+=3){
        blendedPixels[i] = secondTgaPixels[i];
    }
    for(int i = 0; i < layer_blue.getSize(); i+=3){
        blendedPixels[i] = thirdTgaPixels[i];
    }
    writeData("output/part9", layer_red, blendedPixels);

    //part 10
    TgaData text2 = readData("input/text2.tga");
    firstTgaPixels = text2.getPixelData();
    blendedPixels = new unsigned char[text2.getSize()];
    int index = 0;
    for (int i = text2.getSize() - 3; i >=0; i-=3) {
        blendedPixels[i] = firstTgaPixels[index];
        index += 3;
    }
    index = 1;
    for (int i = text2.getSize() - 2; i >=0; i-=3) {
        blendedPixels[i] = firstTgaPixels[index];
        index += 3;
    }
    index = 2;
    for (int i = text2.getSize() - 1; i >=0; i-=3) {
        blendedPixels[i] = firstTgaPixels[index];
        index += 3;
    }
    writeData("output/part10", text2, blendedPixels);

    //testing
    /*TgaData example1 = readData("examples/EXAMPLE_part1.tga");
    TgaData part1 = readData("output/part1.tga");
    if(compare(example1, part1)){
        cout << "Task 1 passed" << endl;
    }
    else{
        cout << "Task 1 failed" << endl;
    }
    TgaData example2 = readData("examples/EXAMPLE_part2.tga");
    TgaData part2 = readData("output/part2.tga");
    if(compare(example2, part2)){
        cout << "Task 2 passed" << endl;
    }
    else{
        cout << "Task 2 failed" << endl;
    }
    TgaData example3 = readData("examples/EXAMPLE_part3.tga");
    TgaData part3 = readData("output/part3.tga");
    if(compare(example3, part3)){
        cout << "Task 3 passed" << endl;
    }
    else{
        cout << "Task 3 failed" << endl;
    }
    TgaData example4 = readData("examples/EXAMPLE_part4.tga");
    TgaData part4 = readData("output/part4.tga");
    if(compare(example4, part4)){
        cout << "Task 4 passed" << endl;
    }
    else{
        cout << "Task 4 failed" << endl;
    }
    TgaData example5 = readData("examples/EXAMPLE_part5.tga");
    TgaData part5 = readData("output/part5.tga");
    if(compare(example5, part5)){
        cout << "Task 5 passed" << endl;
    }
    else{
        cout << "Task 5 failed" << endl;
    }
    TgaData example6 = readData("examples/EXAMPLE_part6.tga");
    TgaData part6 = readData("output/part6.tga");
    if(compare(example6, part6)){
        cout << "Task 6 passed" << endl;
    }
    else{
        cout << "Task 6 failed" << endl;
    }
    TgaData example7 = readData("examples/EXAMPLE_part7.tga");
    TgaData part7 = readData("output/part7.tga");
    if(compare(example7, part7)){
        cout << "Task 7 passed" << endl;
    }
    else{
        cout << "Task 7 failed" << endl;
    }
    TgaData example8_r = readData("examples/EXAMPLE_part8_r.tga");
    TgaData part8_r = readData("output/part8_r.tga");
    TgaData example8_g = readData("examples/EXAMPLE_part8_g.tga");
    TgaData part8_g = readData("output/part8_g.tga");
    TgaData example8_b = readData("examples/EXAMPLE_part8_b.tga");
    TgaData part8_b = readData("output/part8_b.tga");
    if(compare(example8_r, part8_r)&&compare(example8_g, part8_g)&&compare(example8_b, part8_b)){
        cout << "Task 8 passed" << endl;
    }
    else{
        cout << "Task 8 failed" << endl;
    }
    TgaData example9 = readData("examples/EXAMPLE_part9.tga");
    TgaData part9 = readData("output/part9.tga");
    if(compare(example9, part9)){
        cout << "Task 9 passed" << endl;
    }
    else{
        cout << "Task 9 failed" << endl;
    }
    TgaData example10 = readData("examples/EXAMPLE_part10.tga");
    TgaData part10 = readData("output/part10.tga");
    if(compare(example10, part10)){
        cout << "Task 10 passed" << endl;
    }
    else{
        cout << "Task 10 failed" << endl;
    }*/
}
