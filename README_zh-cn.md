# RedstoneLimiter

[English](README.md) | 简体中文  
在LiteLoaderBDS服务器上限制红石频率

## 安装

### 使用Lip

```bash
lip install RedstoneLimiter
```

### 手动安装

从[Release](https://github.com/ShrBox/RedstoneLimiter/releases)中下载

## 使用方法

`/redstonelimiter reload` 重载配置文件  
`/redstonelimiter set <tick>` 临时设置刻限制

## 配置文件

```jsonc
{
    "EnableCommands": true, // 是否启用 /redstonelimiter 指令  
    "TickLimitation": 5 // 多少游戏刻触发一次红石刻
}
```