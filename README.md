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

## How does it work?

Justifying text means aligning the text so both the left and right edges
of the text block are straight to create an even look. This is often used
in printed materials like books and newspapers, and sometimes in formal
documents.

`justify` achieves this by adding extra space between words or letters to
ensure that each line extends to the right margin. The last line of a
paragraph is not justified and is aligned left.
