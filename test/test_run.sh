#!/bin/bash

# Coder type implemented
I="n-gamma fu-gamma f-gamma n-delta fu-delta \
        fg-delta f-delta vbyte simple9 simple16 \
        p4delta optp4delta vseblocks vser vserest \
        vsehybrid vsesimple-v1 vsesimple-v2"

# Mapper from name to ID
declare -A M
M=(["n-gamma"]=0 ["fu-gamma"]=1 ["f-gamma"]=2 ["n-delta"]=3 \
        ["fu-delta"]=4 ["fg-delta"]=5 ["f-delta"]=6 ["vbyte"]=7 \
        ["binypl"]=8 ["simple9"]=9 ["simple16"]=10 ["p4delta"]=11 \
        ["optp4delta"]=12 ["vseblocks"]=13 ["vser"]=14 ["vserest"]=15 \
        ["vsehybrid"]=16 ["vsesimple-v1"]=17 ["vsesimple-v2"]=18)

if [ ! -x ./decbench ]; then
        echo 'Exception: decbench not existed'
        exit 1
fi

# Output headers
echo "Coder Benchmarks:"
echo "/* --- Show Performance(mis)/Ccompression(bps) --- */"

echo -e "mis\t\tbps"
echo '=========================='

# Run tests, output table
for impl in $I; do
        ./decbench ${M[$impl]} ./test/.test.dat > temp.output || exit 1
        sed -n 's/^Performance: \(.*\) mis$/\1/p' < temp.output | xargs echo -n
        echo -en '\t\t'
        sed -n 's/^Ratio: \(.*\) %$/\1/p' < temp.output | xargs echo -n
        echo -en '\t\t'
	echo -n '-- '
	echo $impl
done

echo -en '\n'

# Remove
rm -rf temp.output

