#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<unistd.h>
 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
#include<event.h>
#include<event2/bufferevent.h>
#include<event2/buffer.h>
#include<event2/util.h>

#include <string>
#include <sstream>
#include <cstring>
#include "user.pb.h"
#include "Booster.hpp"

enum MSG_TYPE : uint32_t {
    MESS_REGISTER = 10001,
    MESS_LOGIN = 10002
};

const std::map<MSG_TYPE, std::string> convert_msg_type = {
    {MESS_REGISTER, "mess_register"}, 
    {MESS_LOGIN, "mess_login"}
};

struct MSG_INFO {
    std::size_t msg_len = 0;
    MSG_TYPE msg_type = MESS_REGISTER;
    std::size_t msg_crc = 0;
};

void cmd_msg_cb(int fd, short events, void* arg);
void server_msg_cb(struct bufferevent* bev, void* arg);
void event_cb(struct bufferevent *bev, short event, void *arg);
std::pair<std::size_t, std::unique_ptr<uint8_t[]>> GetRegisterMsg(const std::string& email, const std::string& passwd);
std::pair<std::size_t, std::unique_ptr<uint8_t[]>> GetLoginMsg(const std::string& email, const std::string& passwd);
std::pair<std::size_t, std::unique_ptr<uint8_t[]>> CopyData(std::string& msg, MSG_TYPE eType);
 
int main(int argc, char** argv)
{
    if( argc < 3 )
    {
        //两个参数依次是服务器端的IP地址、端口号
        printf("please input 2 parameter\n");
        return -1;
    }
 
    struct event_base *base = event_base_new();
 
    struct bufferevent* bev = bufferevent_socket_new(base, -1,
                                                     BEV_OPT_CLOSE_ON_FREE);
 
    //监听终端输入事件
    struct event* ev_cmd = event_new(base, STDIN_FILENO,
                                     EV_READ | EV_PERSIST,
                                     cmd_msg_cb, (void*)bev);
 
 
    event_add(ev_cmd, NULL);
 
    struct sockaddr_in server_addr;
 
    memset(&server_addr, 0, sizeof(server_addr) );
 
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &server_addr.sin_addr);
 
    bufferevent_socket_connect(bev, (struct sockaddr *)&server_addr,
                               sizeof(server_addr));
 
 
    bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, (void*)ev_cmd);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
 
 
 
    event_base_dispatch(base);
 
    printf("finished \n");
    return 0;
}

void cmd_msg_cb(int fd, short events, void* arg)
{
    char buf[1024] = {};
 
    int ret = read(fd, buf, sizeof(buf));
    if( ret < 0 )
    {
        perror("read fail ");
        exit(1);
    }
 
    std::pair<std::size_t, std::unique_ptr<uint8_t[]>> pair;
    std::string msg(buf);
    if (msg.substr(0, msg.size() - 1) == "0") {
        pair = GetRegisterMsg("120616003@qq.com", "12345678");
    }
    else if (msg.substr(0, msg.size() - 1) == "1") {
        pair = GetLoginMsg("120616003@qq.com", "12345678");
    }
    else {
        return;
    }

    struct bufferevent* bev = (struct bufferevent*)arg;
    bufferevent_write(bev, pair.second.get(), pair.first);
    bufferevent_flush(bev, 0, BEV_FINISHED);
}

std::pair<std::size_t, std::unique_ptr<uint8_t[]>> GetRegisterMsg(const std::string& email, const std::string& passwd)
{
    acc_register ar;
    ar.set_type(common_enum::ACC_EMAIL);
    ar.set_email(email);
    ar.set_passwd(passwd);

    std::string msg = ar.SerializeAsString();
    return CopyData(msg, MESS_REGISTER);
}

std::pair<std::size_t, std::unique_ptr<uint8_t[]>> GetLoginMsg(const std::string& email, const std::string& passwd)
{
    acc_login al;
    al.set_type(common_enum::ACC_EMAIL);
    al.set_email(email);
    al.set_passwd(passwd);

    std::string msg = al.SerializeAsString();
    return CopyData(msg, MESS_LOGIN);
}

std::pair<std::size_t, std::unique_ptr<uint8_t[]>> CopyData(std::string& msg, MSG_TYPE eType)
{
    MSG_INFO msg_info;
    msg_info.msg_type = eType;
    msg_info.msg_len = msg.size();
    msg_info.msg_crc = town::Booster::Crc(reinterpret_cast<uint8_t*>(const_cast<char*>(msg.data())), msg_info.msg_len);

    std::unique_ptr<uint8_t[]> buf(new uint8_t[1024]());
    memcpy(buf.get(), &msg_info, sizeof(MSG_INFO));
    memcpy(buf.get() + sizeof(MSG_INFO), msg.data(), msg_info.msg_len);

    return {msg_info.msg_len + sizeof(MSG_INFO), std::move(buf)};
}

void server_msg_cb(struct bufferevent* bev, void* arg)
{
    MSG_INFO msg_info{};
    bufferevent_read(bev, &msg_info, sizeof(MSG_INFO));

    std::unique_ptr<uint8_t[]> data_buf(new uint8_t[msg_info.msg_len]());
    bufferevent_read(bev, data_buf.get(), msg_info.msg_len);

    if (msg_info.msg_type == MESS_REGISTER) {
        acc_register ar;
        if (!ar.ParseFromArray(data_buf.get(), msg_info.msg_len)) {
            printf("parse error\n");
            return;
        }
        printf("msg_info.msg_len:%lu, type:%d\n", msg_info.msg_len, ar.err_type());
    }
    else if (msg_info.msg_type == MESS_LOGIN) {
        acc_login al;
        if (!al.ParseFromArray(data_buf.get(), msg_info.msg_len)) {
            printf("parse error\n");
            return;
        }
        printf("msg_info.msg_len:%lu, type:%d\n", msg_info.msg_len, al.err_type());
        printf("uuid:%s\n", al.uuid().c_str());
    }

}

void event_cb(struct bufferevent *bev, short event, void *arg)
{
 
    if (event & BEV_EVENT_EOF)
        printf("connection closed\n");
    else if (event & BEV_EVENT_ERROR)
        printf("some other error\n");
    else if( event & BEV_EVENT_CONNECTED)
    {
        printf("the client has connected to server\n");
        return ;
    }
 
    // 这将自动close套接字和free读写缓冲区
    bufferevent_free(bev);
 
    struct event *ev = (struct event*)arg;
    event_free(ev);
}