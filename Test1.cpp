#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
using namespace std;


mutex m;

vector<int> vInt{};

atomic<int> i {0};


template<typename T>
class Lock_Guard
{
public:
	Lock_Guard(T* _t)
	{
		m_t = _t;
		m_t->lock();
	}

	~Lock_Guard()
	{
		m_t->unlock();
	}

private:
	T* m_t{};
};

void PushV()
{
	for(int j = 0 ; j < 20000; ++j)
	{
		Lock_Guard<mutex> LG(&m);
		i++;
		vInt.push_back(i);
	}
}

int main()
{
	thread t1(PushV);
	thread t2(PushV);

	t1.join();
	t2.join();

	cout <<vInt.size();

	return 0;
}