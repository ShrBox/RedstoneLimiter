# RedstoneLimiter

English | [简体中文](README_zh-cn.md)  
Limit redstone frequency on LiteLoaderBDS server

## Installation

### Use Lip

```bash
lip install github.com/Tooth-Hub/RedstoneLimiter
```

### Manual

Download from [Release](https://github.com/ShrBox/RedstoneLimiter/releases)

## Usage

`/redstonelimiter reload` Reload configuration file  
`/redstonelimiter set <tick>` Set tick limitation temporarily

## Configuration File

```jsonc
{
    "EnableCommands": true, // Whether to enable /redstonelimiter command  
    "TickLimitation": 5 // How many game ticks trigger redstone tick
}
```
