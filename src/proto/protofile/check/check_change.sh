#!/bin/bash
GetProtoFile() {
    local cnt=0
    cd $1

    for file in `ls *.proto`
    do
        proto_array[$cnt]="$file"
        proto_md5[$cnt]=`md5sum -b $file | awk '{print $1}'|sed 's/ //g'`
        ((cnt++))
    done
}

AddProtoCmd() {
    echo "execute_process(COMMAND rm -rf inc/${1}.pb.h src/${1}.pb.cc WORKING_DIRECTORY \${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/)" >> ../compile_proto.cmake
    echo "execute_process(COMMAND build/bin/protoc --proto_path=src/proto/protofile/ --cpp_out=src/proto/src/ ${1}.proto WORKING_DIRECTORY \${CMAKE_CURRENT_SOURCE_DIR}/../../../../)" >> ../compile_proto.cmake
    echo "execute_process(COMMAND mv src/${1}.pb.h inc WORKING_DIRECTORY \${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/proto/)" >> ../compile_proto.cmake
}

ErgodicFile() {
    GetProtoFile $1
    local flag=0
    if [ ! -d  ../inc ]; then 
        mkdir ../inc 
    fi 
    if [ ! -d ../src ]; then 
        mkdir ../src 
    fi
    echo "" > ../compile_proto.cmake

    for file in "${!proto_array[@]}"
    do
        md5_file="."`echo "${proto_array[$file]}" | awk -F "." '{print $1}'`".md5"
        cat "check/"${md5_file} > /dev/null 2>&1
        if [ $? -eq 0 ]; then
            old_md5=`cat "check/"${md5_file}`
        else
            old_md5=""
        fi
        if [[ $old_md5 != ${proto_md5[$file]} ]]; then
            echo ${proto_md5[$file]} > "check/"${md5_file}
            file_prefix=`echo "${proto_array[$file]}" | awk -F "." '{print $1}'`
            AddProtoCmd $file_prefix
            ((flag++))
        fi
    done
    echo $flag
}

CompileProto() {
    flag=$(ErgodicFile $3)
    if [[ ${flag} != "0" ]]; then
        rm $1 $2 > /dev/null 2>&1
    fi
}

CompileProto $1 $2 $3