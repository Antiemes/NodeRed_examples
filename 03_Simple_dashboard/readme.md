# Injecting different numbers

## Working mechanism

With the 4 *inject* nodes fixed values can be emitted. All values are then displayed as
debug messages and put on a *chart*. The chart can be accessed through the dashboard (/ui URL).

The second version of the flow contains a *function*, which copies the incoming message to
its output and reduces the number of connections.

## Used node types

* inject
* debug
* chart
* function

