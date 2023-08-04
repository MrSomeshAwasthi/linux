#!/bin/bash
emp_struct(){
name=""
eid=""
phone=""
}
menu(){
	echo "menu:"
	echo "1. enter new record. "
	echo "2. delete existing record. "
	echo "3. search a record. "
	echo "4. sort record. "
	echo "5. list all record. "
	echo "6. exit. "
	echo "Enter your choice: "
}
new_rec(){
	echo "enter full name : "
	read name
	echo "enter eid : "
	read eid
	echo "enter mob no.: "
	read phone
	echo "$name | $eid | $phone">>data
}
del_rec(){
	echo "enter eid to delete: "
	read a
	#grep -v "^.*:$num:.*$" data > temp
	#mv temp data
	sed -i "/$a/d" data
}
search(){
	echo "enter eid to search"
	read a
	if grep -q "$a" data;  then
		cat data | sed -n "/$a/p"
	else
		echo "record not found"
	fi	
}
sorted(){
	sort -t ':' -k2n data > temp
	mv temp data
	cat data
}
display_all(){
	cat data
}
while true;
	do 
		menu
		read input
		case $input in 
			1)new_rec;;
			2)del_rec;;
			3)search;;
			4)sorted;;
			5)display_all;;
			6)exit;;
			*)echo "invalid input";;
		esac
	done
