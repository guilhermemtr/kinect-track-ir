#include <list>

#include "yal.h"
#include "subscriber.h"

// not thread safe
template <class T> class publisher
{
public:
	publisher()
	{
		subs = {};
	}

	~publisher()
	{
		subs = {};
	}

	void add_subscriber(subscriber<T> *s)
	{
		subs.push_front(s);
	}

	void publish(T data)
	{
		for (subscriber<T>* sub : subs)
		{
			sub->publisher_callback(data);
		}
	}

private:
	std::list<subscriber<T>*> subs;
};

