#include <stdio.h>
#include <iostream>
#include <stdint.h>
int main(int argc, char* argv[])
{
    uint8_t data[32] = {'a','b','c','9','0','7'};
	printf("hello world\n");
    std::cout << data <<std::endl;
	return 0;
}
