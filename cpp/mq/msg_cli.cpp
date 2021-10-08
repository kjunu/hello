#include <boost/program_options.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>

#include "msgq.h"

using namespace std; 

int main(int argc, char* argv[])
{

	using namespace boost::interprocess;

	namespace po = boost::program_options;

#define BUF_SIZE 256
	char buf[BUF_SIZE] = {0,};
	size_t recv_byte = 0;
	unsigned int priority = 0;

	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help,h", "produce help message")
			//("device_connection_map,d", po::value<int>(), "set compression level");
			("device_connection_map,d", "show device conneciton map info");

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		int qry = 0; 
		if (vm.count("device_connection_map")) {
			qry = MQ_DEV_CONN_INFO;
		} else {
			cout << desc << endl;
			return 0;
		}
		
		message_queue req_mq( open_only, MQ_TO_SERVER);
		message_queue res_mq( open_only, MQ_TO_CLIENT);
		req_mq.send((void*)&qry, sizeof(qry), 0);
		while(1) {
			if(res_mq.get_num_msg() > 0) {
				res_mq.receive(buf, BUF_SIZE, recv_byte, priority);
				if ( recv_byte > BUF_SIZE ) {
					cout << "recved byte : "<< recv_byte << endl;
					throw 1;
				}
				break;
			}
		}
		cout << buf << endl;
	
	}
	catch (int err_no) {
		cout << "internal error no : " << err_no << endl;
	}
	catch (exception &e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

