head -n 28 libft.h > temp.h
cat *.c | grep "(" | grep -v ";" | grep -v "static" | grep -v "if" | grep -v "while" | grep -v "=" | grep -v "-" | grep -v "+" | sed 's/$/;/' >> temp.h
echo "\n#endif" >> temp.h
mv temp.h libft.h
