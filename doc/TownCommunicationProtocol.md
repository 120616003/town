# town服务端文档协议

### `注册 10001`

> **`class acc_register;`**

| Field Name   | Type   |
| ------------ | ------ |
| type         | enum   |
| email        | string |
| phone        | string |
| name         | string |
| passwd       | string |
| err_type     | enum   |

### `登录 10002`

> **`class acc_login;`**

| Field Name   | Type   |
| ------------ | ------ |
| type         | enum   |
| email        | string |
| phone        | string |
| name         | string |
| passwd       | string |
| err_type     | enum   |
| uuid         | string |

### `登出 10003`

> **`class acc_logout;`**

| Field Name   | Type   |
| ------------ | ------ |
| type         | enum   |
| email        | string |
| phone        | string |
| name         | string |
| err_type     | enum   |
| uuid         | string |

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