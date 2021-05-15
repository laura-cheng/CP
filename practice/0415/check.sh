g++ -std=c++14 $1 -o ac 
g++ -std=c++14 $2 -o wa
g++ -std=c++14 $3 -o gen
for i in $(seq 1 1000);
do	
	echo $i
	./gen > input
	./wa < input > out_wa
	./ac < input > out_ac
	diff out_wa out_ac || break
done
