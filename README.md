# What is a class

A *class* in C++ is a programmatic construct to group data and functions into
comprehensive and reusable units, to optionally restrict access to such data
or the calling of such functions, and to optionally automate actions when such
a unit is created or destroyed during the lifecycle of a program.

This document addresses only getting to know classes on a basic level. Advanced
topics such as copy constructors, overloaded assignment operators or `this` are
not covered.

## Declaration vs. definition

Similar to the fact that declaring the prototype of a function and defining
(implementing its code) are two different things, declaring a class and defining
it are separate. The class *definition* just defines what data and functions are
available. Once a class is defined, other code can use it as if it were a new
data type.

> A class' functions are typically called *methods* or *member functions*.
> Variables that are created having this type are called *objects* or
> *class instances*.

It's good practice to:

*  Declare a class in its header
*  Define the class in one or more `.cc` source files.

(Often one might find the declaration, code, right in the header file. That's
an example of inline code, and it is usable in its own right. That approach
is not followed here.)

## An example to work on

In this example, let's define a new type that is capable of tracking a
firstname, a lastname and a year of birth. The type will be named `Person`.

The class definition start with:

```c++
class Person {
  // To be filled in.
  // Data to track: first and last name, and year of birth
  // Methods to provide: to manipulate these data
};
```

The typography to start a classname with one capital is just my personal
preference, there are no strict rules here. Note that the class definition ends
with a semicolon.

## Public vs. private

Both the data that will be stored in the class, and the methods that the class
will define, can be labeled either `private` or `public` (at least, that
suffices for this example):

*  Private data may only be accessed (read or written) by methods of that
   class and not by 'the outside'.
*  Private methods may only be called from methods of that class and not by
   the outside.
*  Public data may be accessed by anyone.
*  Public methods may be called by anyone.

The most simplistic class would have all data public and no methods. This is
in fact just a `struct`:

```c++
// Most simplistic Person class. We won't follow this approach any further.
class Person {
 public:                              // everything beyond this is public
  std::string firstname, lastname;    // first and last name
  unsigned int yearofbirth;           // year of birth
};
.
.
.
Person one;
one.firstname = "Sponge";
one.lastname = "Bob";
one.yearofbirth = 1999;
```

However, it's good practice to:

*  Keep all class data `private`
*  Provide `public` accessor methods to these data to manipulate.

This forces users of such a class to invoke accessors, instead of manipulating
the fields. Here is an example for the year of birth in this example:

```c++
// Class declaration
class Person {
 public:
  void setyearofbirth(int yb);
 private:
  unsigned int yearofbirth;
};

// Definition of method setyearofbirth
void Person::setyearofbirth(int yb) {
  yearofbirth = yb;
}

// Calling example
Person one;
one.setyearofbirth(1999);
```

This example also shows how to define class functions: they have the *type*
that's stated in the definition, followed by *classname*, ::, and then the
*method name*. Finally there is the *parameter list* in parentheses. The
class name prefix tells the compiler that this definition applies to a class
method.

The benefit of having private data and public accessors is that code
modifications of the class methods may later occur, without having to modify
callers. Imagine that we suddenly decide that the persons we track may not be
born before 1900. If the class had a `public unsigned int yearofbirth` then
we'd have to check all sources to provide an `if` statement to check that
the year has the right value. When access to this data member is localized,
then the check has to be implemented in only one location:

```c++
// Revised definition of method setyearofbirth. The year must be >= 1900.
void Person::setyearofbirth(int yb) {
  if (yb < 1900)
    throw "setyearofbirth: year must be >= 1900"
  yearofbirth = yb;
}
```

## Const

You are most likely familiar with the keyword `const` to provide information
that a function won't modify a parameter, or that a variable won't be modified:

```c++
// func() won't modify its somestring parameter
void func (std::string const &somestring);

// max can't be modified below
int const max = 256;
```

The keyword `const` also has a purpose when used in class declarations: it
specifies that a class method won't alter the class data. For example, the above
`Person::setyearofbirth()` can't be `const` because it modifies the class
variable `yearofbirth`. But a new accessor `Person::getyearofbirth()` could -
and should - be labeled `const`. This must be done both in the class declaration
and in the method definition:

