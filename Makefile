CXX := g++
CXX_ARGS := -std=c++17
TARGETS := foo baz

all: $(TARGETS)

sync: *.ll *.hh Makefile *.foo *.baz
	- scp -r ./*ll ./*.hh ./Makefile *.foo *.baz patty:foo

%: %.cc %.hh
	$(CXX) $(CXX_ARGS) -g -o $@ $*.cc

%.cc: %.ll %.hh
	flex -o $@ $*.ll

clean:
	-rm -rf $(TARGETS)
	-rm -rf *.dSYM
	-rm -rf *.cc

.PHONY: clean sync
