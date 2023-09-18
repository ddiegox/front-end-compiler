.PHONY: clean all

all: kfe

main: kfe main

kfe:    driver.o parser.o scanner.o kfe.o
	clang++ -o kfe driver.o parser.o scanner.o kfe.o `llvm-config --cxxflags --ldflags --libs --libfiles --system-libs`

kfe.o:  kfe.cc driver.hh
	clang++ -c kfe.cc -I/usr/local/opt/llvm/include -std=c++17  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -L/usr/lib/llvm-14/lib -lLLVM-14
	
parser.o: parser.cc
	clang++ -c parser.cc -I/usr/local/opt/llvm/include -std=c++17 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
	
scanner.o: scanner.cc parser.hh
	clang++ -c scanner.cc -I/usr/local/opt/llvm/include -std=c++17 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS 
	
driver.o: driver.cc parser.hh driver.hh utility.hh
	clang++ -c driver.cc -I/usr/local/opt/llvm/include -std=c++17  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS 

parser.cc, parser.hh: parser.yy 
	bison -o parser.cc parser.yy

scanner.cc: scanner.ll
	flex -o scanner.cc scanner.ll

main: main.o simplefun.o
	clang++ -o main main.o simplefun.o 

main.o: main.cc
	clang++ -c main.cc

simplefun.o: simplefun.k
	./kfe -o simplefun simplefun.k

externusage.o: externusage.k
	./kfe -o externusage externusage.k

clean:
	rm -f *~ driver.o scanner.o parser.o kfe.o kfe scanner.cc parser.cc parser.hh main.o simplefun.o
