#include <iostream>
#include <time.h>
#include <boost/shared_ptr.hpp>
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
	//TRACE("callback sleep...1");
	sleep(1);
	TRACE("good morning callback! after 1");
}
class testman
	: public boost::enable_shared_from_this<testman>
{
public:
	std::string name;
	boost::asio::io_service io;
	boost::shared_ptr<boost::asio::io_service::work> work_ptr;
	testman(){
		testman("static jw");
	}
	testman(const std::string& n){
		name = n;
		TRACE(name);
	}
	static void postcallback()
	{
		TRACE("postcallback()");
		sleep(1);
		TRACE("hello! after 1");
	}
	int test_asio()
	{
		TRACE("start");
		work_ptr.reset(new boost::asio::io_service::work(io));
		boost::thread thread1(boost::bind(&boost::asio::io_service::run, &io));
		//boost::thread thread2(boost::bind(&boost::asio::io_service::run, &io));
		
		//for (int i = 0 ; i < 3000000; i ++ )
		{
		boost::shared_ptr<boost::asio::deadline_timer> t(new boost::asio::deadline_timer(io));//, boost::posix_time::seconds(2));
		boost::asio::deadline_timer t2(io);//, boost::posix_time::seconds(2));
		//boost::asio::steady_timer t(io);

		t->expires_from_now(boost::posix_time::seconds(10));
		TRACE("set timer 1");
		//t2.expires_from_now(boost::posix_time::seconds(1));
		//TRACE("set timer 2");
		t->async_wait(&callback);
		//t->cancel();
		//t2.async_wait(&callback);
		//boost::thread thread2(boost::bind(&boost::asio::io_service::run, &io));
		//testman jw("jw");
		//io.post(&testman::postcallback);
		sleep(1);
		size_t cnt = t->cancel();
		//t.reset(new boost::asio::deadline_timer(io));
		std::cout << "test main slept 1 : cancel cnt = " << cnt << std::endl;
		t->expires_from_now(boost::posix_time::seconds(1));
		t->async_wait(&callback);
		}
		work_ptr.reset();
		thread1.join();
		//thread2.join();
		TRACE("test main end");
	}
};

int main()
{
	testman jw;
	return jw.test_asio();
}
