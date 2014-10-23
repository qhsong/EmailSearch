gcc *.c -o strfind
rm computer.time
echo "First run"
./strfind /home/bupt/strpool.dat /home/bupt/checkedemail.dat --use=trie >>computer.time
echo "Second run"
./strfind /home/bupt/strpool.dat /home/bupt/checkedemail.dat --use=trie >>computer.time
echo "Third run"
./strfind /home/bupt/strpool.dat /home/bupt/checkedemail.dat --use=trie >>computer.time
sum=`awk '{sum+=$1}END{print sum}' computer.time`
echo `echo "scale=4;$sum/3"|bc` >>computer.time
vimdiff result.dat ~/result.dat
