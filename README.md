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
As an example with additional logic, adding a not:
```
A'B + A'B' 
= A'(B + B') 
= A'
```
```
(or (and (not 0) 1) (and (not 0) (not 1))) 
= (and (not 0) (or 1 (not 1))) 
= (not 0)
```
```shell
> ./cimulink "(or (and (not 0) 1) (and (not 0) (not 1)))"
(not 0)
```

## Axioms:
The input S-Expression is parsed into a tree. Checking for 8 axioms (some redundant) allows for arbitrary reduction.
### Identity
```
  or
 /  \   ==> X
X    0      
```
```
  and
 /   \   ==> X
X     1      
```
### Null
```
  or
 /  \   ==> 1
X    1      
```
```
  and
 /   \   ==> 0
X     0      
```
### Idempotency
```
  or
 /  \   ==> X
X    X      
```
```
  and
 /   \   ==> X
X     X      
```
### Involution
```
not
 |
not   ==> X
 |
 X
```
### Complementarity
```
  or
 /  \
X   not   ==> T
     |
     X
```
```
  and
 /   \
X    not   ==> F
      |
      X
```
### Commutativity
```
  and            and
 /   \   ==>    /   \
X     Y        Y     X
```
```
  or            or
 /  \   ==>    /  \
X    Y        Y    X
```
### Associativity
```
  or                or
 /  \       ==>    /  \
X   or            Y   or
   /  \              /  \
  Y    Z            X    Z
```
```
  and                and
 /   \       ==>    /   \
X    and           Y    and
    /   \              /   \
   Y     Z            X     Z
```

### Distributivity
```
      and                  or
    /     \               /  \
  or        or     ==>   X   and
 /  \      /  \             /   \
X    Y    X    Z           Y     Z
```
```
        or                   and
      /    \                /   \
  and        and     ==>   X    or
 /   \      /   \              /  \
X     Y    X     Z            Y    Z
```