```c++
class Person {
 public:
  // Get and set the year of birth
  void setyearofbirth(unsigned int yb);
  unsigned int getyearofbirth() const;
 private:
  // Class variables
  unsigned int yearofbirth;
};

unsigned int Person::getyearofbirth() const {
  return yearofbirth;
}
```

Labeling class methods correctly allows users of the class to decide whether
they want to create `const` objects. For example:

```c++
Person one;
one.setyearofbirth(1923);    // allowed, one is not const and setyearofbirth
                             // isn't either, so that's ok

Person const two;
two.setyearofbirth(1969);    // not allowed, two is const but setyearofbirth
                             // isn't
```

## Constructors and destructors

Classes provide a mechanism to call two types of "magical" functions when they
are defined:

*  A constructor, if present, is called when an object is instantiated; i.e.,
   when it is created.
*  A destructor, if present, is caleld when an object is destoyed; i.e., when
   it goes out of scope or when it is deallocated.

This is an extremely useful feature. Constructors can e.g. initialize the class
variables to some default, they can open files, start network connections,
etc. Destructors can do the opposite to provide an automatic cleanup.

The name of the constructor is always the class name. The name of the destructor
is always the classname prefixed by a tilde. Note that when defining these
methods, they must be prefixed again by the classname and two semicolons:

```c++
class Person {
 public:
  Person();             // constructor
  ~Person();            // destructor
  .
  .
  .
};

Person::Person() {
  // code for the constructor
}

Person::~Person() {
  // code for the destructor
}
```

By definition, the destructor is called automatically, without any
programmer-supplied code to call it. The destructor therefore never has
parameters. Destructors are called when an object ceases to exist:

*  For global objects, this is after `main()` has finished.
*  For local objects (inside a function), this is when its function returns.

Constructors however can have parameters, but don't have to. A constructor
without paramaters is called the *default constructor*. The supplied parameters,
if any, depend on the code that creates the variable. They are called when an
object is instantiated:

*  For global objects, the constructor is called even before `main()` runs.
*  For local objects (inside a function), the constructor is called when
   the object comes to life; i.e., once that function is called.

This is illustrated in two trivial test programs:

```c++
/*
 * test1.cc: Example of global object construction and destruction.
 * Output:
 *   Test object instantiated
 *   Main ends
 *   Test object destroyed
 */

#include <iostream>

class Test {
 public:
  Test();
  ~Test();
};

Test::Test() {
  std::cout << "Test object instantiated\n";
}

Test::~Test() {
  std::cout << "Test object destroyed\n";
}

Test t;
int main() {
  std::cout << "Main ends\n";
  return 0;
}


/*
 * test2.cc: Example of global object construction and destruction.
 * Output:
 *   Main starts
 *   Func starts
 *   Test object instantiated
 *   Func ends
 *   Test object destroyed
 *   Main ends
 */

#include <iostream>

class Test {
 public:
  Test();
  ~Test();
};

Test::Test() {
  std::cout << "Test object instantiated\n";
}

Test::~Test() {
  std::cout << "Test object destroyed\n";
}

void func() {
  std::cout << "Func starts\n";
  Test t;
  std::cout << "Func ends\n";
}

int main() {
  std::cout << "Main starts\n";
  func();
  std::cout << "Main ends\n";
  return 0;
}
```

## Initializing class variables in constructors

One of the job of constructors is often to initialize class variables to
values. In the case of the default constructor these will be most likely
defaults.

In this context, it is important to distinguish between *initialization* and
*assignment*. The former occurs when a variable is created and immediately
assigned a value; the latter occurs when an existing variable receives a new
value. Or, in an example:

```c++
// Initialization
int a = 12;
// or, less frequently seen:
// int a(12);

// Assignment
int b;
b = 12;
```

The difference may not look like much, but it's there. In an assignment a
variable holds some (random) value before it receives its new value.

When constructors assign values to class variables, they should *always use the
initialization form* and *never the assignment form*. C++ offers a special
syntax for it. For example, the constructor for a `Person` having as parameters
values for the fields `firstname`, `lastname` and `yearofbirth` should look like
this:

