#include <iostream>

template <typename T>
class Vector
{
private:
	T* _array;
	int _size;
	int _capacity;
public:

	//Constructor
	Vector(int capacity)
	{
		_capacity = capacity;
		_size = 0;
		//Выделяем сырую память
		T* new_array = reinterpret_cast<T*> (new char[_capacity * sizeof(T)]);
		_array = new_array;
	}

	//Copy constructor done!
	Vector(Vector& vector)
	{
		_size = vector._size;
		_capacity = vector._capacity;
		T* new_array;
		new_array = reinterpret_cast<T*> (new char[_capacity * sizeof(T)]);
		for (int i = 0; i < vector._size; ++i)
			new (new_array + i) T(vector._array[i]);
		_array = new_array;
	}

	//Move-copy constructor done!
	Vector(Vector&& vector)
	{
		std::swap(_capacity, vector._capacity);
		std::swap(_size, vector._size);
		std::swap(_array, vector._array);
	}

	~Vector()
	{
		for (int i = 0; i < this->_size; ++i)
			_array[i].~T();
		delete[]reinterpret_cast<char*>(_array);
	};

	//to do!!!
	void resize(int new_size, T& value = T())
	{
		if (new_size > _capacity)
		{
			T* new_array = reinterpret_cast<T*> (new char[new_size * sizeof(T)]);
			for (int i = 0; i < _size; ++i)
				new (new_array + i) T(_array[i]);
			//std::cout << "\nFirst\n";
			//this->printAllInfo();
			for (int i = _size; i < new_size; ++i)
				new (new_array + i) T(value);
			//std::cout << "\nSecond\n";
			//this->printAllInfo();

			for (int i = 0; i < this->_size; ++i)
				_array[i].~T();
			//Check
			/*delete[]reinterpret_cast<char*>(_array);*/

			this->_array = new_array;
			this->_capacity = new_size;
			this->_size = new_size;
		}
		else
		{
			for (int i = _size; i < new_size; ++i)
				_array[i] = value;
			_size = new_size;
		}
	}

	void printAllInfo()
	{
		for (int i = 0; i < _size; ++i)
			std::cout << _array[i];
		std::cout << "\nSize: " << _size << "\nCapacity: " << _capacity << "\n";
	}
};

int main()
{
	Vector<int> vec1(Vector<int>(7));
	Vector<int> vec2(vec1);
	int nine = 9, six = 6;
	vec1.resize(9, nine);
	vec2.resize(6, six);
	/*vec2.printAllInfo();*/
	Vector<int> vec3(vec2);
	/*vec3.printAllInfo();*/
	vec3.resize(9, nine);
	vec1.printAllInfo();
	vec2.printAllInfo();
	vec3.printAllInfo();

	return 0;
}