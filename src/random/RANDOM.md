# Random
This directory contains some popular random functions. I recommend you using `splitmix64` initialized with `random_seedFromTime` for fast rng, hoshiro128plus for more accurate 32-bit rng and hoshiro256plus for 64-bit.


## Xoshiro/Xoroshiro RNG algorithms
There are a bunch of versions of xoshiro/xoroshiro algorithms, which are created by [David Blackman and Sebastiano Vigna](https://prng.di.unimi.it/)

```
xoroshiro
├── 32bitValue
|   ├── xoroshiro64star.c
|   └── xoroshiro64starstar.c
└── 64bitValue
    ├── xoroshiro128plus.c
    ├── xoroshiro128plusplus.c
    └── xoroshiro128starstar.c

xoshiro
├── 32bitValue
│   ├── xoshiro128plus.c
│   ├── xoshiro128plusplus.c
│   └── xoshiro128starstar.c
└── 64bitValue
    ├── xoshiro256plus.c
    ├── xoshiro256plusplus.c
    └── xoshiro256starstar.c
```
