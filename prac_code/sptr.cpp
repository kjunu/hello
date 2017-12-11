#include <iostream>
#include <memory>
#include <boost/thread/thread.hpp>

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#define TIMESTAMP std::cout << static_cast<unsigned int>(time(0)) - cur_time
#define TRACE(x) TIMESTAMP << "(" << gettid() << ")"<< __func__ << ":"<< (x) << std::endl
static unsigned int cur_time = static_cast<unsigned int>(time(0));

class human {
public:
	human(std::string name)
		: name_(name)
	{
		//std::cout << "born:" << name_ << std::endl;
		TRACE("born:"+name_);
	}
	~human()
	{
		//std::cout << "dead:" << name_ << std::endl;
		TRACE("dead:"+name_);
		name_="fuck";
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
	std::shared_ptr<human> h(new human(name));
	return h;
}
void do_something(std::shared_ptr<human> h)
{
	sleep(5);
	//std::cout << "do_something with share_ptr during 5 : name = " << h->get_name() << std::endl;
	TRACE("do with shared_ptr 5 : name = " + h->get_name());
}

void do_something_ref(human& h)
{
	sleep(5);
	//std::cout << "do_something with reference during 5 : name = " << h.get_name() << std::endl;
	TRACE("do with ref 5 : name = " + h.get_name());
}

int main()
{
	std::shared_ptr<human> a = create_human("a");

	TRACE("hello " + a->get_name());
	
	//create_human("b");
	
	//boost::thread thread1(&do_something_ref, *a.get());
	boost::thread thread1(&do_something, a);
	sleep(1);
	//boost::thread thread2(&do_something, a);
	TRACE("hello " + a->get_name());
	do_something_ref(*a.get());
	TRACE("hello " + (*(a.get())).get_name());
	//std::cout << "hello " << (create_human("c"))->get_name() << std::endl;
	thread1.join();
	//thread2.join();
	return 0;
}
