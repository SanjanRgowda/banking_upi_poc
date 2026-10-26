CC=gcc
CXX=g++

CFLAGS=-Wall -Wextra -g --coverage
SSLFLAGS=-lssl -lcrypto
GTESTFLAGS=-lgtest -lgtest_main -pthread

TARGET=banking

SRC=main.c auth.c crypto.c transaction.c audit.c

REPORTS=reports

all:
	mkdir -p $(REPORTS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(SSLFLAGS)

test_crypto:
	mkdir -p $(REPORTS)
	$(CC) $(CFLAGS) -c crypto.c -o crypto.o
	$(CXX) $(CFLAGS) test_crypto.cpp crypto.o \
	$(GTESTFLAGS) $(SSLFLAGS) \
	-o test_crypto
	./test_crypto > $(REPORTS)/gtest_crypto.txt

test_auth:
	mkdir -p $(REPORTS)
	$(CC) $(CFLAGS) -c auth.c -o auth.o
	$(CC) $(CFLAGS) -c crypto.c -o crypto.o
	$(CXX) $(CFLAGS) test_auth.cpp auth.o crypto.o \
	$(GTESTFLAGS) $(SSLFLAGS) \
	-o test_auth
	./test_auth > $(REPORTS)/gtest_auth.txt

test_transaction:
	mkdir -p $(REPORTS)
	$(CC) $(CFLAGS) -c transaction.c -o transaction.o
	$(CC) $(CFLAGS) -c crypto.c -o crypto.o
	$(CXX) $(CFLAGS) test_transaction.cpp transaction.o crypto.o \
	$(GTESTFLAGS) $(SSLFLAGS) \
	-o test_transaction
	./test_transaction > $(REPORTS)/gtest_transaction.txt

test_audit:
	mkdir -p $(REPORTS)
	$(CC) $(CFLAGS) -c audit.c -o audit.o
	$(CXX) $(CFLAGS) test_audit.cpp audit.o \
	$(GTESTFLAGS) \
	-o test_audit
	./test_audit > $(REPORTS)/gtest_audit.txt

coverage_crypto:
	gcov crypto.c > $(REPORTS)/coverage_crypto.txt

coverage_auth:
	gcov auth.c > $(REPORTS)/coverage_auth.txt

coverage_transaction:
	gcov transaction.c > $(REPORTS)/coverage_transaction.txt

coverage_audit:
	gcov audit.c > $(REPORTS)/coverage_audit.txt

coverage: coverage_crypto coverage_auth coverage_transaction coverage_audit

valgrind:
	mkdir -p $(REPORTS)
	echo "7" > input.txt
	$(CC) -g $(SRC) -o $(TARGET) $(SSLFLAGS)
	valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./$(TARGET) < input.txt \
	> $(REPORTS)/valgrind_report.txt 2>&1

clean:
	rm -f *.o
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f test_crypto
	rm -f test_auth
	rm -f test_transaction
	rm -f test_audit
	rm -f banking