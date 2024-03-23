# RRIP caching algorithm
## About 
RRIP is a new replacement policy, which prevents cache blocks with a distant re-reference interval (i.e., scan blocks) from evicting blocks that have a near-immediate re-reference interval (i.e., non-scan blocks). RRIP accomplishes this by requiring an 2-bit register per cache block to store its Rereference Prediction Value (RRPV). We propose Static RRIP (SRRIP) that is scan-resistant.

In this project, we utilized information from the article "High Performance Cache Replacement Using
Re-Reference Interval Prediction (RRIP)" by Aamer Jaleel, Kevin B. Theobald, Simon C. Steely Jr., Joel Emer. For more details, refer to [the article available](/doc/2010.06.isca.rrip.pdf).

We also have a [presentation](/doc/presa.pdf) with a detailed description of the project.

## How to build
```bash
git clone https://github.com/Aliyaminim/RRIP-cpp.git
cd RRIP-CPP
cmake -S ./ -B build/
cd build/
cmake --build .
```

## How to run the program
```bash
./rrip/rrip < [file]
```

## How to test the program
```bash
cd ../test
bash testing.sh
```
