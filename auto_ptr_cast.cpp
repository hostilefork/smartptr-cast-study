// std::auto_ptr upcast study
//
// EXPECT: Upcasting to follow same implicit semantics as pointers
// RESULT: Static cast required for initializations and function arguments
// COMPILER: g++ (Ubuntu 4.3.3-5ubuntu4) 4.3.3

#include <memory>

class Base {
public:
	void BaseFunction(std::auto_ptr<Base> bptr) {}
	virtual ~Base() {}
};

class Derived : public Base {
private:
	int val;
public:
	Derived(int valInit) : val (valInit) { }
	void SomeMethod() {
		// Construction from derived std::auto_ptr works...
		std::auto_ptr<Derived> dptr1 (new Derived(1));
		std::auto_ptr<Base> bptrConstructed (dptr1);

		// Assignment from derived std::auto_ptr too...
		std::auto_ptr<Derived> dptr2 (new Derived(2));
		std::auto_ptr<Base> bptrAssigned;
		bptrAssigned = dptr2;

#if 0
		// ...BUT initializers are ambiguous
		std::auto_ptr<Derived> dptr3 (new Derived(3));
		std::auto_ptr<Base> bptrInitialized = dptr3;

		// ...AND so are function arguments
		std::auto_ptr<Derived> dptr4 (new Derived(4));
		BaseFunction(dptr4);

		// conversion from ‘std::auto_ptr<Derived>’ to ‘std::auto_ptr<Base>’ is ambiguous
		// candidates are: 
		// std::auto_ptr<Derived>::operator std::auto_ptr<Base>()
		// std::auto_ptr<Base>::auto_ptr(std::auto_ptr<Derived>&) 
#endif

		// A static cast is a workaround, but not what I am
		// looking for in this case...want it to be implicit
		std::auto_ptr<Derived> dptr5 (new Derived(5));
		std::auto_ptr<Base> bptrInitializedStaticCast = 
			static_cast< std::auto_ptr<Base> >(dptr5);
	}
};

int main() {
	Derived d (0);
	d.SomeMethod();
	return 1;
}
