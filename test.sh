pid=`ps -C strsearch|grep -v 'PID'|awk '{print $1}'`
if [ ! -z $pid ] 
then
	mem=`ps -o vsz -p $pid|grep -v VSZ`
	echo $mem
else 
	echo "Not running the strfind"
fi
