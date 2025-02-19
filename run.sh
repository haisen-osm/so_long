#!/bin/bash

# Test 1: Valid map
echo -e "111111\n10CC01\n10P0E1\n111111" > test_maps/test_map1.ber
./so_long test_maps/test_map1.ber

# Test 2: Missing player
echo -e "111111\n10CC01\n1000E1\n111111" > test_maps/test_map2.ber
./so_long test_maps/test_map2.ber

# Test 3: Missing exit
echo -e test_maps/"111111\n10CC01\n10P001\n111111" > test_maps/test_map3.ber
./so_long test_map3.ber

# Test 4: Invalid character
echo -e "111111\n10XC01\n10P0E1\n111111" > test_maps/test_map4.ber
./so_long test_maps/test_map4.ber

# Add more tests as needed...