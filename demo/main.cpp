#include <iostream>
#include "ovo.h"

int main(int argc, char const *argv[])
{
	ovo::info i;

	i.hi();
	std::cout << i.version << std::endl;
    i.detail();
	return 0;
}
