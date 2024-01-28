#include <iostream>
#include <vector>

using namespace std;

class Hash_func
{
private:
	int a;
	int b;
	int c;
	int size;

public:

	Hash_func() = default;

	void gen_Hash_func(int size) 
	{
		a = rand();
		b = rand();
		c = 997;
		this->size = size;
	}

	int gethash(int val)
	{
		return (val * a + b) % c % size;
	}
};

class Bucket
{
private:
	class Optional
	{
	private:
		bool isval;
		int value;
	public:
		Optional() : isval(false) {};
		Optional(int newval) : isval(true), value(newval){};

		bool hasval()
		{
			return isval;
		}

		int get_val()
		{
			return value;
		}


	};
	vector<Optional> secvec;
	Hash_func f2;

	//bool isgood(int valssize)
	//{
	//	for (int i = 0; i < secvec.size(); ++i)
	//	{
	//		if (secvec[i].hasval())
	//			--valssize;
	//	}
	//	return (valssize == 0);
	//} //Переделать!

	bool isgood(const vector<int>& vals)
	{
		vector<int> hashval;
		bool b = true;
		for (int i = 0; i < vals.size(); ++i)
			hashval.push_back(f2.gethash(vals[i]));
		for (int i = 0; i < vals.size() - 1; ++i)
			for (int j = i + 1; j < vals.size(); ++j)
				if (vals[i] == vals[j])
					b = false;
		return b;
	}

public:
	Bucket() = default;

	void Bucket_dis(const vector<int>& vals)
	{
		secvec.resize(vals.size() * vals.size());
		do 
		{
			f2.gen_Hash_func(secvec.size());
			for (int i = 0; i < vals.size(); ++i)
			{
				secvec[f2.gethash(vals[i])] = vals[i];
			}
		} while (!isgood(vals))

	}
};

class Fixed_set
{
private:
	vector<Bucket> firstvec;
	Hash_func f1;
	bool isgood(const vector<int>& vec)
	{
		int result = 0;
		vector<int> distrvec;
		distrvec.resize(firstvec.size(), 0);
		for (int i = 0; i < vec.size(); ++i)
			++distrvec[f1.gethash(vec[i])];
		for (int i = 0; i < distrvec.size(); ++i)
			result += distrvec[i] * distrvec[i];
		return (result < firstvec.size() * 4);
	}

public:

	Fixed_set(const vector<int>& vec)
	{
		firstvec.resize(vec.size());
		do 
		{
			f1.gen_Hash_func(firstvec.size());
		} while (!isgood(vec));

		vector<vector<int>> mat;
		mat.resize(vec.size());
		for (int val : vec)
			mat[f1.gethash(val)].push_back(val);
		for (int i = 0; i < mat.size(); ++i)
		{
			firstvec[i].Bucket_dis(mat[i]);
		}
	}
	
};

int main()
{
	vector<int> vec = {1, 2 ,3 , 4, 5, 6, 7, 8, 9};

	Fixed_set A (vec);

}
