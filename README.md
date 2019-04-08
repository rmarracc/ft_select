# ft_select
Terminal selection algorithm in C

## Installation

### Clone

- Clone this repo using `git clone https://github.com/rmarracc/ft_select`

### Build

- Simply build the program with `make` in the cloned folder

## Usage

- Execute the program with `./ft_select [options]`
Options can be files, words, folders, or whatever.
You can use `echo `\``./ft_select [options]`\` to display all the selected arguments for example.

## Known bugs

- Loops while selecting a fifo (Since open loops when you open a fifo, stat might be better to use for the colors but was forbidden in the project)
- Scrooling glitchy while putting too much arguments to fill the screen
