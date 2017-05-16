#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <boost/atomic.hpp>

boost::mutex io_mutex; // The iostreams are not guaranteed to be thread-safe!
boost::shared_mutex sh_m; // The iostreams are not guaranteed to be thread-safe!

class counter
{
	public:
		counter() : count(0) { }

		int increment() {
			//boost::unique_lock<boost::mutex> scoped_lock(mutex);
			for (int i = 0 ; i < 10000 ; ++i)
				++count;
			return count;
		}
		void lock() {
		}
		void unlock() {
		}

	private:
		boost::mutex mutex;
		boost::shared_mutex s_mutex;
		boost::atomic<int> count;
};

counter c;

void change_count()
{
	int i = c.increment();
	boost::unique_lock<boost::mutex> scoped_lock(io_mutex);
	std::cout << "count == " << i << std::endl;
}


void sleep_and_print(boost::shared_lock<boost::shared_mutex>& lock_passed)
{
	lock_passed.lock();
	boost::unique_lock<boost::mutex> scoped_lock(io_mutex);
	sleep(1);
	std::cout << "tid = " << std::endl;
	lock_passed.unlock();
}

int main(int, char*[])
{
	const int num_threads = 4;
	boost::thread_group thrds;
	{
		boost::shared_lock<boost::shared_mutex> slock(sh_m);
	for (int i=0; i < num_threads; ++i)
		//thrds.create_thread(&sleep_and_print, boost::ref(slock));
		thrds.create_thread(boost::bind(sleep_and_print, boost::ref(slock)));
	}
	boost::unique_lock<boost::shared_mutex> ulock(sh_m);
	std::cout << "unlock\n" << std::endl;
	thrds.join_all();

	return 0;
}
