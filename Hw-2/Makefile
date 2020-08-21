TARGET = main.out
TARGET_TEST = test.out
HDRS_DIR = project/include

SRCS = \
	project/src/main.c \
	project/src/file.c \
	project/src/func.c \
	project/src/data.c

SRCS_TEST = \
	project/src/main_test.c \
	project/src/test.c \
	project/src/file.c \
	project/src/func.c \
	project/src/data.c

.PHONY: all clean

all: main test

main: $(SRCS)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)


test: $(SRCS_TEST)
	$(CC) -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET_TEST) $(CFLAGS) $(SRCS_TEST)

clean:
	rm -rf $(TARGET) $(TARGET_TEST)
