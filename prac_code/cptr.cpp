#include <iostream>
#include <string>
#include <sstream>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

class person_base
{
public:
	person_base() 
	{
	};
	~person_base()
	{
	};
	virtual string get_nationality() = 0;
	virtual string str() = 0;
};

class english_person : person_base
{
public:
	english_person() : nationality_ ("english")
	{
		cout << "(constructor)" << nationality_ << endl;
	}
	english_person(string nationality) : nationality_ (nationality)
	{
		cout << "(constructor)" << nationality_ << endl;
	}
	string get_nationality(){
		return nationality_;
	}
	string str()
	{
		ostringstream oss;
		oss << "nationality : " << nationality_ ;
		return oss.str();
	}
private:
	string nationality_;
};

int main(int argc, char* argv[])
{
	english_person american = english_person(string("USA"));
	english_person english = english_person();

	cout << american.str() << endl; 
	cout << english.str() << endl; 

	return 0;
}

