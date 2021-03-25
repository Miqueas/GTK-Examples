set -l None "\e[0m"
set -l Bold "\e[1m"

for Src in *.c
  set -l Name (basename -s .c $Src)
  rm $Name
  printf "$Bold > Deleted$None: $Name\n"
end