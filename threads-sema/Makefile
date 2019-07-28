CC     := gcc
CFLAGS := -Wall -Werror -I../include -pthread

OS     := $(shell uname -s)
LIBS   := 
ifeq ($(OS),Linux)
	LIBS += -pthread
endif

SRCS   := dining_philosophers_deadlock.c \
	dining_philosophers_deadlock_print.c \
	dining_philosophers_no_deadlock.c \
	dining_philosophers_no_deadlock_print.c \
	join.c \
	binary.c \
	producer_consumer_works.c \
	rwlock.c \
	zemaphore.c \
	throttle.c 

OBJS   := ${SRCS:c=o}
PROGS  := ${SRCS:.c=}

.PHONY: all
all: ${PROGS}

${PROGS} : % : %.o Makefile
	${CC} $< -o $@ ${LIBS}

clean:
	rm -f ${PROGS} ${OBJS}

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<
