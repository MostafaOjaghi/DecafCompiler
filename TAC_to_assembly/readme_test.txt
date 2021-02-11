Assign global1 = 10
Assign global2 = 20
Lcall main
Exit

Label main:
Beginfunc 100
Assign x = 0
Assign y = 1
Assign z = 2
Pushparam x
Pushparam y
Pushparam z
Lcall function -> r
Popparams 12
Output r
Endfunc 100

Label function: z y x
Beginfunc 4
Assign s = x + y
Assign s = s - z
Assign s = s + global1
Endfunc s