#include <mutex>

#include "yal.h"

template <class T> class subscriber
{
	template<class T> friend class publisher;
public:
	subscriber()
	{
		mtx = std::mutex();
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

