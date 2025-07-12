#!/usr/bin/env bats

load 'vendor/bats-support/load'
load 'vendor/bats-assert/load'
load 'vendor/bats-file/load'

JUSTIFY_BIN="./build/justify"

@test "last line of the output is left aligned" {
  run "${JUSTIFY_BIN}" <<EOF
This is a test of the emergency broadcast system.
EOF
  assert_success
  assert_output "This is a test of the emergency broadcast system."
}

@test "lines are justified to both margins except last line" {
  run "${JUSTIFY_BIN}" <<EOF
Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt
EOF
  assert_success
  expected_output="Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do  eiusmod
tempor incididunt"
  assert_output "$expected_output"
}

@test "lines are justified to both margins except last line with custom line width" {
  run "${JUSTIFY_BIN}" -w 30 <<EOF
This is a test of the emergency broadcast system.
EOF
  assert_success
  expected_output="This  is   a   test   of   the
emergency broadcast system."
  assert_output "$expected_output"
}

@test "words are not split if they fit" {
  run "${JUSTIFY_BIN}" -w 60 <<EOF
Hello world
EOF
  assert_success
  assert_output "Hello world"
}

# Test word wrapping for words longer than buffer
@test "word longer than buffer is wrapped" {
  run "${JUSTIFY_BIN}" -w 60 <<EOF
123456789012345678901234567890123456789012345678901234567890EXTRA
EOF
  assert_success
  expected_output="123456789012345678901234567890123456789012345678901234567890
EXTRA"
  assert_output "$expected_output"
}

@test "very long word is wrapped across multiple lines" {
  run "${JUSTIFY_BIN}" -w 20 <<EOF
verylongwordthatdoesnotfitinasinglelineandshouldbesplitacrossmultiplelines
EOF
  assert_success
  expected_output="verylongwordthatdoes
notfitinasinglelinea
ndshouldbesplitacros
smultiplelines"
  assert_output "$expected_output"
}

@test "long word mixed with normal words preserves spacing" {
  run "${JUSTIFY_BIN}" -w 60 <<EOF
Hello 123456789012345678901234567890123456789012345678901234567890EXTRA world
EOF
  assert_success
  expected_output="Hello 123456789012345678901234567890123456789012345678901234
567890EXTRA world"
  assert_output "$expected_output"
}

@test "multiple spaces in input are collapsed when on last left-aligned line" {
  run "${JUSTIFY_BIN}" <<EOF
This    is     spaced
EOF
  assert_success
  assert_output --partial "This is spaced"
}

@test "empty input produces no output" {
  run "${JUSTIFY_BIN}" <<EOF

EOF
  assert_success
  assert_output ""
}
