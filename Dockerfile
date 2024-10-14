# 使用 Alpine 作为基础镜像
FROM ubuntu:22.04

# 设置工作目录
WORKDIR /app

# 复制本地文件到容器中（可选）
COPY ./lyra /lyra
COPY ./bazel_5.3.2-linux-x86_64.deb /app/bazel_5.3.2-linux-x86_64.deb
RUN apt update
RUN apt install g++ zlib1g-dev unzip git python3 -y
RUN apt install g++ zlib1g-dev unzip git python3-pip -y
RUN pip3 install numpy
#proxy地址，设置为你自己的再build
RUN export HTTP_PROXY=http://172.17.0.1:7897/
RUN export HTTPS_PROXY=http://172.17.0.1:7897/
RUN git config --global http.proxy http://172.17.0.1:7897/
RUN git config --global https.proxy http://172.17.0.1:7897/

RUN dpkg -i /app/bazel_5.3.2-linux-x86_64.deb
WORKDIR /lyra
RUN bazel build -c opt lyra/cli_example:encoder_main
RUN bazel build -c opt lyra/cli_example:decoder_main
CMD ["bash"]
