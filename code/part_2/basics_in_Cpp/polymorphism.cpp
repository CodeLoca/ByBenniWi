#include <cstdint>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

/*
Example for function / method overloading -> compile time polymorphism
*/
class Addition
{
   public:
    static auto add(int8_t num_x, int8_t num_y) -> int16_t
    {
        return num_x + num_y;  // this function is performing addition of two Integer value
    }

    static auto add(const string &str1, const string &str2) -> string
    {
        return str1 + str2;  // this function concatenates two strings
    } 
};

/*
Example for operator overloading -> compile time polymorphism
*/
class A
{
    string str_x_;

   public:
    A() = default;
    // What is explicit?? -> https://stackoverflow.com/a/121163
    // Why prefer std::move?? over explicit A(const string &str_i) : str_x_{str_i}
    // -> https://clang.llvm.org/extra/clang-tidy/checks/modernize/pass-by-value.html
    explicit A(string str_i) : str_x_{std::move(str_i)}
    {
    }
    void operator+(const A &class_a)
    {
        string str_m = str_x_ + class_a.str_x_;
        cout << "The result of the addition of two objects is : " << str_m << endl;
    }
};

/*
Example for function overriding -> runtime polymorphism
*/
class Animal
{
   public:
    void function() const
    {
        cout << "Eating..." << endl;
    }
};
class Man : public Animal
{
   public:
    void function() const
    {
        cout << "Walking ..." << endl;
    }
};

/*
Example for virtual function -> runtime polymorphism
*/
class ParentWVirtual
{
   public:
    void non_virtual_display() const
    {
        cout << "Parent non_virutal speaking !!" << endl;
    }

    virtual void virtual_display() const
    {
        cout << "Parent virtual speaking !!" << endl;
    }

    // if we have defined a base class with "virtual", 
    // it is good practice to define the behaviour of the
    // destructor
    virtual ~ParentWVirtual() = default;
};

class DerivedWVirtual : public ParentWVirtual
{
   public:
    void non_virtual_display() const  // overridden function
    {
        cout << "Derived non_virtual speaking !!"<< endl;
    }

    void virtual_display() const
    {
        cout << "Derived virtual speaking !!" << endl;
    }
};

auto main() -> int
{
    // Example for function / method overloading
    cout << "------ Function Overloading: ------" << endl;
    cout << +Addition::add(3, 9) << endl;             // first method is called
    cout << Addition::add("Hallo", " Welt") << endl;  // second method is called

    // Example for operator overloading
    cout << "------ Operator Overloading: ------" << endl;
    A ca1("Welcome");
    A ca2(" Back");
    ca1 + ca2;

    // Example for function overriding
    cout << "------ Function Overriding: ------" << endl;
    Animal animal = Animal();
    animal.function();  // parent class object
    Man man = Man();
    man.function();  // child class object

    // Example for virtual function
    cout << "------ Virtual Overriding: ------" << endl;
    DerivedWVirtual dwv;  // making object of derived class
    ParentWVirtual *pwv = &dwv;       // base class pointer .it can only access the base class members
    pwv->non_virtual_display(); // call the parent class method
    dwv.non_virtual_display();  // call the overriden derived class method
    pwv->virtual_display();     // call the overriden virtual derived class method via parent class pointer,
    dwv.virtual_display();      // call the overriden virtual derived class method via derived class
    

    return 0;
}