#define _CRT_SECURE_NO_WARNINGS
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
    std::ifstream file("test.bmp");

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

void Negatyw(const char* plik) 
{

    FILE* test = fopen(plik, "rb");
    FILE* neg = fopen("negatyw.bmp", "wb");

    if (neg == nullptr)
    {
        cout << endl << "Nie udalo sie otworzyc pliku!" << endl;
    }
    else
    {
        cout << endl << "Tworzenie negatywu..." << endl;

        fseek(neg, 0, SEEK_SET);
        fwrite(&file_header->bfType, sizeof(file_header->bfType), 1, neg);
        fwrite(&file_header->bfSize, sizeof(file_header->bfSize), 1, neg);
        fwrite(&file_header->bfReserved1, sizeof(file_header->bfReserved1), 1, neg);
        fwrite(&file_header->bfReserved2, sizeof(file_header->bfReserved2), 1, neg);
        fwrite(&file_header->bfOffBits, sizeof(file_header->bfOffBits), 1, neg);


        fseek(neg, 14, SEEK_SET);
        fwrite(&info_header->biSize, sizeof(info_header->biSize), 1, neg);
        fwrite(&info_header->biWidth, sizeof(info_header->biWidth), 1, neg);
        fwrite(&info_header->biHeight, sizeof(info_header->biHeight), 1, neg);
        fwrite(&info_header->biPlanes, sizeof(info_header->biPlanes), 1, neg);
        fwrite(&info_header->biBitCount, sizeof(info_header->biBitCount), 1, neg);
        fwrite(&info_header->biCompression, sizeof(info_header->biCompression), 1, neg);
        fwrite(&info_header->biSizeImage, sizeof(info_header->biSizeImage), 1, neg);
        fwrite(&info_header->biXPelsPerMeter, sizeof(info_header->biXPelsPerMeter), 1, neg);
        fwrite(&info_header->biYPelsPerMeter, sizeof(info_header->biYPelsPerMeter), 1, neg);
        fwrite(&info_header->biClrUsed, sizeof(info_header->biClrUsed), 1, neg);
        fwrite(&info_header->biClrImportant, sizeof(info_header->biClrImportant), 1, neg);


        fseek(neg, sizeof(file_header->bfOffBits), SEEK_SET);

        int Obraz;
        for (int i = file_header->bfOffBits; i < file_header->bfSize; i++)
        {
            fseek(test, i, SEEK_SET);
            fseek(neg, i, SEEK_SET);
            fread(&Obraz, 3, 1, test);
            Obraz = INT_MAX - Obraz;
            fwrite(&Obraz, 3, 1, neg);
        }

        cout << endl;
        fclose(test);
        fclose(neg);
    }
}


int main(int arc, char* argv[]) {
    const char* plik;
        
    if (argv[1] == nullptr)
        plik = "test.bmp"; 
    else
        plik = argv[1];

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

    Negatyw(plik);

    return 0;
}