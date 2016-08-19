#include <iostream>
#include <time.h>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
//#define gettid() boost::this_thread::get_id() //syscall(SYS_gettid)

static unsigned int cur_time = static_cast<unsigned int>(time(0));

#define TRACE_START() std::cout << __func__ << ": start" << std::endl
#define TRACE_END() std::cout << __func__ << ": end" << std::endl

#define TIMESTAMP std::cout << static_cast<unsigned int>(time(0)) - cur_time

#define TRACE(x) TIMESTAMP << "(" << gettid() << ")"<< __func__ << ":"<< (x) << std::endl

void callback(const boost::system::error_code& ec)
{
	TRACE("sleep...");
	sleep(5);
	TRACE("good morning! after 5");
}
class testman
	: public boost::enable_shared_from_this<testman>
{
public:
	std::string name;
	testman(){
		name = "static jw";
	}
	testman(const std::string& n){
		name = n;
		TRACE(name);
	}
	static void postcallback()
	{
		TRACE("sleep...");
		sleep(3);
		TRACE("good morning! after 3");
	}
	int test_asio()
	{
		TRACE("start");

		boost::asio::io_service io;

		//boost::asio::deadline_timer t(io, boost::posix_time::seconds(3));
		boost::asio::deadline_timer t(io);//, boost::posix_time::seconds(2));
		boost::asio::deadline_timer t2(io);//, boost::posix_time::seconds(2));
		//boost::asio::steady_timer t(io);
		t.expires_from_now(boost::posix_time::seconds(1));
		t2.expires_from_now(boost::posix_time::seconds(2));
		TRACE("set timer 1");
		TRACE("set timer 2");
		t.async_wait(&callback);
		t2.async_wait(&callback);
		boost::thread thread1(boost::bind(&boost::asio::io_service::run, &io));
		boost::thread thread2(boost::bind(&boost::asio::io_service::run, &io));
		//io.run();
		//testman jw("jw");
		TRACE("set post");
		//io.post(&testman::postcallback);
		thread1.join();
		thread2.join();
		TRACE("end");
	}
};

int main()
{
	testman jw;
	return jw.test_asio();
}
