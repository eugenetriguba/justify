FROM alpine:3.20.1

RUN apk update && \
    apk upgrade && \
    apk add --no-cache \
	build-base \
	gdb \
	gcc \
	make \
	valgrind \
	bash

WORKDIR /app
COPY . /app

RUN make

ENTRYPOINT ["/bin/bash"]
