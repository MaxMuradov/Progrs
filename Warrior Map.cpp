#include<iostream>
#include<vector>
#include <fstream>


using namespace std;

//rocks - r
//water - w
//forst - f
//town - t

class Map {
private:
	class Hash_func {
	private:
		int a;
		int b;
		int c;
		int size;

	public:
		Hash_func() = default;

		void set_hash(int size)
		{
			a = rand();
			b = rand();
			c = 997;
			this->size = size;
		}

		int get_hash(int value)
		{
			if (size > 0)
				return (a * value + b) % c % size;
			else
				return -1;
		}
	};

	class Bucket {
	private:
		class Optional
		{
		private:
			int _index;
			char obj;
			bool _has_obj;
		public:
			Optional(char ch, int index) : obj(ch), _has_obj(true), _index(index) {};

			Optional() : _has_obj(false) {};


			//оно ссылалось на копиконструктор
			Optional(const Optional& other)
			{
				this->_has_obj = other._has_obj;
				if (_has_obj)
				{
					this->_index = other._index;
					this->obj = other.obj;
				}
			}


			bool has_obj()
			{
				return _has_obj;
			}

			char get_obj() {
				return obj;
			}

			int get_index()
			{
				return _index;
			}

			void operator = (Optional&& other)
			{
				this->_has_obj = other._has_obj;
				if (_has_obj)
				{
					this->_index = other._index;
					this->obj = other.obj;
				}
			}

			void print_op()
			{
				if (_has_obj)
				{
					cout << obj << " :: " << _index;
				}
			}
		};
		vector<Optional> insidevec;
		Hash_func f2;

		bool isgood(const vector<int>& vals)
		{
			vector<int> hashval;
			bool b = true;
			for (int i = 0; i < vals.size(); ++i)
				hashval.push_back(f2.get_hash(vals[i]));
			for (int i = 0; i < vals.size() - 1; ++i)
				for (int j = i + 1; j < vals.size(); ++j)
					if (hashval[i] == hashval[j])// была ошибка
						b = false;
			return b;
		}

	public:
		Bucket() = default;

		void Bucket_build(const vector<int>& vals, const vector<char>& charvec)
		{
			int index;
			do
			{
				insidevec.clear();
				insidevec.resize(vals.size() * vals.size());
				f2.set_hash(insidevec.size());
				for (int i = 0; i < vals.size(); ++i)
				{
					insidevec[f2.get_hash(vals[i])] = Optional(charvec[i], vals[i]);
				}
			} while (!isgood(vals));
		}

		char find_bucket(int index)
		{
			if (f2.get_hash(index) != -1)
			{
				if (insidevec[f2.get_hash(index)].get_index() == index)//была ошибка
					return insidevec[f2.get_hash(index)].get_obj();
				else
					return 'O';
			}
			else
				return 'O';
		}

		void print_buc()
		{
			int index = 0;
			for (auto i : insidevec)
			{
				cout << index++ << ": ";
				i.print_op();
				cout << "\n";
			}
		}

	};

	class Fixed_set {
	private:
		vector<Bucket>outvec;
		Hash_func f1;

		bool isgood(const vector<int>& vals)
		{
			int result = 0;
			vector<int> distrvec;
			distrvec.resize(outvec.size(), 0);
			for (int i = 0; i < vals.size(); ++i)
				++distrvec[f1.get_hash(vals[i])];
			for (int i = 0; i < distrvec.size(); ++i)
				result += distrvec[i] * distrvec[i];
			return (result < outvec.size() * 4);
		}

	public:
		Fixed_set() = default;

		void Fixed_set_build(const vector<int>& vals, const vector<char>& charvec)
		{
			do
			{
				outvec.clear();
				outvec.resize(vals.size());
				f1.set_hash(outvec.size());
			} while (!isgood(vals));

			vector<vector<int>> mat(outvec.size());
			vector<vector<char>> chmat(outvec.size());
			mat.resize(outvec.size());
			for (int i = 0; i < vals.size(); ++i)
			{
				mat[f1.get_hash(vals[i])].push_back(vals[i]);
				chmat[f1.get_hash(vals[i])].push_back(charvec[i]);
			}
			for (int i = 0; i < mat.size(); ++i)
			{
				if (mat[i].size() > 0)
					outvec[i].Bucket_build(mat[i], chmat[i]);
			}

		}

