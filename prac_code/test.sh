#!/bin/bash

echo "start test"

for i in {0..50}
do
	echo "echo test $i"
	expect -f expect_client.exp $i
done
