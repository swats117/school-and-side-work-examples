#include <cstdio>


	//declaration like sll(int): value(int), value2(blah){} for initializaiton list
	//
	// declaration function like return_t get()const; means the function is 
	// const safe, aka it promises not to change the state of the object.
	// const declared objects may only use const-safe functions.
	//
	// at the end of a function, every local object calls its destructor.
	//
	// Making the default constructor private makes it unusable.
	//
	// If a constructor takes one parameter, you can do implicit constructions
	// class name = initialization_parameter;
	//
	// Constructors like "explicit get(initalization_parameter){}" mean you
	// are not allowed to use implicit constructor with type promotion.
	// To get around this, make all declarations explicit by doing class(inititalization parameters);
	//
	// Constructors can have default values return_t constructor(type param=default, type2 param2=default2);
	// These are given left to right. e.g. constructor(value) sets the first param to value, but the second
	// param to default2.
	//
	// Constructors with multiple parameters, where the second through endth parameters have default values
	// are subject to implicit construction.
	// e.g. return_t constructor(type1 param, type2 param2=default2, type3 param3=default3);
	// could be constructed like class name = (type1)value.
	//
	// functions can return by reference, this is the same as returning a pointer, except that
	// references can't be null. A literal or a reference can accept the return value.
	// e.g. int & return_ref()
	// int x=return_ref(); or int& y=return_ref();
	// a function that returns by reference returns a value, but the function then takes
	// the address of that function and returns that, if the return acceptor is a literal,
	// the function returns the value, if the return acceptor is a reference, it returns the reference.
	// really, the return by reference should be for efficient return by value,
	// the return acceptor should really be a reference.
int & return_reference(int &x){

	return x;
}
int & return_reference2(int &x){
	int y=x;
	return x;
}
// int & return_reference3(int &x){
// 	int y=x;
// 	return &y;
// }

int main(){
	
	int x1=7;
	printf("x1:%d\n",x1);
	int& x2=return_reference(x1);

	// int* x3=x2;
	printf("%p \n",x2);
	printf("x2:%d\n",x2);

	x1++;
	printf("x1:%d\n",x1);
	printf("x2:%d\n",x2);

	return 0;
}