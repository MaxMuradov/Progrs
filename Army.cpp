#include <iostream>
#include <vector>

//GUNS -----------------------------

//Default stats + virtual func
class Gun
{
protected:
	int _gun_damage = 50;
	int _gun_weight = 0;
public:
	virtual void Gun_buff() = 0;

	int get_damage()
	{
		return _gun_damage;
	}

	int get_weight()
	{
		return _gun_weight;
	}
};

class Ak47 : public Gun
{
public:
	Ak47() = default;
	void Gun_buff()
	{
		_gun_damage += 50;
		_gun_weight += 2;
	}
};

class M4A4 : public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 40;
		_gun_weight += 1;
	}
};

class Deagle :public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 15;
		_gun_weight += 0;
	}
};

class P90 :public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 30;
		_gun_weight += 1;
	}
};

class Awp :public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 150;
		_gun_weight += 4;
	}
};

class Xm : public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 70;
		_gun_weight += 3;
	}
};

class Negev : public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 100;
		_gun_weight += 4;
	}
};

class Aug :public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 45;
		_gun_weight += 1;
	}
};

class Mp9 : public Gun
{
public:
	void Gun_buff()
	{
		_gun_damage += 30;
		_gun_weight += 1;
	}
};


//Vector of weapons
class Armory
{
protected:
	std::vector<Gun*> _armory;

public:

	Armory()
	{
		load_full();
	}

	void load_full()
	{
		//16 Guns - Max
		//reserve прописать!!!
		_armory.reserve(16);

		push_back(new Ak47);
		push_back(new M4A4);
		push_back(new Deagle);
		push_back(new Awp);
		push_back(new Mp9);
		push_back(new P90);
		push_back(new Xm);
		push_back(new Negev);
		push_back(new Aug);
	}

	void push_back(Gun* ptr)
	{
		_armory.push_back(ptr);
	}

	void pop_back()
	{
		_armory.pop_back();
	}

	Gun* random_pick() {
		int r = std::abs(rand()) % _armory.size();
		return _armory[r];
	}
};


//Warriors--------------------
//Default stats + virtual func
class Warrior
{
protected:
	int _hp = 100;
	int _damage = 30;
	int _armor = 50;
	int _speed = 50;

	Armory* ptr_armory;

public:

	Warrior() {
		ptr_armory = new Armory;
	}

	//Buffs of specialized troops
	virtual void Type_buff() = 0;

	//Buffs of his weapon
	virtual void pick_gun() = 0;

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

};


//Light
class Light_Infantry : public Warrior
{
public:

