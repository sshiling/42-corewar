
corewar()
{
	start=$SECONDS

	./corewar "$1.cor" -dump $2 > a
	if [ "$(( SECONDS - start ))" -gt "3" ]
	then
		echo TIMEOUT
	else
		./vm_champs/corewar "$1.cor" -d $2  > b

		DIFF=$(diff a b)
		echo "$DIFF"
		if [ "$(cat b | tail -1 | awk '{print $1;}')" == "Contestant" ]
		then
			echo END
		fi
		rm b
	fi
	rm a
}

get_right()
{
	r=1000
	e=$(corewar "$1" "$r")
	while [ "$r" -lt "1000000" -a "$e" != "$(echo TIMEOUT)" -a "$e" == "$(echo)" ]
	do
		r=$(echo "$r * 2" | bc)
		e=$(corewar "$1" "$r")
	done
	if [ "$e" == "$(echo TIMEOUT)" ]
	then
		echo -1
	elif [ "$e" != "$(echo && echo END)" ]
	then
		echo "0 - $r" | bc | tr -d "\n"
	else
		echo $r | tr -d "\n"
	fi
}

check_right()
{
	if [ "$1" == "$(echo -1)" ]
	then
		echo "\x1b[93mTIMEOUT\x1b[0m"
	elif [ "0" -gt "$1" ]
	then
		echo "\x1b[91mError on cycle $(echo "0 - $1" | bc | tr -d "\n")\x1b[0m"
	else
		echo
	fi
}

bsearch_error()
{
	break_search=0
	has_error=0
	r=$(get_right "$1")
	l=$(echo "$r / 2" | bc)
	if [ "$(check_right "$r")" == "$(echo)" ]
	then
		while [ "$r" -ge "$l" -a "$break_search" == 0 -a "$has_error" == 0 ]
		do
			i=$(echo "($r + $l) / 2" | bc)
			e0=$(corewar "$1" "$i")

			if [ "$e0" != "$(echo TIMEOUT)" ]
			then
				e1=$(corewar "$(echo "$i+1" | bc)")

				if [ "$e0" == "$(echo)" ] && [ "$e1" != "$(echo)" ]
				then
					break_search=1
				elif [ "$e0" == "$(echo)" ]
				then
					l=$(echo "$i+1" | bc)
				else
					if [ "$e0" != "$(echo && echo END)" ]
					then
						echo "\x1b[91mError on cycle $i\x1b[0m"
						has_error=1
					fi
					r=$(echo "$i-1" | bc)
				fi
			else
				echo "\x1b[93mTIMEOUT\x1b[0m"
				has_error=1
			fi
		done
	else
		check_right "$r"
		has_error=1
	fi
	if [ "$has_error" == "0" ]
	then
		echo "\x1b[92mOK :D\x1b[0m"
	fi
}

for line in $(find . -name "*.s");
do
	champ="$(echo "$line" | rev | cut -d . -f 2- | rev | tr -d "\n")"
	./vm_champs/asm $champ.s > log
	rm log
	echo "Champion $champ: " | tr -d "\n"
	if [ ! $? -eq 0 ]
	then
		echo "\x1b[91mChampion compile error: \x1b[0m$asm"
	else
		./corewar "$champ.cor" -dump 1 > log
		if [ $? -eq 0 ]
		then
			bsearch_error "$champ"
		else
			rm log
		fi
	fi
done
