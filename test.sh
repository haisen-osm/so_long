#!/bin/bash

# Test 1: Valid map
echo -e "111111\n10CC01\n10P0E1\n111111" > test_maps/valid_map.ber
./so_long test_maps/valid_map.ber

# Test 2: Missing player
echo -e "111111\n10CC01\n1000E1\n111111" > test_maps/missing_player.ber
./so_long test_maps/missing_player.ber

# Test 3: Missing exit
echo -e "111111\n10CC01\n10P001\n111111" > test_maps/missing_exit.ber
./so_long test_maps/missing_exit.ber

# Test 4: Invalid character
echo -e "111111\n10XC01\n10P0E1\n111111" > test_maps/invalid_char.ber
./so_long test_maps/invalid_char.ber

# Test 5: Empty line
echo -e "111111\n\n10P0E1\n111111" > test_maps/empty_line.ber
./so_long test_maps/empty_line.ber

# Test 6: Not surrounded by walls
echo -e "111111\n100001\n10P0E1\n111111" > test_maps/open_border.ber
./so_long test_maps/open_border.ber

# Test 7: Unreachable collectibles
echo -e "111111\n1P0001\n1110E1\n111111" > test_maps/unreachable_collectibles.ber
./so_long test_maps/unreachable_collectibles.ber