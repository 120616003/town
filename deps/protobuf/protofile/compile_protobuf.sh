#!/bin/bash
cd $1
for file in `ls ../protofile/*.proto`
do
    ./protocb --proto_path=../protofile/ --cpp_out=../protofile/ $file
done