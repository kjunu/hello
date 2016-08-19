#include <boost/thread/thread.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>

#include "msgq.h"

void handle_msgqueue_server()
{
	using namespace boost::interprocess;
	char buf[256] ={0,};
	unsigned int priority;
	size_t recved;

	message_queue::remove("jw test msgq");
	message_queue mq( open_or_create, "jw test msgq", 100, 256);

	while(1)
	{
		if(mq.get_num_msg() >0)
		{
			mq.receive(buf, 256, recved, priority);
			std::cout << "recv-ed " << buf << std::endl;
			mq.send(buf, recved, 0);
		}
	}

}
int main() {
	// Create a server endpoint
	//boost::thread th = boost::thread(handle_msgqueue_server);
	handle_msgqueue_server();
}
