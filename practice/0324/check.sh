g++ -std=c++14 $1 -o ac
g++ -std=c++14 $2 -o wa
g++ -std=c++14 $3 -o gen
for i in $(seq 1 10000);
do 
	./gen > input
	./ac < input > out_ac
	./wa < input > out_wa
	diff out_ac out_wa || break
done

