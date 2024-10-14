# Pellet dispenser

## Working mechanism

The aim is these flows is to implement a dispenser mechanism,
there the dispensing duration can be set from 1 to 10 seconds.
The dispensing event can be started with a dashboard button.
The dashboard shows a textual status. Initial conditions are
set (dispensing off, duration: 5 sec).

The dispensing time is stored in a flow variable. Most transformations
are implemented with change nodes. Function nodes are used to copy
messages.

