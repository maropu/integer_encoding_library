#!/bin/bash

# Executable file
COMPRESS='vcompress'

# Maximum ID to test
MAXID=17

# Defined suffix
SUFFIX='.vc'

# Length to test
L='256 1024 4096 16384 65536 262144 1048576 4194304'

# Mapping from name to ID
declare -A M

M=([0]='n-gamma' [1]='fu-gamma' [2]='f-gamma'   \
   [3]='n-delta' [4]='fu-delta' [5]='fg-delta'  \
   [6]='f-delta' [7]='vbyte' [8]='binypl'       \
   [9]='simple9' [10]='simple16' [11]='p4delta' \
   [12]='optp4delta' [13]='vseblocks ' [14]='vse-r' \
   [15]='vsereset' [16]='vsehybrid' [17]='vsesimple')

# Validate inputs
if [ $# != 1 ]; then
  echo -e "Exception: irregal arguments"
  exit 1
fi

if [ ! -x ./$COMPRESS ]; then
  echo -e "Exception: $COMPRESS not existed"
  exit 1
fi

if [ ! -f $1 ]; then
  echo -e "Exception: $1 not existed"
  exit 1
fi

# Output headers
echo 'Variable Length Benchmarks:'
echo '/* --- Show Performance(mis) --- */'

echo -en '\t'
for len in $L; do
  echo -en '\t'
  echo -en $len
done

echo -en '\n'
echo '=========================='

# Run tests, output results
for impl in $(seq 0 $MAXID); do
  # Show a type of coders to test
  echo -n "${M[$impl]}   "

  for len in $L; do
    # Compress lists, and warm-up
    ./$COMPRESS $impl -n $len $1 > /dev/null || exit 1
    ./$COMPRESS -d $1$SUFFIX > /dev/null || exit 1

    # Do benchmarking
    ./$COMPRESS -d $1$SUFFIX > temp.output || exit 1
    echo -en '\t'
    sed -n 's/  Performance: \(.*\)mis$/\1/p' < temp.output | xargs echo -n
  done
  echo -en '\n'
done

echo -en '\n'

# Remove
rm -rf temp.output
rm -rf $1.*

