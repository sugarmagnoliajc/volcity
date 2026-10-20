# volcity - Initial ideas:
Begin with a printable rxc board, probably in a 2D-vector

Each cell can contain an object with information about the building / feature on that cell

ASCII art, at least to begin with (unicode would give us more symbols if we can figure that out)



### Example board section:

Key: – and | are roads, H - hospital, $ - store, @ - home, . - empty
```
   1    2     3   4    5    6    7
a  –    –     –   |    –    –    H
b  .    .     @   |    $    .    .    
c  .    .     @   |    $    .    .   
…
```

### Input/Output
Have command line prompt running with command ‘h’ to list options and syntax

[command] [row] [col]   

for example   “info a 7” returns information about a7, which contains the hospital in the example board above
```
> info a 7
Building:   Hospital
Population: [number]
…
```
Reprint board after every action

This should give us a good base to build the actual interactions/gameplay on top of

### Functionality considerations: 
Board can be expanded easily if we always resize our vector with the empty cell object 

Most things like the building type, population and how it displays can be stored within the object

### Design considerations: 
Some buildings could be represented with multiple characters for more detail as long as we keep spacing consistent

For example upgraded hospital could look like “=H=” (a huge hospital with multiple wings, use your imagination)
