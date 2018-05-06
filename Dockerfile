FROM alpine:3.7

WORKDIR /src
RUN apk add --update --no-cache \
    build-base  \
    ncurses-dev \
    cmake       \
    ruby

COPY . ./
RUN mkdir build                             \
    && cd build                             \
    && cmake .. -DCMAKE_BUILD_TYPE=Release  \
    && make -j4                             \
    && make install

CMD ["/usr/local/bin/citizenhack"]
