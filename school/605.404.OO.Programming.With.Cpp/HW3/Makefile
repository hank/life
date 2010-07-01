all: p2

p2: p2.cpp stock.cpp stocksnapshot.cpp stockutil.cpp
	g++ -o p2 p2.cpp stockutil.cpp stock.cpp stocksnapshot.cpp \
		-lboost_date_time -lboost_filesystem -lboost_regex -g -Wall
