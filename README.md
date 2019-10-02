# Extream simple test result

* for numTest = 10'000'000
* element type - MetalInputDesc

1. std::unordered_map & MurmurHashFn
2. tsl::robin_map & MurmurHashFn
3. tsl::robin_map & Cityhash

## 50 element sample group

1. 3511 44999955 
2. 3410 44999955
3. 3291 44999955

## 5000 element sample

1. 3853 26744257786
2. 3634 26744257786
3. 3481 26744257786