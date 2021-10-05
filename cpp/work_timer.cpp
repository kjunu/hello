#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <sys/syscall.h>
#define gettid() boost::this_thread::get_id() //syscall(SYS_gettid)


#define TRACE_START() std::cout << __func__ << ": start" << std::endl
#define TRACE_END() std::cout << __func__ << ": end" << std::endl
#define TRACE(x) std::cout << __func__ << ":" << (x) << std::endl

void callback(const boost::system::error_code& ec)
{
	TRACE(gettid());
	sleep(3);
	TRACE(ec.message());
}

int test_asio()
{
	TRACE_START();

	boost::asio::io_service io;

	//boost::asio::deadline_timer t(io, boost::posix_time::seconds(3));
	boost::asio::deadline_timer t(io);//, boost::posix_time::seconds(2));
	boost::asio::deadline_timer t2(io);//, boost::posix_time::seconds(2));
	//boost::asio::steady_timer t(io);
	t.expires_from_now(boost::posix_time::seconds(1));
	t2.expires_from_now(boost::posix_time::seconds(2));
	TRACE(gettid());
	TRACE("after sleep");
	t.async_wait(&callback);
	t2.async_wait(&callback);
	boost::thread thread1(boost::bind(&boost::asio::io_service::run, &io));
	boost::thread thread2(boost::bind(&boost::asio::io_service::run, &io));
	//io.run();
	thread1.join();
	thread2.join();
	TRACE("after run");
	TRACE_END();
}

int main()
{
	return test_asio();
}
