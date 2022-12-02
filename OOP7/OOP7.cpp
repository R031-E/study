#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <functional>
#include <numeric>
#include <string>

using namespace std;

int m1 = 0, m2 = 15;

class IncorrectInput 
{
private:
	string text;
public:
	IncorrectInput(string msg = "Incorrect input.\n")
	{
		text = msg;
	}
	string what() { return text; }
};

template <class Type>
struct power
{
	Type operator() (Type& Element) const
	{
		return Element * Element;
	}
};

template <class S>
ostream& operator<<(ostream& os, const vector<S>& vector)
{
	for (const auto& element : vector) 
	{
		os << element << " ";
	}
	return os;
}

template <class T> class Vec
{
private:
	int size;
	vector <T> v, v1, v2;
public:
	Vec(int);
	~Vec() { }
	void vec2();
	void shuffle();
	void aver();
	void mult();
	void powerelementwise();
};

template <class T> Vec <T>::Vec(int _size)
{
	srand(time(NULL));
	size = _size;
	v1.reserve(size);
	string a = typeid(T).name();
	if (a == "int")
	{
		for (int i = 0; i < size; i++)
		{
			v1.push_back((m1 + rand() % (m2 - m1 + 1)));
		}
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			T f = (T)rand() / RAND_MAX;
			v1.push_back(m1 + f * (m2 - m1));
		}
	}
	cout << "Vector 1: ";
	cout << v1 << endl;
}

template <class T> void Vec <T>::vec2() 
{
	v2.reserve(size);
	copy(v1.begin(), v1.end(), back_inserter(v2));
	cout << "Vector 2: " << v2 << endl;
}

template <class T> void Vec <T>::shuffle()
{
	random_shuffle(v2.begin(), v2.end());
	cout << "Shuffled Vector 2: " << v2;
}

template <class T> void Vec <T>::aver()
{
	double a;
	a = accumulate(v1.begin(), v1.end(), 0.0) / size;
	cout << "\nAverage of Vectors 1 and 2: " << a;
}

template <class T> void Vec <T>::mult()
{
	v.reserve(size);
	transform(v1.begin(), v1.end(), v2.begin(), back_inserter(v), multiplies<T>());
	cout << "\nElementwise multiplication of Vector 1 and Vector 2. Vector: " << v << endl;
}

template <class T> void Vec <T>::powerelementwise()
{
	transform(v.begin(), v.end(), v.begin(), power<T>());
	cout << "Vector powered elementwise: " << v << endl;
}

int main()
{
	string n, c;
	int n1, c1;
	cout << "Select data type in the vector:\n 1) Integer\n 2) Double\n 3) Float\n";
	try 
	{
		cin >> c;
		if ((c.find_first_not_of("123") == string::npos) == false) throw IncorrectInput();
		c1 = stoi(c);
	}
	catch (IncorrectInput& ex)
	{
		while ((c.find_first_not_of("123") == string::npos) == false)
		{
			cout << ex.what();
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> c;
		}
		c1 = stoi(c);
	}
	cout << "Input size: ";
	try 
	{
		cin >> n;
		if ((n.find_first_not_of("0123456789") == string::npos) == false) throw IncorrectInput();
		n1 = stoi(n);
	}
	catch (IncorrectInput& ex)
	{
		while ((n.find_first_not_of("0123456789") == string::npos) == false)
		{
			cout << ex.what();
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin >> n;
		}
		n1 = stoi(n);
	}
	switch (c1) 
	{
	case 1:
	  {
		Vec<int> vectors(n1);
		vectors.vec2();
		vectors.shuffle();
		vectors.aver();
		vectors.mult();
		vectors.powerelementwise();
		return 0;
	  }
	case 2:
	  {
		Vec<double> vectors(n1);
		vectors.vec2();
		vectors.shuffle();
		vectors.aver();
		vectors.mult();
		vectors.powerelementwise();
		return 0;
	  }
	case 3:
	  {
		Vec<float> vectors(n1);
		vectors.vec2();
		vectors.shuffle();
		vectors.aver();
		vectors.mult();
		vectors.powerelementwise();
		return 0;
	  }
	}
}