# town服务端文档协议

### `注册 10001`

> **`class ACCRegister;`**

| Field Name   | Type   |
| ------------ | ------ |
| email        | string |
| phone        | string |
| account_name | string |
| passwd       | string |

### `登录 10002`

> **`class ACCLogin;`**

| Field Name   | Type   |
| ------------ | ------ |
| email        | string |
| phone        | string |
| account_name | string |
| passwd       | string |

### `登出 10003`

> **`class ACCLogout;`**

| Field Name   | Type   |
| ------------ | ------ |
| account_name | string |

### `注销 10004`

> **`class ACCCancellation;`**

| Field Name   | Type   |
| ------------ | ------ |
| email        | string |
| phone        | string |
| account_name | string |

### `恢复 10005`

> **`class ACCRecovery;`**

| Field Name   | Type   |
| ------------ | ------ |
| account_name | string |

### `个人信息 10006`

> **`ACCPersonInfo 10006;`**

| Field Name   | Type   |
| ------------ | ------ |
| account_name | string |