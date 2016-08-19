#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
//#include <boost/function_equal.hpp>

class A {
public:
	A() {
	}
	int& get_address_of_a() {
		return a_;
	}
	boost::function<void( int, int )>& callback() {
		std::cout << "callback_:" << boost::addressof(callback_) << std::endl;
		return callback_;
	}
	int a_;
	boost::function<void( int, int )> callback_;
};

void print_plus(int a, int b)
{
	std::cout << a << "+" << b << "=" << a+b << std::endl;
	return;
}
int main(int argc, char *argv[])
{
	std::cout << "hello" << std::endl;
	A class_a;
	//a.callback() = boost::bind(&print_plus,  _1, _2);
	class_a.callback_ = boost::bind(&print_plus,  _1, _2);
	class_a.callback_(1,2);

	class_a.get_address_of_a() = 4;
	
	std::cout << "class_a.a_ : " << class_a.a_ << std::endl;
	return 1;
}


