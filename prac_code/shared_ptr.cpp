#include <stdio.h>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

class Test;
//void display_function(boost::shared_ptr<Test> ptr);
void display_function(Test ptr);

class Test //: public boost::enable_shared_from_this<Test>
{
	public:
		explicit Test(int value)  : value_(value) 
		{
			printf("Test constructor\n");
		}

		~Test()
		{
			printf("Test destructor %p\n", this);
		}

		void display()
		{
			//display_function(boost::shared_ptr<Test>(this));
			//display_function(shared_from_this());
			display_function(this);
		}

		void console_out()
		{
			printf("console_out : %d\n", value_);
		}

	private:
		int value_;
};

//void display_function(boost::shared_ptr<Test> ptr)
void display_function(Test &ptr)
{
	//ptr->console_out();
	ptr.console_out();
}

int main()
{
	boost::shared_ptr<Test> s_ptr(new Test(100));
	s_ptr->display();
}
