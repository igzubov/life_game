# The game of life
Look how a system evolve every generation until it dies or starts to repeat

## Rules
The game consist of simple rules:
- Any live cell with fewer than two live neighbours dies, as if by underpopulation
- Any live cell with two or three live neighbours lives on to the next generation
- Any live cell with more than three live neighbours dies, as if by overpopulation
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction

## How to play

1. ``` git clone https://github.com/igzubov/life_game/ && cd life_game```
2. ``` mkdir build && cd build ```
3. ``` cmake .. && make ```
4. Place initial_state_file in the folder with executable **life_game**
5. ``` ./life_game initial_state_file ```, 
where **initial_state_file** is a file containing initial state of the world in the next format:  
m n    
cell_00 cell_01 ... cell_0n    
cell_10 cell_11 ... cell_1n   
...     ...     ... ...    
cell_m0 cell_m1 ... cell_mn

The size of initial state must be **at least 2x2**, every cell can be **either 0 or 1**.    
For example use points.txt from this repository, the result of evolution will be in the file gameOutput.txt.   
To continuously watch it in console run:    
``` watch cat gameOutput.txt ```
