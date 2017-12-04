#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>

class human {
public:
	human(std::string name)
		: name_(name)
	{
		std::cout << "born:" << name_ << std::endl;
	}
	~human()
	{
		std::cout << "dead:" << name_ << std::endl;
	}
	void set_name(std::string name)
	{
		name_ = name;
	}
	std::string get_name()
	{
		return name_;
	}
private:
	std::string name_;
};


std::shared_ptr<human> create_human(std::string name)
{
	std::shared_ptr<human> A(new human(name));
	return A;
}
void do_something(std::shared_ptr<human> h)
{
	sleep(5);
	std::cout << "do_something during 5" << h->get_name() << std::endl;
	
}

int main()
{
	std::shared_ptr<human> a = create_human("a");

	std::cout << "hello " << a->get_name() << std::endl;
	
	create_human("b");
	
	boost::thread thread1(&do_something, a);
	sleep(1);
	boost::thread thread2(&do_something, a);
	std::cout << "hello " << (create_human("c"))->get_name() << std::endl;
	thread1.join();
	thread2.join();
	return 0;
}
