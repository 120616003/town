# town服务端文档协议

### `10001 注册`

> **`class acc_register`**

| Field Name    | Type   | Transmission Direction   | comment |
| ------------- | ------ | ------------------------ | ------- |
| type          | enum   | client -> server         | 用户类型 |
| email         | string | client -> server         | 邮箱 |
| phone         | string | client -> server         | 手机号码 |
| passwd        | string | client -> server         | 密码 |
| err_type      | enum   | server -> client         | 错误码 |

### `10002 登录`

> **`class acc_login`**

| Field Name    | Type   | Transmission Direction   | comment |
| ------------- | ------ | ------------------------ | ------- |
| type          | enum   | client -> server         | 用户类型 |
| email         | string | client -> server         | 邮箱 |
| phone         | string | client -> server         | 手机号码 |
| name          | string | client -> server         | 用户名 |
| passwd        | string | client -> server         | 密码 |
| err_type      | enum   | server -> client         | 错误码 |
| uuid          | string | server -> client         | token 认证 key |

### `10003 账户信息`

> **`class acc_info`**

| Field Name    | Type   | Transmission Direction   | comment |
| ------------- | ------ | ------------------------ | ------- |
| email         | string | server -> client         | 邮箱 |
| phone         | string | server -> client         | 手机号码 |
| name          | string | server -> client         | 用户名 |

### `10004 个人信息`

> **`class user_info`**

| Field Name    | Type   | Transmission Direction   | comment |
| ------------- | ------ | ------------------------ | ------- |
| name          | string | server -> client         | 用户名 |
| nick_name     | string | server -> client         | 昵称 |
| remarks       | string | server -> client         | 备注 |
| sex           | int32  | server -> client         | 性别 |
| birthday      | string | server -> client         | 生日 |
| head_portrait | bytes  | server -> client         | 头像 |
| err_type      | enum   | server -> client         | 错误码 |

### `10005 好友信息`

> **`class friend_info`**

| Field Name    | Type               | Transmission Direction   | comment |
| ------------- | ------------------ | ------------------------ | ------- |
| friend_info   | repeated user_info | server -> client         | 用户名 |
| err_type      | enum               | server -> client         | 错误码 |