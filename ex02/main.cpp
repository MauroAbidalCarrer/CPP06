#include <iostream>
#include <string>
#include <cstdlib>

class Base { public: virtual ~Base(void){}};

class A : public Base {};
class B : public Base {};
class C : public Base {};

Base* generate()
{
    Base* pointer;
    int random = std::rand() % 3;
    if (random == 0)
    {
        std::cout << "generated A class instance" << std::endl;
        pointer = new A();
    }
    if (random == 1)
    {
        std::cout << "generated B class instance" << std::endl;
        pointer = new B();
    }
    if (random == 2)
    {
        std::cout << "generated C class instance" << std::endl;
        pointer = new C();
    }
    std::cout << "child address" << pointer << std::endl;
    return pointer;
}
void identify(Base* p)
{
    std::cout << "identifying pointer " << p << " ..." << std::endl;
    if (dynamic_cast<A*>(p))
        std::cout << "identified pointer as class A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "identified pointer as class B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "identified pointer as class C" << std::endl;
    else 
        std::cout << "could not identify pointer " << p << " ... nanni?"<< std::endl;
}
template<typename T> void identify(Base &ref, std::string typeName/*because we can't use typeInfo*/)
{
    try
    {
        (void)dynamic_cast<T&>(ref);
        std::cout << "reference " << &ref << "identified as class " << typeName << std::endl;
    }
    catch(const std::exception& e) {}
}

void identify(Base& p)
{
    identify<A>(p, "A");
    identify<B>(p, "B");
    identify<C>(p, "C");
}


int main()
{
    std::srand((unsigned int)time(NULL));
    std::cout << "Identify tests with pointers:" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        Base* randomlyGeneratedChild = generate();
        identify(randomlyGeneratedChild);
        delete randomlyGeneratedChild;
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
    for (int i = 0; i < 5; i++)
    {
        Base* randomlyGeneratedChild = generate();
        identify(*randomlyGeneratedChild);
        delete randomlyGeneratedChild;
        std::cout << std::endl;
    }
}