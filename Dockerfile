FROM ubuntu:23.04

ADD . /app

RUN chmod 777 /app/scripts/auto-dependency-install.sh
RUN chmod 777 /app/scripts/build-server-rel.sh

RUN /app/scripts/auto-dependency-install.sh
RUN /app/scripts/build-server-rel.sh

ENTRYPOINT ["/app/out/Release/server"]