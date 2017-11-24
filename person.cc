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
