#!/bin/sh

# ================ Check if required argument was passed or not =====================
check_argument()
{
for i in "$@"
 do
   case "$i" in
     --no-mem) return 0 # 0 = true
	       ;;
   esac
done
return 1 # 1 = false
}
# ===================================================================================
# Output filename
out_file="a.out"
# ===================================================================================

# Log compile process
echo "[CPP RUNNER]: Compiling $1..."

# Compile the file
g++ -Wall -pedantic -std=c++17 -o "$out_file" $1

# Exit if above process didn't suceeded properly
if [ $? -ne 0 ]; then exit 1; fi

# Log running process
echo "[CPP RUNNER]: Running $1..."

if check_argument "$@"; then
  echo "[CPP RUNNER]: Opted no memory leak checks"
  ./$out_file
  exit 0
fi

# Check if valgrind exists
if command -v valgrind >/dev/null 2>&1; then
  valgrind ./$out_file
else
  echo "[CPP RUNNER]: Failed to find valgrind... skipping memory checks"
  ./$out_file
fi
