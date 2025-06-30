# Justify

`justify` is a small utility for justifying text.

## Usage

```sh
justify [-w WIDTH] < input.txt
```
- `-w`, `--width WIDTH`: Set the line width for justification (default: 72).
- Input is read from standard input.
- Output is written to standard output.
- Any error messages are written to standard error.

### Example

```
$ cat test.txt
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incidi
dunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercita
tion ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor i
n reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excep
teur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit 
anim id est laborum.
$ justify < test.txt
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do  eiusmod
tempor incidi dunt ut labore et dolore magna aliqua. Ut  enim  ad  minim
veniam, quis nostrud exercita tion ullamco laboris nisi ut aliquip ex ea
commodo consequat. Duis aute irure dolor i n reprehenderit in  voluptate
velit esse cillum dolore eu  fugiat  nulla  pariatur.  Excep  teur  sint
occaecat cupidatat non proident, sunt  in  culpa  qui  officia  deserunt
mollit anim id est laborum.
```

## How does it work?

Justifying text means aligning the text so both the left and right edges
of the text block are straight to create an even look. This is often used
in printed materials like books and newspapers, and sometimes in formal
documents.

`justify` achieves this by adding extra space between words or letters to
ensure that each line extends to the right margin. The last line of a
paragraph is not justified and is aligned left.

## Installation

### Homebrew (macOS)

```sh
$ brew tap eugenetriguba/homebrew-justify
$ brew install justify
```
### Manual Build

1. Clone the repository
```sh
$ git clone https://github.com/eugenetriguba/justify
$ cd justify
```

2. Create a build directory and build the project
```
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

3. Install the binary and man page (may require sudo)
```sh
$ sudo cmake --install build
```

This will:
- Install the `justify` binary to your system’s default binary directory (e.g., `/usr/local/bin`)
- Install the man page to the appropriate man directory (e.g., `/usr/local/share/man/man1`)

You can then use the `justify` CLI and view the man page via `man justify`.

