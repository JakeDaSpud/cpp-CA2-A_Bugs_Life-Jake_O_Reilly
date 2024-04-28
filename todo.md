# A Bug's Life

---

## To-do
- [x] Create Plan/Checklist for Project
- [x] Make Classes
- [x] Make Menu
- [x] Implement all functions
- [ ] Custom Controllable ```Bug```
- [x] New ```Bug``` type's ```move()``` uses int interval, where it moves 2 spaces instead of 1, every interval moves it makes

### Classes
- [x] Plan ```Bug``` Class 
- - [x] Create ```Bug``` Class
- - - string / enum type 
- - - int id
- - - int x
- - - int y
- - - int direction
- - - int size
- - [x] Create ```Crawler``` Class (Inherits ```Bug```)
- - [x] Create ```Hopper``` Class (Inherits ```Bug```)
- - - int hopLength

---

### Main

- [x] Look up Low Level Learning for how to use .h header files
- [x] Include .h header files (is that right? or do i include the .cpp files?) for ```Bug```, ```Crawler``` and ```Hopper```
- [x] Make bugs.txt: input file for all bugs to be instantiated (e.g. "```C;101;0;0;4;10``` ```H;102;9;0;1;8;2```")
- [x] Make Menu System
- - [x] Dummy items 1-8
- - [x] Menu 1: Initialise board (load ```Bug```s from ```bugs.txt```)
- - [x] Menu 2: Display all ```Bug```s
- - [x] Menu 3: Find a ```Bug``` from id
- - [x] Menu 4: Tap the board (```moveAll()``` -> ```fight()``` or ```eat()```)
- - [x] Menu 5: Display history of all ```Bug```s (path taken ***AND ACTIONS? ASKKKKKKK***)
- - [x] Menu 6: Display all cells listing their bugs (i.e "```6-3: Empty``` ```0-5: Crawler 64, Hopper 33```)
- - [x] Menu 7: Run simulation (run ```tap()``` every second)
- - [x] Menu 8: Write current ```Bug``` history to a file, then Exit app 