# Push\_swap

This project is about sorting numbers considering two stacks and using only the following instructions:
* `sa` : swap a - swap the first 2 elements at the top of stack a . Do nothing if there is only one or no elements).
* `sb` : swap b - swap the first 2 elements at the top of stack b . Do nothing if there is only one or no elements).
* `ss` : sa and sb at the same time.
* `pa` : push a - take the first element at the top of b and put it at the top of a . Do nothing if b is empty.
* `pb` : push b - take the first element at the top of a and put it at the top of b . Do nothing if a is empty.
* `ra` : rotate a - shift up all elements of stack a by 1. The first element becomes the last one.
* `rb` : rotate b - shift up all elements of stack b by 1. The first element becomes the last one.
* `rr` : ra and rb at the same time.
* `rra` : reverse rotate a - shift down all elements of stack a by 1. The flast element becomes the first one.
* `rrb` : reverse rotate b - shift down all elements of stack b by 1. The flast element becomes the first one.
* `rrr` : rra and rrb at the same time

## Getting Started

### Usage

To generate the set of instructions for a set of numbers:
```
./push_swap n1 n2 n3...
```
and to check wether the set of instructions really sorts:
```
./push_swap n1 n2 n3... | ./checker [-v] n1 n2 n3 ...
```

#### Example
```
ARG=`ruby -e "puts (-50..50).to_a.shuffle.join(' ')"` ; ./push_swap $ARG | ./checker -v $ARG
```

#### Visualizer

The visualizer have several commands:
* Right arrow: do one step
* 0 (numpad): pause autoplay
* 1-9 (numpad): autoplay (1 is slowest, 9 is fastest)
* space: BOOSTER (play as fast as possible)

### Prerequisites

You will need SDL2

Debian
```
sudo apt-get install sdl2
```
OSX
```
brew install sdl2
```

### Compiling

```
make all
```

## Author

* **[Youva Gaudé](https://github.com/Eviber)**
