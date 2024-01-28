#include <iostream>

template <typename T>
class Unique_ptr
{
private:
	T* _ptr;

public:
	Unique_ptr() : _ptr(nullptr) {}

	Unique_ptr(T* new_ptr) : _ptr(new_ptr) {}

	Unique_ptr(T& obj) : _ptr(&obj) {}

	Unique_ptr(const Unique_ptr& other) = delete;

	Unique_ptr& operator =(const Unique_ptr& other) = delete;

	Unique_ptr(Unique_ptr&& other)
	{
		std::swap(this->_ptr, other._ptr);
	}

	Unique_ptr& operator = (Unique_ptr&& other)
	{
		std::swap(this->_ptr, other._ptr);
		return *this;
	}

	T& operator *() {
		return *_ptr;
	}

	~Unique_ptr() { delete _ptr; }

};

template <typename T>
class Shared_ptr
{
private:
	T* _ptr;
	int* _counter = 0;

public:
	Shared_ptr() : _ptr(nullptr),  _counter(0) {}

	Shared_ptr(T* new_ptr) : _ptr(new_ptr), _counter(1) {}

	Shared_ptr(T& obj) : _ptr(&obj), _counter(1){}

	Shared_ptr(const Shared_ptr& other) : _ptr(other._ptr), _counter(++other._counter) {}

	Shared_ptr& operator = (const Shared_ptr& other)
	{
		_ptr = other._ptr;
		_counter = ++other._counter;
		return *this;
	}

	Shared_ptr(Shared_ptr&& other)
	{
		std::swap(_ptr, other._ptr);
	}

	Shared_ptr& operator = (Shared_ptr&& other)
	{
		std::swap(_ptr, other._ptr);
		return *this;
	}

	~Shared_ptr() {
		--_counter;
		if (_counter == 0)
		delete _ptr;
	}
};

int main()
{
	return 0;
}