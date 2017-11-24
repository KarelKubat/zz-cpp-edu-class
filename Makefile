all: person test1 test2

person: person.cc
	$(CXX) -g -Wall -o $@ $<

test1: test1.cc
	$(CXX) -g -Wall -o $@ $<

test2: test2.cc
	$(CXX) -g -Wall -o $@ $<

clean:
	rm -f person test1 test2
