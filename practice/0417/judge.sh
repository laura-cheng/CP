path=$1
tot=$2
g++ -std=c++14 $3 -o code

for i in $(seq 1 "$tot");
do 
	in=$path$i".in"
	out=$path$i".out"
	echo $in
	echo $out
	./code < "$in" > code_out
	diff code_out "$out" || break 
done
