Console arguments: (use '.' to use default value)
--

1. Screen width
2. Screen height
3. Screen update delay (ms)
4. Spawn probability (0-100) [at first frame of the game]
5. Cell pixel side length (>0)
6. Max evolving generation (>0)

- Sample: `conway.exe 1000 500 10 70 1 200` (100x500 window, 10ms delay, 70% chance of spawning at first frame, evovle 200 generations in total, with cells of 1 pixel of side size)
- Sample: `conway.exe . . . 50 4 .` (default window size, default delay, 50% chance of spawning at first frame, default number of generation evolved, with cells of 4 pixels of side size)


Controls:
--

- ESCAPE, Q: Quit
- P: Pause / Resume 
- Up arrow: Speed up
- Down arrow: Slow down
- Mouse left click and drop: Add live cells
- Mouse right click and drop: Kill cells
