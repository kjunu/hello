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
#define MAX_NUM 500000

int id[MAX_NUM] = {0,};

int main(int argc, char** argv)
{
	TRACE("start");
	int find = 1;
	int i = 0;
	int j = 0;
	for(j = 0; j < 10000 ; ++j){
		for(i = 0; i < MAX_NUM ; ++i){
			if(id[i] == find){
				break;
			}
		}
	}
	std::cout << i <<std::endl;
	std::cout << j <<std::endl;
	TRACE("end");
	return 0;
}