		char find_Fixed_set(int index)
		{
			return outvec[f1.get_hash(index)].find_bucket(index);
		}

		void print_fs()
		{
			int index = 0;
			for (auto fs : outvec)
			{
				cout << "Bucket: " << index++ << "\n";
				fs.print_buc();
				cout << "\n";
			}
		}
	};

	Fixed_set Hashtable;

	int _map_size;
	int _map_lenght;

	int from_index_to_num(int index_x, int index_y)
	{
		return index_x * _map_lenght + index_y;
	}

	int from_num_to_index_y(int num)
	{
		return num / _map_lenght;
	}

	int from_num_to_index_x(int num)
	{
		return num % _map_lenght;
	}



public:

	void build_map()
	{
		vector<char>charvec;
		vector<int>indexvec;
		char ch;
		int index = 0;


		ifstream file("C:\\Users\\maxim\\OneDrive\\Рабочий стол\\matrix.txt");
		if (file.is_open())
		{
			char buff[55];
			file >> _map_lenght;
			_map_size = _map_lenght * _map_lenght;

			while (!file.eof())
			{
				file >> ch;
				if (ch != ' ' && ch != 'O')
				{
					charvec.push_back(ch);
					indexvec.push_back(index++);
				}
				else if (ch == 'O')
					++index;
			}
		}
		else
		{
			cout << "file not found";
			exit;
		}

		Hashtable.Fixed_set_build(indexvec, charvec);
	}

	int get_size()
	{
		return _map_size;
	}

	int get_lenght()
	{
		return _map_lenght;
	}

	char find(int index_i, int index_j)
	{
		int index = from_index_to_num(index_i, index_j);
		return Hashtable.find_Fixed_set(index);
	}

	void print_map()
	{
		char ch;
		for (int i = 0; i < _map_lenght; ++i, cout << "\n")
			for (int j = 0; j < _map_lenght; ++j)
			{
				cout << find(i, j) << " ";
			}
	}

	void print_hashtable()
	{
		Hashtable.print_fs();
	}
};

class Warrior
{
protected:
	int _hp;
	int _damage;
	int _armor;
	int _speed;
	int _stamina;
	int _possition_x;
	int _possition_y;

	//Armory* ptr_armory;
	Map* ptr_map;

public:

	Warrior() {
		_hp = 100;
		_damage = 30;
		_armor = 50;
		_speed = 50;
		_stamina = 100;
		//ptr_armory = new Armory;
		ptr_map = new Map;
		ptr_map->build_map();
	}

	//Buffs of specialized troops
	//virtual void Type_buff() = 0;

	//Buffs of his weapon
	//virtual void pick_gun() = 0;

	//get
	int get_hp() {
		return _hp;
	}
	int get_damage() {
		return _damage;
	}
	int get_armor() {
		return _armor;
	}
	int get_speed() {
		return _speed;
	}

	//set
	void set_hp(int value)
	{
		this->_hp = value;
	}
	void set_armor(int value)
	{
		this->_armor = value;
	}
	void set_possition(int x, int y)
	{
		_possition_x = x;
		_possition_y = y;
	}

	//operators
	bool operator< (Warrior& other)
	{
		double power = this->_damage * 3 + this->_hp * 2 + this->_speed * 5 + this->_armor * 1.5;
		double power_op = other._damage * 3 + other._hp * 2 + other._speed * 5 + other._armor * 1.5;

		if (power < power_op)
			return true;
		else
			return false;
	}

	bool operator> (Warrior& other)
	{
		double power = this->_damage * 3 + this->_hp * 2 + this->_speed * 5 + this->_armor * 1.5;
		double power_op = other._damage * 3 + other._hp * 2 + other._speed * 5 + other._armor * 1.5;

		if (power > power_op)
			return true;
		else
			return false;
	}

