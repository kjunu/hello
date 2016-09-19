#pragma once
#include <iostream>

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class device
{
public:
	device();
	~device();
	boost::uuids::uuid& get_id();
	void connect();
private:
	boost::uuids::uuid id_;
};