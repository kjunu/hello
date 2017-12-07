#include <iostream>
#include <time.h>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/function.hpp>
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
	TRACE("callback sleep...1");
	sleep(1);
	//TRACE("good morning callback! after 1");
}

class testman
	: public boost::enable_shared_from_this<testman>
{
public:
	std::string name;
	boost::asio::io_service io;
	boost::shared_ptr<boost::asio::io_service::work> work_ptr;

	testman()
	{
		testman("static jw");
	}
	
	testman(const std::string n)
	{
		name = n;
		TRACE(name);
		//bad
		//func = boost::bind(&testman::bindfunc, this, _1, _2);
	}

	static void postcallback()
	{
		TRACE("postcallback()");
		sleep(1);
		TRACE("hello! after 1");
	}

	void bindfunc(std::string a, int b)
	{
		TRACE(" bind a=" + a + ",b="+  std::to_string(b));
		sleep(1);
	}

	int test_asio()
	{
		TRACE("start");
		work_ptr.reset(new boost::asio::io_service::work(io));
		boost::thread thread1(boost::bind(&boost::asio::io_service::run, &io));
		boost::shared_ptr<boost::asio::deadline_timer> t(new boost::asio::deadline_timer(io));//, boost::posix_time::seconds(2));
		boost::asio::deadline_timer t2(io);//, boost::posix_time::seconds(2));
		//boost::asio::steady_timer t(io);

		size_t cnt = t->cancel();
		//size_t cnt = 0; //t->cancel();
		t->expires_from_now(boost::posix_time::seconds(2));
		TRACE("set timer 2");
		//t2.expires_from_now(boost::posix_time::seconds(1));
		//TRACE("set timer 2");
		t->async_wait(&callback);
		//sleep(1);
		//t->cancel();
		//t2.async_wait(&callback);
		//boost::thread thread2(boost::bind(&boost::asio::io_service::run, &io));
		//testman jw("jw");
		//io.post(&testman::postcallback);
		std::string a = "a";
		int b = 0xb;
		//io.post(boost::bind(&testman::bindfunc, this, boost::ref(a), b));
		sleep(3);
		
		//bad
		func(a, b);
		TRACE("main slept 4, a=" + a);
		std::cout << "cancel cnt = " << cnt << std::endl;
		work_ptr.reset();
		thread1.join();
		//thread2.join();
		TRACE("test main end");
		return 0;
	}
	void set_func(boost::function<void(std::string, int)> f)
	{
		func = f;
	}
	boost::function<void(std::string, int)> func;
};
class player
{
	public:
		player(testman& man)
		{
			//man.func = boost::bind(&player::play, this, _1, _2);
			man.set_func(boost::bind(&player::play, this, _1, _2));
		}
		void play(std::string name, int age)
		{
			TRACE(" name=" + name + ",age="+  std::to_string(age));
		}
};
int main()
{
	testman jw;
	player p(jw);
	return jw.test_asio();
}
