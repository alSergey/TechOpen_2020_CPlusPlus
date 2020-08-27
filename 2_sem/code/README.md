module: process
1. Демонизация
	bash (pid: bash_pid) -> fork & exec -> hserver (pid: hserver_pid; ppid: bash_pid; fds: stdin, stdout, stderr)
		hserver close(stdin) close(stdout) close(stderr)
		hsever fork() -> hserver_child(pid: hserver_child_pid; ppid: hserver_pid)
		hserver exit() -> hsrever_child(pid: hserver_child_pid; ppid: 1 (init))
		setsid()
		create pid file

2. Управление сигналами
	SIGTERM

	static int is_exited = 0;

	void sigterm_handler(int sig) {
		is_exitd = 1;
	}

	...
	int main

	signal()

	while (1) {
		client = accept(server)
		http_handle(client)
		if (is_exited)
			break;
	}

module: log
3. Логгирование
	log_open()
	log_close()
	log_info(log, format, ...);
	log_error(log, format, ...);

module: network
4. Сеть
	network_open()
	network_close()
	network_accept()

module: http
5. HTTP протокол
	METHOD URL PROTOCOL\n  ==   GET /cat.gif HTTP/1.1\n
	HEADER_NAME: HEADER_VALUE\n Host: mail.ru
	HEADER_NAME: HEADER_VALUE\n
	\n

	PROTOCOL STATUS MESSAGE\n == HTTP/1.1 200 Ok
	HEADER_NAME: HEADER_VALUE\n
	Content-Type: text/html\n
	Content-Length: DATA_LEN\n
	\n
	DATA

    method_begin
	|
	GET /abcebeua HTTP/1.0
           |
        method_end

	URL HOST

localohst
index.html

/var/www/HOST/URL

mail.ru/

/var/www/mail.ru/index.html
