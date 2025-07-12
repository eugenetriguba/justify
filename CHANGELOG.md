# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## 0.1.1 - 2025-06-12

### Fixed

- When a word was too long for the line buffer, it'd wrap to the next line
  but it was missing a character. So 'abc123' with a line length of 3 was
  resulting in 'abc\n23'.

- When `-h` is used to show the usage information, the program was giving
  back an exit code of 1 to indicate an error. It now gives back an exit
  code of 0.

- When `-w` was used with a value <= 0, the program would crash or do nothing.
  Now, an exit code of 1 is given back because any value for `-w` is expected
  to be positive.

## [0.1.0] - 2025-06-30

- Initial Release

