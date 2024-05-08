# To create the file use:
# for i in 1K 1M 10M 100M 1G 10G; do fallocate -l $i file-$i.img; done

FILES="file-1K.img file-1M.img file-10M.img file-100M.img file-1G.img file-10G.img"
IP=<ip>

function runbench {
for i in $FILES
do echo "$i"
	#TEST="./clientw $IP 8080 $i"
	TEST="./client-sf $IP 8080 $i"
    perf stat -e context-switches -a $TEST
	#perf stat -C 2,3 -a -e cycles:uk $TEST
	sleep 5
    sync
	echo ""
done
}
runbench
