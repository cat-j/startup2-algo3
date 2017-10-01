CXXFLAGS=-g -std=c++11 -pedantic -Wall

test: elcondor tests/1.in
	./elcondor < tests/1.in

# elcondor.o: elcondor.h elcondor.cpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

# disjoint_set_union.o: disjoint_set_union.h
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $<

elcondor: elcondor.o disjoint_set_union.o
	$(CXX) $(CXXFLAGS) -o $@ $^
