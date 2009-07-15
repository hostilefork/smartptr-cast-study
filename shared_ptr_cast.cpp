// std::tr1::shared_ptr upcast study
//
// EXPECT: Upcasting to follow same implicit semantics as pointers
// RESULT: As expected
// COMPILER: g++ (Ubuntu 4.3.3-5ubuntu4) 4.3.3

#include <memory>
#include <tr1/memory>
 
class Base {
public:
	void BaseFunction(std::tr1::shared_ptr<Base> bptr) {}
	virtual ~Base() {}
};
 
class Derived : public Base {
private:
	int val;
public:
	Derived(int valInit) : val (valInit) { }
	void SomeMethod() {
		// Construction from derived std::tr1::shared_ptr works...
		std::tr1::shared_ptr<Derived> dptr1 (new Derived(1));
		std::tr1::shared_ptr<Base> bptrConstructed (dptr1);
 
		// Assignment from derived std::tr1::shared_ptr too...
		std::tr1::shared_ptr<Derived> dptr2 (new Derived(2));
		std::tr1::shared_ptr<Base> bptrAssigned;
		bptrAssigned = dptr2;
 
		// Initializers work for shared pointers (unlike std::auto_ptr)
		std::tr1::shared_ptr<Derived> dptr3 (new Derived(3));
		std::tr1::shared_ptr<Base> bptrInitialized = dptr3;
 
		// ...AND function arguments work too (unlike std::auto_ptr)
		std::tr1::shared_ptr<Derived> dptr4 (new Derived(4));
		BaseFunction(dptr4);
	}
};
 
int main() {
	Derived d (0);
	d.SomeMethod();
	return 1;
}
