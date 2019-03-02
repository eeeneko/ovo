#include <iostream>
#include <vector>

#include "ovo.h"

int main(int argc, char const *argv[])
{
	ovo::info i;

	i.hi();
	std::cout << i.version << std::endl;
    i.detail();

    ovo::file f;
    vector<string> fls;
    f.get_files_name(".\\",fls,"*.md",1,1);
    for(int i = 0; i < fls.size(); i++)
    std::cout << fls[i] << endl;

	return 0;
}
