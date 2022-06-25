#pragma pack(1)

#include <iostream>
#include <fstream>

using namespace std;



void fill() {
    ifstream file("test.bmp");

    if (file) {
        file.seekg(0, std::ios::end);
        streampos length = file.tellg();
        file.seekg(0, std::ios::beg);

    }
}

int main() {

    fill();

    return 0;
}