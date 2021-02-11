# Compiler Project Decaf

Komphyler

```
HamidReza Kamkari   97110177

Mostafa Ojaghi      97105782

Yeganeh Gharedaghi  97106216
```

## TAC format
**Input and Output**:
The following commands handle simple input and output of character.

* `Input x`: Takes an *Integer* as an input and writes it in `x`
* `Output x`: Outputs the value in `x`.

**Assign value commands**:

* `Assign x = y`: Set the value of `x` equal to the value of `y`
* `Assign x = a op b`: This command calculates `a op b` and then writes the output
in x. `op` can have forms such as follows:
  * `+`: Add `a` and `b`
  * `-`: Subtract `b` from `a`
  * `*`: Multiply `a` and `b`
  * `/`: Calculate `a` divided by `b`
  * `%`: Calculate `a` mod `b`
  * `<`: If `a` is strictly less than `b` then the value `1` will be written into `x` otherwise `0`
  * `<=`: If `a` is less than or equal to `b` then the value `1` will be written into `x` otherwise `0`
  * `>`: If `a` is strictly larger than `b` then the value `1` will be written into `x` otherwise `0`
  * `>=`: If `a` is larger than or equal to `b` then the value `1` will be written into `x` otherwise `0`
  * `==`: If `a` and `b` are equal then `1` will be written into `x` otherwise `0`
  * `!=`: If `a` and `b` are not equal then `1` will be written into `x` otherwise `0`
  * `&&`: Calculate logical and of `a` and `b` (`a` and `b` should be `0` or `1`)
  * `||`: Calculate logical or of `a` and `b` (`a` and `b` should be `0` or `1`)
* `Assign x = not y`: `y` should be `0` or `1` and the calculated not is written into `x`
* `Assign x = - y`: negate `y` and then write the negated value into `x`

**Labels and goto**:
* `label labelName:`: defines a label to be able to jump to.
* `goto labelName`: A simple jump to label named `labelName`

**Function call commands**:

* `label functionName: param1 param2 param3 ...`: This defines a label, if the label is a function
the parameters `param1`, `param2`, ... are the input arguments.
* `Lcall functionName`: Call the function that has a label named `functionName`
* `Lcall functionName -> r`: Call the function that has a label named `functionName` and then return the value from that function in `r`
* `Pushparam x`: This adds argument `x` to the stack before function call.
* `Popparams sz`: Free the stack
* `Beginfunc sz`: Free the stack by `sz` bytes, this is used to free space for each 
local variable that is used in the function. *Caution*: keep in mind if you have 3 variables in a function
  you should start the function with `Beginfunc 12`.
* `Endfunc`: ends the function.
* `Endfunc var`: returns the value that is stored in `var`


**Exit command**:
* `Exit`: If this line is read then the program exits.

**Global Variables**:
each program in TAC is written as follows:
```
Assign g1 = 0
Assign g2 = 0
Assign g3 = 0
.
.
.
Assign gk = 0
Lcall main
Exit

label main:
Beginfunc s
.
.
.
Endfunc

label func1: arg1 arg2 ...
Beginfunc s1
.
.
.
Endfunc ret1/nothing

label func2: arg1 arg2 ...
.
.
.
```
The variables `g1`, `g2`, ..., `gk` are all global variables and the function
`main` is the function that is being called. Other procedures such as `func1`, `func2` ... 
are all functions that may or may not return value. To call each of these functions an arbitrary amount of
`Pushparam x` may be needed if they have input arguments and then after each function call there should
be a `Popparams sz`.

**Pointers**:
The following commands include memory access.
* `Store *(a + offset) = b`: Store the value of `b` in offset bytes after `a` in memory.
* `Load a = *(b + offset)`: Load the value in addes `b + offset` of memory

##TAC tests

**Simple function call example**:
```
Assign global1 = 10
Assign global2 = 20
Lcall main
Exit

label main:
Assign x = 0
Assign y = 1
Assign z = 2
Pushparam x
Pushparam y
Pushparam z
Lcall function -> r
Popparams 12

label function: z y x
Beginfunc 4
Assign s = x + y
Assign s = s - z
Assign s = s + global1
Endfunc s
```

```
Lcall main
Exit

Label main:
Beginfunc 64
Input s
Output s
Input a
Output a
Assign b = s / a
Assign b = - s
Output b
Pushparam b
Lcall f -> x
Popparams 4
Output x
Endfunc

Label f: c
Beginfunc 64
Output c
Lcall check
Endfunc c

Label check:
Beginfunc 64
Input y
Output y
Endfunc
```
