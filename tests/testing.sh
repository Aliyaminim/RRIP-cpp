#!/bin/bash

echo Testing has started!
echo 
echo "Recency friendly access pattern tests:"
for file in recency_friendly_access_pattern/*.in; do
    echo $file
    ../build/rrip/rrip < $file
    ../build/ideal_cache/ideal_cache < $file
    echo 
done

echo "Thrashing access pattern tests:"
for file in thrashing_access_pattern/*.in; do
    echo $file
    ../build/rrip/rrip < $file
    ../build/ideal_cache/ideal_cache < $file
    echo 
done

echo "Mixed access pattern tests:"
for file in mixed_access_pattern/*.in; do
    echo $file
    ../build/rrip/rrip < $file
    ../build/ideal_cache/ideal_cache < $file
    echo 
done

echo "Other tests"
for file in other_tests/*.in; do
    echo $file
    ../build/rrip/rrip < $file
    ../build/ideal_cache/ideal_cache < $file
    echo 
done



