#!/bin/bash

# Coder-type to test (coder-type: EncoderName, DecoderName)
#       n-gamma: Gamma, N Gamma
#       fu-gamma: Gamma, FU Gamma
#       f-gamma: Gamma, F Gamma
#       n-delta: Delta, N Delta 
#       fu-delta: Delta, FU Delta 
#       fg-delta: Delta, FG Delta 
#       f-delta: Delta, F Delta 
#       varbyte: Variable Byte, Variable Byte
#       biny-intpltv: Binary Intepolative, Binary Interpolative
#       simple9: Simple 9, Simple 9
#       simple16: Simple 16, Simple 16
#       p4delta: PForDelta, PForDelta
#       optp4delta: OPTPForDelta, OPTPForDelta
#       vseblocks: VSEncodingBlocks, VSEncodingBlocks
#       vse-r: VSE-R, VSE-R
#       vserest: VSEncodingRest, VSEncodingRest
#       vsehybrid: VSEncodingBlocksHybrid, VSEncodingBlocksHybrid
#       vsesimple-v1: VSEncodingSimpleV1, VSEncodingSimpleV2
#       vsesimple-v2: VSEncodingSimpleV1, VSEncodingSimpleV2
I="n-gamma n-delta varbyte simple9 simple16 p4delta optp4delta vseblocks vse-r vserest vsehybrid vsesimple-v1 vsesimple-v2"

if [ ! -x ./decbench ]; then
        echo 'Exception: decbench not existed'
        exit 1
fi

# Output headers
echo "Coder Benchmarks:"
echo "/* --- Show Performance(mis)/Ccompression(bps) --- */"
echo 

echo -e "mis\t\tbps"
echo '=========================='

# Run tests, output table
for impl in $I; do
        ./decbench $impl ./test/.test.dat > temp.output || exit 1
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

