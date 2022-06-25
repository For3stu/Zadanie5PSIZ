#pragma pack(1)

#include <iostream>
#include <fstream>
#include <vector>
#include "bmp.h"

using namespace std;

vector<char> buffer;
PBITMAPFILEHEADER file_header;
PBITMAPINFOHEADER info_header;


void fill() {
    ifstream file("test.bmp");

    if (file) {
        file.seekg(0, std::ios::end);
        streampos length = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.resize(length);
        file.read(&buffer[0], length);

        file_header = (PBITMAPFILEHEADER)(&buffer[0]);
        info_header = (PBITMAPINFOHEADER)(&buffer[0] + sizeof(BITMAPFILEHEADER));
    }
}

int main() {

    fill();
    cout << "buffer: ";
    cout << buffer[0] << buffer[1] << endl;
    cout << "Rozmiar : ";
    cout << file_header->bfSize << endl;
    cout << "Szerokosc: ";
    cout << info_header->biWidth << endl;
    cout << "Wysokosc: ";
    cout << info_header->biHeight << endl;
    cout << "Liczba platkow: ";
    cout << info_header->biPlanes << endl;
    cout << "Liczba bitow na piksel: ";
    cout << info_header->biBitCount << endl;
    cout << "Kompresja: ";
    cout << info_header->biCompression << endl;
    cout << "Rozmiar samego rysunku: ";
    cout << info_header->biSizeImage << endl;
    cout << "Rozdzielczosc pozioma: ";
    cout << info_header->biXPelsPerMeter << endl;
    cout << "Rozdzielczosc pionowa: ";
    cout << info_header->biYPelsPerMeter << endl;
    cout << "Liczba kolorow w palecie: ";
    cout << info_header->biClrUsed << endl;
    cout << "Wazne kolory w palecie: ";
    cout << info_header->biClrImportant << endl;

    return 0;
}