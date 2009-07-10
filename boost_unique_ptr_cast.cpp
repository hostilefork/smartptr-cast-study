// boost::interprocess::unique_ptr upcast study
//
// EXPECT: Upcasting to follow same implicit semantics as pointers
// RESULT: No implicit upcast or explicit static_cast ability 
// COMPILER: g++ (Ubuntu 4.3.3-5ubuntu4) 4.3.3
// BOOST: 1.39

#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

using boost::interprocess::unique_ptr;

template<class T> struct genericdeleter { void operator() (T * p) { delete p;} };

class Base {
public:
	void BaseFunction(unique_ptr< Base, genericdeleter<Base> > bptr) {}
	virtual ~Base() {}
};

class Derived : public Base {
private:
	int val;
public:
	Derived(int valInit) : val (valInit) { }
	void DerivedFunction(unique_ptr< Base, genericdeleter<Base> > bptr) {}
	void SomeMethod() {
#if 0
		// As we expect, constructing without move() is not legal
		unique_ptr< Derived, genericdeleter<Derived> > dptr1 (new Derived(1));
		unique_ptr< Derived, genericdeleter<Derived> > dptrNoMoveInitialized = dptr1;	

		//  error: unique_ptr<Derived, genericdeleter<Derived> >::
		//         unique_ptr(unique_ptr<Derived, genericdeleter<Derived> >&) 
		//         is private within this context
#endif

		// However, if you use move it's legal...
		unique_ptr< Derived, genericdeleter<Derived> > dptr2 (new Derived(2));
		unique_ptr< Derived, genericdeleter<Derived> > dptrMoveInitialized = move(dptr2);

#if 0
		// No luck on upcasting...and explicit static cast doesn't help
		// (explicit static cast worked for std::auto_ptr)
		unique_ptr< Derived, genericdeleter<Derived> > dptr3 (new Derived(3));
		unique_ptr< Base, genericdeleter<Base> > bptrInitialized =
			move(dptr3);
			
/*
error: unique_ptr<Base, genericdeleter<Base> >::unique_ptr(unique_ptr<Derived, genericdeleter<Derived> >&)  is private within this context

error: no matching function for call to unique_ptr<Base, genericdeleter<Base> >::unique_ptr(unique_ptr<Base, genericdeleter<Base> >)
candidates are: unique_ptr<Base, genericdeleter<Base> >::unique_ptr(unique_ptr<Base, genericdeleter<Base> >&)
unique_ptr<Base, genericdeleter<Base> >::unique_ptr(unique_ptr<Base, genericdeleter<Base> >&) 
unique_ptr<Base, genericdeleter<Base> >::unique_ptr(rv<boost::interprocess::unique_ptr<Base, genericdleter<Base> > >&) 
*/
#endif
	}
};

int main() {
	Derived d (0);
	d.SomeMethod();
	return 1;
}
