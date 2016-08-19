#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)


using boost::asio::ip::tcp;

class session
{
	public:
		session(boost::asio::io_service& io_service)
			: socket_(io_service)
		{
			std::cout << "session constructor : " << gettid() << "\n";
		}

		tcp::socket& socket()
		{
			return socket_;
		}

		void start()
		{
			std::cout << "session start: " << gettid() << "\n";
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
									boost::bind(&session::handle_read, this,
												boost::asio::placeholders::error,
												boost::asio::placeholders::bytes_transferred));
		}

	private:
		void handle_read(const boost::system::error_code& error,
						 size_t bytes_transferred)
		{
			if (!error)
			{
				std::cout << "session handle_read: " << gettid() << "\t" << data_ << "\n";
				std::cout << "bytes_transfer " <<bytes_transferred << "\n";
;
				boost::asio::async_write(socket_,
										 boost::asio::buffer(data_, bytes_transferred),
										 boost::bind(&session::handle_write, this,
													 boost::asio::placeholders::error));
			}
			else
			{
				delete this;
			}
		}

		void handle_write(const boost::system::error_code& error)
		{
			if (!error)
			{
				std::cout << "session handle_write: " << gettid() << "\n";
				std::cout << "bytes_transfer " <<boost::asio::placeholders::bytes_transferred << "\n";
;
				socket_.async_read_some(boost::asio::buffer(data_, max_length),
										boost::bind(&session::handle_read, this,
													boost::asio::placeholders::error,
													boost::asio::placeholders::bytes_transferred));
			}
			else
			{
				delete this;
			}
		}

		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_[max_length];
};

class server {
public:
	server(boost::asio::io_service& io_service, short port)
		: io_service_(io_service),
		  acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
	{
		std::cout << "server constructor : " << gettid() << "\n";
		start_accept();
	}

private:
	void start_accept()
	{
		session* new_session = new session(io_service_);
		std::cout << "start accept: " << gettid() << "\n";
		acceptor_.async_accept(new_session->socket(),
							   boost::bind(&server::handle_accept, this, new_session,
										   boost::asio::placeholders::error));
	}
	void handle_accept(session* new_session,
					   const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "handle accept: " << gettid() << "\n";
			new_session->start();
		}
		else
		{
			delete new_session;
		}

		start_accept();
	}

	boost::asio::io_service& io_service_;
	tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: async_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		using namespace std; // For atoi.
		server s(io_service, atoi(argv[1]));
		//boost::bind(&boost::asio::io_service::run, &io_service);
		boost::thread server_thread(boost::bind(&boost::asio::io_service::run, &io_service));
		boost::thread server_thread1(boost::bind(&boost::asio::io_service::run, &io_service));
		boost::thread server_thread2(boost::bind(&boost::asio::io_service::run, &io_service));
		//new boost::thread(&(io_service.run));
		//io_service.run();
		server_thread.join();
		server_thread1.join();
		server_thread2.join();

	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}

