#!/bin/bash

echo Testing has started!
echo 
echo "Recency friendly access pattern tests:"
for file in tests/recency_friendly_access_pattern/*.in; do
    echo $file
    ./bin/main < $file
    echo 
done

echo "Thrashing access pattern tests:"
for file in tests/thrashing_access_pattern/*.in; do
    echo $file
    ./bin/main < $file
    echo 
done

echo "Mixed access pattern(1) tests:"
for file in tests/mixed_access1_pattern/*.in; do
    echo $file
    ./bin/main < $file
    echo 
done

echo "Mixed access pattern(2) tests:"
for file in tests/mixed_access2_pattern/*.in; do
    echo $file
    ./bin/main < $file
    echo 
done


echo "Other tests"
for file in tests/other_tests/*.in; do
    echo $file
    ./bin/main < $file
    echo 
done

#bash ./tests/bash.sh