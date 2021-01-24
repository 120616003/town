#ubuntu 18.04

#安装编译环境
sudo apt update
sudo apt upgrade
sudo apt install cmake gcc g++ build-essential -y

#安装依赖库
sudo apt install mysql-server libmysql++-dev libmysqlclient-dev libevent-dev -y