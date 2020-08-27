all: hserver

hserver: hserver.o log.o process.o network.o http.o http_request.o http_response.o
	gcc -o $@ $^

%.o: %.c
	gcc -g -o $@ -c $^

clean:
	rm -f hserver

.PHONY: all clean
