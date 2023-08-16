#Challenge: Illustrating Advanced Shell Scripting
#Design an interactive shell script that serves as an Employee Record Management System. This system should encompass key employee details: their Name, Employee Number, and Telephone Number.
#The script's capabilities should encompass the ability to seamlessly create records, delete records, effortlessly retrieve and showcase specific employee details, efficiently sort the records, and comprehensively present the entire employee record collection.

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
	echo "$name|$eid|$phone">>data
}
del_rec(){
	echo "enter eid to delete: "
	read a
	grep -v  "|$a|" data > temp
	mv temp data
}
search(){
	echo "enter eid to search"
	read a
	grep "|$a|" data || echo "no record found "	
}
sorted(){
	sort -t '|' -k 1 data > temp
	mv temp data
	cat data
}
display_all(){
	echo " "
	echo "Displaying all data ..."
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
