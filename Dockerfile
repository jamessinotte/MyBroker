# Dockerfile
FROM mongodb/mongo-cxx-driver:3.10.1-redhat-ubi-9.4

WORKDIR /build

RUN microdnf upgrade -y && microdnf install -y g++

COPY ping.cpp /build/

RUN g++ \
    -o ping \
    ping.cpp \
    -I/usr/local/include/bsoncxx/v_noabi/ \
    -I/usr/local/include/mongocxx/v_noabi/ \
    -lmongocxx \
    -lbsoncxx

CMD /build/ping