	Light_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 0;
		_damage += 0;
		_armor += 5;
		_speed += 5;
	}

	void pick_gun()
	{

		Gun* ptr = ptr_armory->random_pick();

		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Irregular
class Irregular_Infantry :public Warrior
{
public:
	Irregular_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 50;
		_damage += -5;
		_armor += 0;
		_speed += 0;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Heavy
class Heavy_Infantry : public Warrior
{
public:
	Heavy_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 15;
		_damage += 15;
		_armor += 25;
		_speed += -15;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Mountain
class Mountain_Infantry :public Warrior
{
public:
	Mountain_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 40;
		_damage += 5;
		_armor += 20;
		_speed += -10;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Motorized
class Motorized_Infantry :public Warrior
{
public:
	Motorized_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 25;
		_damage += 10;
		_armor += 75;
		_speed += 30;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Mechanized
class Mechanized_Infantry :public Warrior
{
public:
	Mechanized_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 45;
		_damage += 0;
		_armor += 100;
		_speed += 35;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Airborne
class Airborne_Infantry :public Warrior
{
public:
	Airborne_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 30;
		_damage += 20;
		_armor += 10;
		_speed += 25;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Air Assault
class Air_assault_Infantry :public Warrior
{
public:
	Air_assault_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 10;
		_damage += 5;
		_armor += 5;
		_speed += 10;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};

//Naval
class Naval_Infantry :public Warrior
{
public:
	Naval_Infantry()
	{
		this->Type_buff();
		this->pick_gun();
	}

	void Type_buff()
	{
		_hp += 20;
		_damage += 10;
		_armor += 15;
		_speed += -10;
	}

	void pick_gun()
	{
		Gun* ptr = ptr_armory->random_pick();
		ptr->Gun_buff();
		_damage += ptr->get_damage();
		_speed -= ptr->get_weight();
		if (_speed < 0) _speed = 0;
	}
};



//Army ------------------

class Army
{
protected:
	std::vector<Warrior*> _army;
	int _size;

public:
	Army() {
		_size = 0;
	}

	Army(std::vector<Warrior*> vec)
	{
		vec = _army;
		this->build_heap();
	}

	//find index ----
	int left_Child(int parent_index)
	{
		return (parent_index * 2 + 1);
	}

	int right_Child(int parent_index)
	{
		return (parent_index * 2 + 2);
	}

	int parent(int child_index)
	{
		return ((child_index - 1) / 2);
	}

	//Children_Check ----
	bool two_children(int index)
	{
		if (right_Child(index) >= _size)
			return false;
		else
			return true;
	}

	bool one_child(int index)
	{
		//last child left and only one
		if (left_Child(index) == _size - 1)
			return true;
		else
			return false;

	}

	bool no_child(int index)
	{
		if (left_Child(index) >= _size)
			return false;
		else
			return true;
	}

	//sift up/down ----
	void sift_down(int index)
	{
		//re-check!!!
		bool EF = false;
		while (no_child(index) == true && (EF == false))
		{
			if (two_children(index))
			{
				//!
				int max_index = (*_army[left_Child(index)] > *_army[right_Child(index)]) ? left_Child(index) : right_Child(index);
				if (*_army[max_index] > *_army[index])
				{
					std::swap(_army[max_index], _army[index]);
					index = max_index;
				}
				else
					EF = true;
			}
			else if (one_child(index) == true)
			{
				//!
				if (*_army[index] < *_army[left_Child(index)])
				{
					std::swap(_army[index], _army[left_Child(index)]);
					index = left_Child(index);
				}
				else
				{
					EF = true;
				}
			}
		}

	}

	void sift_up(int index)
	{
		//!
		while (*_army[parent(index)] < *_army[index])
		{
			std::swap(_army[parent(index)], _army[index]);
			index = parent(index);
		}
	}

	//main---
	void build_heap()
	{
		for (int i = 0; i < _army.size(); ++i)
		{
			sift_up(i);
			++_size;
		}
	}

	Warrior* extract_max()
	{
		std::swap(_army[0], _army[_size - 1]);
		--_size;
		sift_down(0);
		return _army[_size];
	}

	//Push ----
	void hire(Warrior* troop)
	{
		if (_size > 0)
		{
			if (_size == _army.size())
				push_to_heap(troop);
			else
			{
				int index = _size;
				/*int n = _army.size();*/
				_army.push_back(troop);
				for (int i = _army.size() - 1; i > _size; )
				{
					std::swap(_army[i], _army[i - 1]);
					index = --i;
				}
				sift_up(index);
				++_size;

				//double check
				//sift_down(index);
			}
		}
		else
		{
			this->push_back_heap(troop);
		}
	}

	void push_to_heap(Warrior* troop)
	{
		_army.push_back(troop);

		sift_up(_army.size() - 1);

		++_size;
	}

	void push_back_heap(Warrior* troop)
	{
		_army.push_back(troop);
		++_size;
	}

	//operators----

	void print() {
		for (int i = 0; i < _army.size(); ++i)
			if (_army[i] != nullptr)
				std::cout << "Yes";
			else
				std::cout << "no";
	}

	/*void hire(Warrior* troop)
	{
		_army.push_back(troop);
		++_size;
	}*/

	//pop_back
	void loss()
	{
		_army.pop_back();
	}

	void move(Warrior* atk, Warrior* def)
	{
		int health = def->get_hp();
		health -= (atk->get_damage() - def->get_armor() / 2);
		def->set_hp(health);
		def->set_armor(def->get_armor() / 2);
	}

	bool fight(Warrior* soldier1, Warrior* soldier2)
	{
		int counter;
		if (soldier1->get_speed() > soldier2->get_speed())
			counter = 0;
		else
			counter = 1;

		while ((soldier1->get_hp() > 0) && (soldier2->get_hp() > 0))
		{
			if (counter % 2 == 0)
				move(soldier1, soldier2);
			else
				move(soldier2, soldier1);

			++counter;
		}

		if (soldier1->get_hp() <= 0)
			return 1;
		else
			return 0;
	}

	void Clash(Army& opponent)
	{
		bool loser;
		Warrior* tmp_warrior1 = this->extract_max();
		Warrior* tmp_warrior2 = opponent.extract_max();
		//int this_index, opponent_index;
		while ((this->_size != 0) && (opponent._size != 0))
		{
			//Making them fight

			loser = fight(tmp_warrior1, tmp_warrior2);


			if (loser)
				this->loss();
			else
				opponent.loss();

			if (loser)
				tmp_warrior1 = this->extract_max();
			else
				tmp_warrior2 = opponent.extract_max();
		}

		if (this->_size == 0)
			std::cout << "\nWe lost!\n";
		else
			std::cout << "\nWe won!\n";
	}

};



//Main ---------------------
int main()
{

	Army A;
	Army B;

	A.hire(static_cast<Warrior*>(new Heavy_Infantry));
	A.hire(static_cast<Warrior*>(new Irregular_Infantry));
	A.hire(static_cast<Warrior*>(new Airborne_Infantry));
	A.hire(static_cast<Warrior*>(new Mechanized_Infantry));
	B.hire(static_cast<Warrior*>(new Mechanized_Infantry));
	B.hire(static_cast<Warrior*>(new Irregular_Infantry));
	B.hire(static_cast<Warrior*>(new Naval_Infantry));
	B.hire(static_cast<Warrior*>(new Air_assault_Infantry));

	std::cout << "\nA\n";
	A.print();
	std::cout << "\nB\n";
	B.print();


	A.Clash(B);
	return 0;
}