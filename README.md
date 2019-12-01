# Cimulink

Reduce combinational boolean algebra expressions with optional mapping to ZedBoard I/O.

## Examples:
In 'traditional' notation,
```
AB + AB' 
= A(B + B') 
= A
```
Variables are mapped to 0-8, so as an S-Expression,
```
(or (and 0 1) (and 0 (not 1))) 
= (and 0 (or 1 (not 1))) 
= 0
```
Verifying:
```shell
> ./cimulink "(or (and 0 1) (and 0 (not 1)))"
0
```