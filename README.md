# RedstoneLimiter

Limit redstone frequency on LiteLoaderBDS server

## Usage

`/redstonelimiter reload` Reload configuration file  
`/redstonelimiter set <tick>` Set tick limitation temporarily

## Configuration File

```jsonc
{
    "EnableCommands": true, // Whether enable /redstonelimiter command  
    "TickLimitation": 5 // How many game ticks trigger redstone tick
}
```