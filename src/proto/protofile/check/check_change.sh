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

ErgodicFile() {
	GetProtoFile $1
	local cnt=0
	local flag=0
	for file in "${!proto_array[@]}"
	do
		md5_file="."`echo "${proto_array[$cnt]}" | awk -F "." '{print $1}'`".md5"
		cat "check/"${md5_file} > /dev/null 2>&1
		if [ $? -eq 0 ]; then
			old_md5=`cat "check/"${md5_file}`
		else
			old_md5=""
		fi
		if [[ $old_md5 != ${proto_md5[$cnt]} ]]; then
			echo ${proto_md5[$cnt]} > "check/"${md5_file}
			((flag++))
		fi
		((cnt++))
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