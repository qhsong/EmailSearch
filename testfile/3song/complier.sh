sum=`awk '{sum+=$1}END{print sum}' computer.time`
echo `echo "scale=4;$sum/3"|bc` >>computer.time
vimdiff result.dat ~/result.dat
