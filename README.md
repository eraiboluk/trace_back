# trace_back

---

## A trace back implementation in c with using only gcc functions

It can be used for debuging, error finding, creating a dump

It can be modified so that it doesnt ask for executable name when called.

Uses \_\_builtin_return_address() function to find the return address then manipulates memory to find the function address and uses nm command to find the name of the functions.

```
It only works when the main (start of the code) is at the bottom of the code. Otherwise it crashes after complating the trace_back.
```
