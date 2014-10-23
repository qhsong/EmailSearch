gcc *.c -o strfind --std=c99
rm computer.time
echo "First run"
./strfind >>computer.time
echo "Second run"
./strfind >>computer.time
echo "Third run"
./strfind >>computer.time
sum=`awk '{sum+=$1}END{print sum}' computer.time`
echo `echo "scale=4;$sum/3"|bc` >>computer.time
vimdiff result.dat ~/result.dat