	bool operator== (Warrior& other)
	{
		double power = this->_damage * 3 + this->_hp * 2 + this->_speed * 5 + this->_armor * 1.5;
		double power_op = other._damage * 3 + other._hp * 2 + other._speed * 5 + other._armor * 1.5;

		if (power == power_op)
			return true;
		else
			return false;
	}

	//move
	bool O_check(int pos)
	{
		return (pos == 0);
	}

	bool border_check(int pos)
	{
		int border = ptr_map->get_lenght();
		return (pos == border);
	}

	char input(int x, int y)
	{
		char ch;
		cout << "Your current possition is: (" << x << "; " << y << ") Here: \n\n";
		for (int i = 0; i < ptr_map->get_lenght(); ++i)
		{
			for (int j = 0; j < ptr_map->get_lenght(); ++j)
			{
				if (i == y && j == x)
					cout << 'x' << " ";
				else
					cout << 0 << " ";
			}
			cout << "\n";
		}
		cout << "\nYour current stamina is: " << _stamina << "\n";
		cout << "Chose the direction by (N, W, S, E or X to stay)\n";
		cin >> ch;
		cout << "\n";
		return ch;
	}

	void move()
	{
		int prev_x = _possition_x;
		int prev_y = _possition_y;

		char direction;
		direction = input(_possition_y, _possition_x);

		if (direction == 'W' && !O_check(_possition_y))
			--this->_possition_y;
		else if (direction == 'E' && !border_check(_possition_y))
			++this->_possition_y;
		else if (direction == 'N' && !O_check(_possition_x))
			--this->_possition_x;
		else if (direction == 'S' && !border_check(_possition_x))
			++this->_possition_x;
		else if (direction == 'X')
			this->_stamina += 20;

		if ((_possition_x == prev_x) && (_possition_y == prev_y) && (direction != 'X'))
		{
			cout << "out of borders!\nYou haven't move & you gain 10 stamina";
			_stamina += 10;
		}
		else if (direction == 'X')
		{
			cout << "You gain 20 stamina!";
		}
		else
		{
			int movement_loss = 0;
			if (ptr_map->find(_possition_x, _possition_y) == 'R')
			{
				cout << "You hit the rocks!\n";
				movement_loss = 10;
			}
			else if (ptr_map->find(_possition_x, _possition_y) == 'T')
			{
				cout << "You found the Town!\n";
				movement_loss = -25;
			}
			else if (ptr_map->find(_possition_x, _possition_y) == 'F')
			{
				cout << "You were lost in forest!\n";
				movement_loss = 20;
			}
			else if (ptr_map->find(_possition_x, _possition_y) == 'W')
			{
				cout << "You crossed big water flow!\n";
				movement_loss = 50;
			}

			if (movement_loss > _stamina)
			{
				_possition_x = prev_x;
				_possition_y = prev_y;
				_stamina += 10;
				cout << "not enough stamina!\nYou haven't move & you gain 10 stamina";
			}
			else
			{
				_stamina -= movement_loss;
				cout << "possition changed to " << _possition_y << " " << _possition_x;
				if (movement_loss >= 0)
					cout << "\nstamina loss = " << movement_loss;
				else
					cout << "\nstamina gain = " << movement_loss * -1;
			}
		}
	}

	void start_running()
	{
		char lever;
		cout << "Press I to start!  \n";
		cin >> lever;
		cout << "\n";
		while (lever == 'I')
		{
			this->move();
			cout << "\nIf you want to continue press I, else press O  ";
			cin >> lever;
			cout << "\n";
		}

	}
};






int main()
{
	char ch;
	Map A;
	A.build_map();
	//ch = A.find(2, 3);
	//A.print_hashtable();
	//cout << "\n\n\n";
	//A.print_map();

	Warrior W;
	W.set_possition(0, 0);
	W.start_running();
	//W.move();

	return 0;
}