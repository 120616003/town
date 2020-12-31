#ubuntu 18.04

#安装编译环境
sudo apt update
sudo apt upgrade
sudo apt install cmake gcc g++ build-essential -y

#安装依赖库
sudo apt install mysql-server libmysqlclient-dev libevent-dev -y

#protobuf生成
./protoc --proto_path=/home/yan/Project/town/src/proto/protofile/ --cpp_out=/home/yan/Project/town/src/proto/src user.proto