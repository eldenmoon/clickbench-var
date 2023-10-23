#!/bin/bash

if [[ -n "$1" ]]; then
    file="$1"
else
    echo "input query file like queries.sql"
    exit 1
fi

TRIES=3
QUERY_NUM=1
touch result_"$file".csv
truncate -s0 result_"$file".csv

while read -r query; do
    sync
    echo 3 | sudo tee /proc/sys/vm/drop_caches >/dev/null

    echo -n "query${QUERY_NUM}," | tee -a result_"$file".csv
    for i in $(seq 1 $TRIES); do
        RES=$(mysql -vvv -h127.1 -P9030 -uroot hits -e "${query}" | perl -nle 'print $1 if /\((\d+\.\d+)+ sec\)/' || :)

        echo -n "$RES" | tee -a result_"$file".csv
        [[ "$i" != "$TRIES" ]] && echo -n "," | tee -a result_"$file".csv
    done
    echo "" | tee -a result_"$file".csv

    QUERY_NUM=$((QUERY_NUM + 1))
done < $file

