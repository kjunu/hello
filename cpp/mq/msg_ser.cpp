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

	message_queue::remove(MQ_TO_SERVER);
	message_queue::remove(MQ_TO_CLIENT);
	message_queue req_mq( open_or_create, MQ_TO_SERVER, 100, 256);
	message_queue res_mq( open_or_create, MQ_TO_CLIENT, 100, 256);

	std::cout << "handle" << std::endl;
	while(1)
	{
		if(req_mq.get_num_msg() > 0)
		{
			req_mq.receive(buf, 256, recved, priority);
			std::cout << "recv-ed " << buf << std::endl;
			res_mq.send(buf, recved, 0);
		}
	}
}
int main() {
	// Create a server endpoint
	std::cout << "start server" << std::endl;
	boost::thread th = boost::thread(handle_msgqueue_server);
	std::cout << "thread start" << std::endl;
	//handle_msgqueue_server();
	th.join();
	std::cout << "end server" <<  std::endl;
	//handle_msgqueue_server();
}
