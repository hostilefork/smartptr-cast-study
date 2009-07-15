// std::unique_ptr upcast study
//
// EXPECT: Upcasting to follow same implicit semantics as pointers
// RESULT: As expected, but requires GCC 4.4 and compilation with -std=gnu++0x
// COMPILER: g++ (GCC) 4.4.0

#include <memory>
 
class Base {
public:
	void BaseFunction(std::unique_ptr<Base> bptr) {}
	virtual ~Base() {}
};
 
class Derived : public Base {
private:
	int val;
public:
	Derived(int valInit) : val (valInit) { }
	void SomeMethod() {
		// Construction from derived std::tr1::shared_ptr works...
		std::unique_ptr<Derived> dptr1 (new Derived(1));
		std::unique_ptr<Base> bptrConstructed (move(dptr1));
 
		// Assignment from derived std::tr1::shared_ptr too...
		std::unique_ptr<Derived> dptr2 (new Derived(2));
		std::unique_ptr<Base> bptrAssigned;
		bptrAssigned = move(dptr2);
 
		// Initializers work for shared pointers (unlike std::auto_ptr)
		std::unique_ptr<Derived> dptr3 (new Derived(3));
                std::unique_ptr<Base> bptrInitialized = move(dptr3);
 
		// ...AND function arguments work too (unlike std::auto_ptr)
		std::unique_ptr<Derived> dptr4 (new Derived(4));
		BaseFunction(move(dptr4));
	}
};
 
int main() {
	Derived d (0);
	d.SomeMethod();
	return 1;
}
