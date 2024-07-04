FROM alpine:3.20.1

RUN apk update && \
	apk upgrade && \
	apk add --no-cache \
	build-base \
	lldb \
	clang \
	cmake \
	valgrind \
	bash \
	vim

WORKDIR /app
COPY . /app

RUN mkdir build \
	&& cd build \
	&& cmake .. \
	&& cmake --build .

ENTRYPOINT ["/bin/bash"]