```c++
Person::Person(string const &fn, string const &ln, unsigned int yob):
    firstname(fn), lastname(ln), yearofbirth(yob) {

// other code (if any)

}
```

Note that the initialization of the class data occurs even before the open-brace
character. Any other code of the constructor won't even be executed before the
initialization occurs.

Why is this better than an assignment? 

Consider the bad alternative:

```c++
// DON'T DO THIS ALTHOUGH IT WILL PROBABLY WORK
Person::Person(string const &fn, string const &ln, unsigned int yob) {
  firstname = fn;
  lastname = ln;
  yearofbirth = yob;
}
```

The problem with this code is that by the time that the assignment `firstname =
fn` is executed, `firstname` already has some (random) value. The assignment
might try to free up memory that this random value seems to occupy, leading to
memory corruption. In this case that probably won't happen; class `std::string`
is well thought through. But you just should initialize when appropriate, and
assign when appropriate, and not mix.

## Full example code

Finally, here's the full example code for the class `Person`. The code in the
class methods doesn't do much except for writing to `std::cout` what's
happening, but it does illustrate the class concept. Note that the below listing
might be somewhat stale (depending on changes that I might apply). For the most
recent version see the source file `person.cc`.

```c++
#include <iostream>

class Person {
 public:

  // Default constructor, constructor with parameters, and destructor
  Person();
  Person(std::string const &fn, std::string const &ln, unsigned int yob);
  ~Person();

  // Name accessors
  void setname(std::string const &fn, std::string const &ln);
  std::string getfirstname() const;
  std::string getlastname() const;

  // Year of birth accessors
  void setyearofbirth(unsigned int yob);
  unsigned int getyearofbirth() const;

 private:
  // Private data
  std::string firstname, lastname;
  unsigned int yearofbirth;
};


Person::Person():
    firstname(""), lastname(""), yearofbirth(0) {
  std::cout << "Person object instantiated without names or birth year\n";
}

Person::Person(std::string const &fn, std::string const &ln, unsigned int yob):
    firstname(fn), lastname(ln), yearofbirth(yob) {
  std::cout << "Person object instatiated: " << firstname << ' '
            << lastname << ", year of birth " << yearofbirth << '\n';
}

Person::~Person() {
  std::cout << "Person " << firstname << ' ' << lastname
            << " born in " << yearofbirth << " goes out of scope\n";
}

void Person::setname(std::string const &fn, std::string const &ln) {
  std::cout << "Person previously known as " << firstname << ' ' << lastname;
  firstname = fn;
  lastname = ln;
  std::cout << " is now " << firstname << ' ' << lastname << '\n';
}

std::string Person::getfirstname() const {
  return firstname;
}

std::string Person::getlastname() const {
  return lastname;
}

void Person::setyearofbirth(unsigned int yob) {
  if (yob < 1900)
    throw "setyearofbirth: year must be >= 1900";

  std::cout << "Person " << firstname << ' ' << lastname << ", born in "
            << yearofbirth;
  yearofbirth = yob;
  std::cout << " is now born in " << yearofbirth << '\n';
}

unsigned int Person::getyearofbirth() const {
  return yearofbirth;
}

// Example of a local object in a called function
void func() {
  Person x ("Scooby", "Doo", 1969);
}

// Example of local object in main, and func() is called to instantiate
// another local object
int main() {
  Person one;
  Person two("Sponge", "Bob", 1999);

  one.setname("Mickey", "Mouse");
  one.setyearofbirth(1928);

  func();

  try {
    // This should fail
    one.setyearofbirth(1800);
  } catch (...) {
    std::cout << "Could not set the birth year to 1800\n";
  }

  return 0;
}

/*
 * Output:
 *  Person object instantiated without names or birth year
 *  Person object instatiated: Sponge Bob, year of birth 1999
 *  Person previously known as   is now Mickey Mouse
 *  Person Mickey Mouse, born in 0 is now born in 1928
 *  Person object instatiated: Scooby Doo, year of birth 1969
 *  Person Scooby Doo born in 1969 goes out of scope
 *  Could not set the birth year to 1800
 *  Person Sponge Bob born in 1999 goes out of scope
 *  Person Mickey Mouse born in 1928 goes out of scope
 */
```
