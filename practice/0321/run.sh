g++ -std=c++14 $1 -o t
g++ -std=c++14 $2 -o gen
for i in $(seq 1 100);
do 
	echo $i
	./gen > input
	./t < input > out_t
done
