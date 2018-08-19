
corewar_v()
{
	./corewar "$1.cor" -v $2 > my
	./vm_champs/corewar "$1.cor" -v $2 > src
	diff my src
	rm my src
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
			if [ "$(corewar_v "$champ" 31)" == "$(echo)" ]
			then
				echo "\x1b[92mOK :D\x1b[0m"
			else
				echo "\x1b[91mKO :(\x1b[0m"
			fi
		else
			rm log
		fi
	fi
done