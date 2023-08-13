PROJECTNAME=3DViewer

CC=g++
CXXFLAGS=-c -fPIC -Wall -Werror -Wextra -Wpedantic -std=c++17 `pkg-config --cflags Qt5Gui`
LDFLAGS=`pkg-config --libs Qt5Gui` -lgtest -lm -pthread

SRCFILES=src/model/*.cc src/view/*.cc
HDRFILES=$(SRCFILES:.cc=.h)
LIBSRC=src/model/transform_matrix.cc src/model/transform_matrix_builder.cc src/model/file_reader.cc
LIBOBJ=$(LIBSRC:.cc=.o)

TESTSRC=./tests/tests.cc
TESTOBJ=$(TESTSRC:.cc=.o)
EXECUTABLE=./tests/$(PROJECTNAME)_tests

INSTALLDIR=build

LCOVEXEC=$(EXECUTABLE).info
REPORTDIR=report

LEAKS_REPORT_FILE=leaks_report.txt
LEAKS_LINUX=valgrind --leak-check=full --verbose --log-file=$(REPORTDIR)/$(LEAKS_REPORT_FILE)
LEAKS_MAC=leaks -atExit --
UNAME_S=$(shell uname -s)
DVI_FILE=Readme

.PHONY: all install uninstall clean dvi dist build_tests tests gcov_report style cppcheck

all: install

%.o: %.cc
	$(CC) $(CXXFLAGS) $^ -o $@

install: uninstall
	@mkdir $(INSTALLDIR) && cd $(INSTALLDIR) && \qmake ../$(PROJECTNAME).pro && \
	make && make clean && rm -f Makefile .qmake.stash

uninstall:
	@rm -rf $(INSTALLDIR)

clean:
	@rm -f $(EXECUTABLE) $(LCOVEXEC) $(DVI_FILE).pdf
	@rm -rf $(REPORTDIR) $(INSTALLDIR)
	@find . -type f -name "*.o" -exec rm -f {} \;
	@find . -type f -name "*.gcda" -exec rm -f {} \;
	@find . -type f -name "*.gcno" -exec rm -f {} \;
	@find . -type f -name "*.dot" -exec rm -f {} \;
	@find . -type f -name "*.info" -exec rm -f {} \;

dvi:
	texi2pdf $(DVI_FILE).tex -o $(DVI_FILE).pdf -q
	rm -rf *.aux *.log *.toc

dist: install
	@cd $(INSTALLDIR) && tar -czf $(PROJECTNAME).tgz $(PROJECTNAME) && rm -f $(PROJECTNAME)

build_tests: clean $(TESTOBJ) $(LIBOBJ)
	$(CC) $(TESTOBJ) $(LIBOBJ) -o $(EXECUTABLE) $(LDFLAGS)

tests: build_tests
	./$(EXECUTABLE)

style:
	clang-format -n $(HDRFILES) $(SRCFILES) main.cc

cppcheck:
	cppcheck --language=c++ ./controller/*.cc ./controller/*.h ./model/*.cc ./model/*.h ./view/*.cc ./view/*.h main.cc

gcov_report: CXXFLAGS+=--coverage
gcov_report: LDFLAGS+=--coverage
gcov_report: tests
	lcov -t $(EXECUTABLE) -o $(LCOVEXEC) --include */src/model/*.cc -c -d ./model 
	genhtml -o $(REPORTDIR) $(LCOVEXEC)
