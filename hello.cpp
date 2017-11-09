/*
#include <iostream>
#include <exception>
using namespace std;
int main()
{
	try{
		cout <<"hello, world" << endl;
		cout << sizeof(1) << endl;
		int A = 0x0002;
		int B = 0x0004;
		int C = A|B;
		int D = 0x0008;
		cout << "0x"<< hex << C << endl;

		if ( A & C )
			cout << "A & C" << endl;
		if ( B & C )
			cout << "B & C" << endl;
		if ( D & C )
			cout << "D & C" << endl;
			
		throw 1;
	} catch(int a) {
		cout << "errno:" << a << endl;
	} catch(exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
*/
#include <iostream>
#include <memory>

class a {
public:
	a(){
		v = 0;
	}
	a(int value)
	{
		v = value;
	}
	int get_v()
	{
		return v;
	}
	void set_v(int value)
	{
		v = value;
	}
private:
	int v;
};

int global_int = 7;

int main () {
	std::shared_ptr<int> sp;  // empty
	std::shared_ptr<int> sp2;  // empty
	//std::cout << *sp << '\n';

	sp.reset (new int);       // takes ownership of pointer
	*sp=10;
	std::cout << *sp << '\n';
	
	sp2 = sp;
	sp2.reset (new int);       // deletes managed object, acquires new pointer
	*sp2=20;
	std::cout << *sp << '\n';
	std::cout << *sp2 << '\n';

	sp.reset();               // deletes managed object

	//std::shared_ptr<a> shared_a_stack;
	a stack_a;
	stack_a.set_v(123);
	//shared_a_stack.reset(stack_a);
	//std::cout << shared_a_stack->get_v() << '\n';
	std::cout << stack_a.get_v() << '\n';
	
	std::shared_ptr<a> shared_a_heap;
	shared_a_heap.reset(new a(321));
	std::cout << shared_a_heap->get_v() << '\n';
	return 0;
}
