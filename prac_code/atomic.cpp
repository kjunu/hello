#include <iostream>
#include <thread>
//#include <atomic>
#include <boost/atomic.hpp>

//std::atomic<long long> data;
boost::atomic<int> data;
bool exchanged = false;
static const int create= 1;
static const int complete= 20;
static const int post_complete= 30;
void do_work()
{
	//data.fetch_add(1, std::memory_order_relaxed);
	//static int complete_local = 1;
	//static int post_complete = 3;
	int complete_local = complete;
	std::cout << "do_work()---start---" << data <<'\n';
	std::cout 
		<< "data:" << data
		<< ",complete_local:" << complete_local 
		<< ",post_complete:" << post_complete 
		<< ",exchanged:" << exchanged 
		<< std::endl;
	exchanged = data.compare_exchange_strong(complete_local, post_complete);	
	if (exchanged) {
		std::cout << "***************************changed:" << data << '\n';
	}
	std::cout 
		<< "data:" << data
		<< ",complete_local:" << complete_local 
		<< ",post_complete:" << post_complete 
		<< ",exchanged:" << exchanged 
		<< std::endl;
	std::cout << "do_work()--- end ---" << data <<'\n';
}

int main()
{
	data = complete;
	std::thread th1(do_work);
	std::thread th2(do_work);
	std::thread th3(do_work);
	std::thread th4(do_work);
	std::thread th5(do_work);

	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();

	std::cout << "Result:" << data << '\n';
}
