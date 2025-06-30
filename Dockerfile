FROM alpine:3.22.0

RUN apk update && \
	apk upgrade && \
	apk add --no-cache \
	build-base \
	pkgconf \
	cmocka \
	cmocka-dev \
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
