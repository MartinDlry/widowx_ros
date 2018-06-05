#pass AX12.py path as first argument to the script
FILE='servos_registers.py'
sed '/#/d' $1 > $FILE # removing all comments
sed -i '/AX_/d' $FILE # removing all lines with "AX_"
sed -i '/^$/d' $FILE # removing all empty lines
sed -i '/_H =/d' $FILE # removing all lines with "_H ="
sed -i 's/^P_/\"/g' $FILE # replacing all "P_" at line beginning with """
sed -i 's/=/= [/g' $FILE # replacing "=" with "= ["
sed -i '/_L =/ s/$/ , 2 ]/' $FILE # adding " , 2 ]" at the end of lines that contains "_L ="
sed -i 's/_L =/ =/g' $FILE # removing all "_L" before "="
sed -i '/]/! s/$/ , 1 ]/' $FILE # adding " , 1 ]" at the end of lines that don't contains "]"
sed -i 's/ =/" :/g' $FILE  # replacing all " =" with "" : "
sed -i 's/$/ ,/g' $FILE
sed -i '$ s/,$//g' $FILE
sed -i '1 s/^/registersDict = {\n/' $FILE
sed -i '$ s/$/\n}/' $FILE

