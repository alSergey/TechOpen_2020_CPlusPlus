#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "log.h"

#define MESSAGE_SIZE 4096

static char *log_levels[] = {
	"info",
	"error",
};

log_t *log_open(const char *file_name) {

	log_t *log = calloc(1, sizeof(log_t));
	if (!log)
		return NULL;

	log->fd = open(file_name, O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	if (log->fd == -1) {
		free(log);
		return NULL;
	}

	return log;
}

int log_close(log_t *log) {
	int rc = close(log->fd);
	free(log);
	return rc;
}

static int log_message(log_t *log, log_level_t level, const char *format, va_list args) {
	char message[MESSAGE_SIZE];
	size_t offset = 0;

	time_t t = time(NULL);
	struct tm tm;
	localtime_r(&t, &tm);
	offset += strftime(message + offset, sizeof(message) - offset, "%Y-%m-%d %H:%M:%S %z\t", &tm);
	offset += snprintf(message + offset, sizeof(message) - offset, "[%s]\t%lu\t", log_levels[level], (unsigned long)getpid());
	offset += vsnprintf(message + offset, sizeof(message) - offset, format, args);
	offset += snprintf(message + offset, sizeof(message) - offset, "\n");
	return write(log->fd, message, offset);
}

int log_info(log_t *log, const char *format, ...) {
	va_list args;
	va_start(args, format);
	int rc = log_message(log, LOG_LEVEL_INFO, format, args);
	va_end(args);
	return rc;
}

int log_error(log_t *log, const char *format, ...) {
	va_list args;
	va_start(args, format);
	int rc = log_message(log, LOG_LEVEL_ERROR, format, args);
	va_end(args);
	return rc;
}
