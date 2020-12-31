# town服务端文档协议

### `注册 10001`

> **`class AccRegister;`**

| Field Name   | Type   |
| ------------ | ------ |
| type         | int    |
| email        | string |
| phone        | string |
| accname      | string |
| passwd       | string |

### `登录 10002`

> **`class AccLogin;`**

| Field Name   | Type   |
| ------------ | ------ |
| email        | string |
| phone        | string |
| accname      | string |
| passwd       | string |

### `登出 10003`

> **`class AccLogout;`**

| Field Name   | Type   |
| ------------ | ------ |
| accname      | string |

### `注销 10004`

> **`class AccCancellation;`**

| Field Name   | Type   |
| ------------ | ------ |
| email        | string |
| phone        | string |
| accname      | string |

### `恢复 10005`

> **`class AccRecovery;`**

| Field Name   | Type   |
| ------------ | ------ |
| accname      | string |

### `个人信息 10006`

> **`AccPersonInfo 10006;`**

| Field Name   | Type   |
| ------------ | ------ |
| accname      | string |
| name         | string |
| age          | int32  |