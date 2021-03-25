#!/bin/fish

set -l Gtk3  (string split -n -- " " (pkg-config --cflags --libs gtk+-3.0))
set -l None  "\e[0m"
set -l Bold  "\e[1m"
set -l Green "\e[1;32m"

for Src in *.c
  set -l Name (basename -s .c $Src)

  printf "$Bold > Building$None: $Name ..."
  gcc $Src -o $Name $Gtk3
  printf "$Green Done!$None\n"
end