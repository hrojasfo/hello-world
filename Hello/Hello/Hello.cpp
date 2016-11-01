// Hello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

int get_info(char *arr, int offset, int size) {
	if (size > 4) {
		std::cout << "Error cant read more that 4 bytes into integer\n";
		return -1;
	}
	int result = 0;
	for (int i = 0; i < size; ++i) {
		result |= arr[offset + i] << (8 * i) ;
	}
	return result;
}

class BMP {
	std::ifstream image;
	char *memblock;
public:
	~BMP() {
		delete[] memblock;
	}
	void read_bmp(std::string path) {
		image.open(path, std::ios::binary | std::ios::ate);
		if (image.is_open()) {
			int size = image.tellg();
			memblock = new char[size];
			image.seekg(0, std::ios::beg);
			image.read(memblock, size);
			std::cout << "File size " << size << '\n';
			image.close();
		}
		else {
			std::cout << "-E- Can't open file\n";
		}
	}
	void print_bmp() {
		int offset = get_info(memblock, 0xa, 4);
		int w = get_info(memblock, 0x12, 4);
		int h = get_info(memblock, 0x16, 4);
		int ps = get_info(memblock, 0x1c, 4);

		int row_size = floor((ps * w + 31) / 32) * 4;
		std::cout << "Row size " << row_size << '\n';
		for (int i = h - 1; i >= 0; --i) {
			for (int j = 0; j < w; ++j) {
				int pixel = (j % 2 == 0) ? memblock[offset + (row_size * i) + (j / 2)] >> 4 : memblock[offset + (row_size * i) + (j / 2)];
				pixel &= 0xf;
				std::cout << (char)((pixel == 15) ? '.' : '*') << ' ';
			}
			std::cout << '\n';
		}
	}
};

int main()
{
	std::string path = "C:\\Users\\rojashe\\Documents\\NNA";
	BMP bmp;
	//bmp.read_bmp(path + "\\1_1.bmp");
	//bmp.print_bmp();
	std::string input;
	while(true) {
		std::cout << "Enter bmp file: ";
		std::cin >> input;
		if (input == "quit") {
			break;
		}
		else {
			bmp.read_bmp(path + "\\" + input + ".bmp");
			bmp.print_bmp();
		}
	} 
    return 0;
}

