#创建用户
create user "town"@"localhost" identified by "1"; #本地登录
create user "town"@"%" identified by "1"; #远程登录

#给用户开通数据库权限
grant 权限列表 on 数据库 to '用户名'@'访问主机' ;
grant all privileges on town.* to 'town'@'localhost' identified by '1'; #本地
grant all privileges on town.* to 'town'@'%' identified by '1'; #远程



#刷新系统权限表
flush privileges;

#用户
sudo mysql -uroot -p
1
sudo mysql -utown -p
1

#初始化配置
sudo mysql_secure_installation
#查看状态
systemctl status mysql.service
#创建数据库
create database town;
#创建用户表
create table if not exists user (
	id int auto_increment primary key not null,
	account_number int not null,
	password varchar(20)
);

create user "typecho"@"localhost" identified by "Hui0415+"; 
create user "typecho"@"%" identified by "Hui0415+"; 

grant all privileges on typecho.* to 'typecho'@'%' identified by 'Hui0415+';
grant all privileges on typecho.* to 'typecho'@'localhost' identified by 'Hui0415+';