#include "device.hpp"

#include <windows.h>

device::device() :
	id_(boost::uuids::random_generator()())
{
}

device::~device()
{
}

boost::uuids::uuid& device::get_id()
{
	return id_;
}

void device::connect()
{
	Sleep(1);
	std::cout << boost::lexical_cast<std::string> (id_) << std::endl;
}