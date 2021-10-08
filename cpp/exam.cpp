#include <iostream>

using namespace std;

class Mine; 
void print_by_ref(Mine& a);
void print_by_value(Mine a);

class Mine{
	public:
		explicit Mine(int n=10, int k=20) 
		{
			n_ = n;
			k_ = k;
		}
		void member_call()
		{
			cout << "inside instance" << endl;
			print_by_ref(*this);    
			print_by_value(*this);    
		}
		int k_; 
		int n_; 
};

void print_by_ref(Mine& a)
{
	cout << "by ref" << endl;
	cout << static_cast<const void*>(&a)<< " "   << a.n_ << " " << a.k_ << endl;
}

void print_by_value(Mine a)
{
	cout << "by value(copy)" << endl;
	cout << static_cast<const void*>(&a)<<" "  << a.n_ << " " << a.k_ << endl;
}

int main()
{

	Mine a;

	print_by_ref(a);
	print_by_value(a);

	a.member_call();

}
