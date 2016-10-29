// Hello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

int main()
{
	std::string name;
	std::cout << "Hello World!!!\n";
	std::cout << "Who are you? ";
	std::cin >> name;
	std::cout << "Hello " << name << '\n';
	getchar();
    return 0;
}

