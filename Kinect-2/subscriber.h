#include <mutex>

#include "yal.h"

#ifndef __SUBSCRIBER__
#define __SUBSCRIBER__

template <class T> class subscriber
{
	template<class T> friend class publisher;
public:
	subscriber()
	{
	}

	~subscriber()
	{
	}

	virtual void callback(T data) = 0;
private:
	void publisher_callback(T data)
	{
		mtx.lock();
		this->callback(data);
		mtx.unlock();
	}

	std::mutex mtx;
};

#endif