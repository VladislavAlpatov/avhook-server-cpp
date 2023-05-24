FROM ubuntu:23.04

ADD . /app
ADD ./etc /app/out/Release/server

RUN apt update -y
RUN apt upgrade -y
RUN apt install -y libsqlite3-dev libboost-all-dev libfmt-dev libgtest-dev cmake clang ninja-build

WORKDIR /app

RUN cmake --preset x64-release -S .
RUN cmake --build cmake-build/build/x64-release --target server -j 6

EXPOSE 7777

CMD ["/app/out/Release/server"]