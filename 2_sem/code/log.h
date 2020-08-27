#ifndef LOG_H
#define LOG_H

typedef enum {
	LOG_LEVEL_INFO = 0,
	LOG_LEVEL_ERROR = 1,
} log_level_t;

typedef struct {
	int fd;
} log_t;

log_t *log_open(const char *file_name);
int log_close(log_t *log);
int log_info(log_t *log, const char *format, ...);
int log_error(log_t *log, const char *format, ...);

#endif
