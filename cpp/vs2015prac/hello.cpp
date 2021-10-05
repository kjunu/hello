#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

#include "device.hpp"

const DWORD MS_VC_EXCEPTION = 0x406D1388;
#pragma pack(push, 8)
typedef struct THREADNAME_INFO {
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void _SetThreadName(DWORD threadId, const char* threadName) {
	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = threadId;
	info.dwFlags = 0;
	__try {
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
	}
}
void set_thread_name(boost::thread::id threadId, std::string threadName) {
	// convert string to char*
	const char* cchar = threadName.c_str();
	// convert HEX string to DWORD
	unsigned int dwThreadId;
	std::stringstream ss;
	ss << std::hex << threadId;
	ss >> dwThreadId;
	// set thread name
	_SetThreadName((DWORD)dwThreadId, cchar);
}
using namespace std;

int main(int argc, char* argv[])
{
	boost::asio::io_service work_io;
	device* first_device = new device();

	boost::asio::deadline_timer t(work_io, boost::posix_time::seconds(2));

	boost::thread thread1(boost::bind(&boost::asio::io_service::run, &work_io));
	set_thread_name(thread1.get_id(), "jw");

	t.async_wait(boost::bind(&device::connect, first_device));
	boost::uuids::uuid& uuid = first_device->get_id();
	cout << "hello" << endl;
	cout << boost::lexical_cast<string> (uuid) << endl;

	thread1.join();
	return 0;
}