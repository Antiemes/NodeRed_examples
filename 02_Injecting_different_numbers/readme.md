# Injecting different numbers

## Working mechanism

Multiple gray *inject* nodes are present in the flow, each can emit
a different number. All nodes are connected to the same *debug* node.
With this mechanism  different fixed messages can be emitted to the
same sink.

## Used node types

* inject
* debug

