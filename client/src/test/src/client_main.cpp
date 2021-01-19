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

struct MSG_INFO{
    std::size_t msg_len = 0;
    enum MSG_TYPE : uint32_t {
        MESS_REGISTER = 0,
        MESS_LOGIN = 1
    } msg_type = MESS_REGISTER;
    std::size_t msg_crc = 0;
};

void cmd_msg_cb(int fd, short events, void* arg);
void server_msg_cb(struct bufferevent* bev, void* arg);
void event_cb(struct bufferevent *bev, short event, void *arg);
 
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

int count = 0;

void cmd_msg_cb(int fd, short events, void* arg)
{
    char buf[1024] = {};
 
    int ret = read(fd, buf, sizeof(buf));
    if( ret < 0 )
    {
        perror("read fail ");
        exit(1);
    }
 
    struct bufferevent* bev = (struct bufferevent*)arg;
 
    // 把终端的消息发送给服务器端

    std::string msg;
    MSG_INFO msg_info{};
    if (count % 2) {
        acc_login al;
        al.set_type(common_enum::ACC_PHONE);
        al.set_email("1249152106@qq.com");
        al.set_passwd("000000");
        msg = std::move(al.SerializeAsString());
        msg_info.msg_type = MSG_INFO::MESS_LOGIN;
    }
    else {
        acc_register ar;
        ar.set_type(common_enum::ACC_EMAIL);
        ar.set_email("120616003@qq.com");
        ar.set_passwd("123456");
        msg = std::move(ar.SerializeAsString());
        msg_info.msg_type = MSG_INFO::MESS_REGISTER;
    }

    
    msg_info.msg_len = msg.size();
    msg_info.msg_crc = town::Booster::Crc(reinterpret_cast<uint8_t*>(const_cast<char*>(msg.data())), msg_info.msg_len);

    memcpy(buf, &msg_info, sizeof(MSG_INFO));
    memcpy(buf + sizeof(MSG_INFO), msg.data(), msg_info.msg_len);
    bufferevent_write(bev, buf, msg_info.msg_len + sizeof(MSG_INFO));
    count++;
}

void server_msg_cb(struct bufferevent* bev, void* arg)
{
    char msg[1024];
 
    size_t len = bufferevent_read(bev, msg, sizeof(msg));
    msg[len] = '\0';
 
    printf("recv %s from server\n", msg);
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