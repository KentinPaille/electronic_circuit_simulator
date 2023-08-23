### Description
NanoTekSpice is a logic simulator that builds a graph (the nodes of which will be simulated digital electronic
components, inputs or outputs) from a configuration file, and injects values into that graph to get results.

Usage:

```
$ make

$ ./nanotekspice
Usage: ./nanotekspice circuit/FILE.nts 


SHELL:
        exit:           closes the program.
        display:      prints the current tick and the value of all inputs and outputs in the standard output.
        input=value:    changes the value of an input. Possible value are 0, 1 and U. This also apply to clocks. Use *=value to change all inputs in same time.
        simulate:     simulate a tick of the circuit.
        loop:         continuously runs the simulation (simulate, display, simulate, ...) without displaying a prompt, until SIGINT is received.

```

Demo:

```
$ ./nanotekspice circuit/or.nts
> display
tick: 0
input(s):
  in_1: U
  in_2: U
output(s):
  out: U
> in_1=0
> in_2=0
> simulate
> display
tick: 1
input(s):
  in_1: 0
  in_2: 0
output(s):
  out: 0
> in_2=1
> simulate
> display
tick: 2
input(s):
  in_1: 0
  in_2: 1
output(s):
  out: 1
> exit
```
