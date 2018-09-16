FROM ubuntu:16.04
RUN apt-get update
RUN apt-get -y install cmake gcc g++
ADD . native
RUN cd native && cmake . -DCMAKE_BUILD_TYPE=Release && make native_static -j8 && make native -j8 && make install
RUN export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
RUN rm -rf native
WORKDIR /
