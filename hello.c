#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[])
{
    uint8_t data[32] = {'a','b','c','9','0','7'};
	char char_array[16] = {'i','d','t','e','s','t'};
	//char* char_array = "test it";
	char* id = char_array;
	char* test = char_array+3;
	std::string my_str = boost::lexical_cast<std::string>(id);	
	printf("hello world\n");
    std::cout << data <<std::endl;
    std::cout << id <<std::endl;
    std::cout << test <<std::endl;
    std::cout << my_str <<std::endl;
	return 0;
}
