for line in $(find . -name "*.s");
do

champ="$(echo "$line" | rev | cut -d . -f 2- | rev | tr -d "\n")"
rm -f a
rm -f b
rm -f "$champ.cor"

 ./asm "$champ.s" > c
if [ -f "$champ.cor" ]
	then
		our="1"
		cp "$champ.cor" a
	else
		our="0"
fi

rm -f "$champ.cor"
./vm_champs/asm "$champ.s" > d
if [ -f "$champ.cor" ]
	then
		their="1"
		cp "$champ.cor" b
	else
		their="0"
fi

if ([ "$our" = "0" ] && [ "$their" = "1" ])
	then
 		DIFF=$(diff a b)
fi
rm -f a
rm -f b
rm -f c
rm -f d

if ([ "$DIFF" = "$(echo)" ] && [ "$our" = "$their" ])
	then
		echo "$champ: \x1b[92mOK :D\x1b[0m"
	else
		echo "$champ: \x1b[91mKO :(\x1b[0m"
fi
done