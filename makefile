# Makefile
CXX = g++
CXXFLAGS += -Wall
CXXFLAGS += -g

TARGET = retirement

SRCS = retirement.cpp Expenses.cpp TaxProg.cpp

HEADERS = Tax.h Expenses.h Economy.h User.h Income.h Savings.h TaxProg.h

OBJS = ${SRCS:.cpp=.o}

${TARGET}: ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o ${TARGET}

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c ${SRCS:.o=.cpp}

clean:
	rm -f *.o
