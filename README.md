# RRIP-cpp
Project name: RRIP-cache

Contributors: Minimullina Aliya

To install and run the code, follow these steps: 
1. git clone https://github.com/Aliyaminim/RRIP-cpp.git
2. cd RRIP-CPP
3. bash start.sh
4. cd tests
5. bash testing.sh

RRIP is a new replacement policy, which prevents cache blocks with a distant re-reference interval (i.e., scan blocks) from evicting blocks that have a near-immediate re-reference interval (i.e., non-scan blocks). RRIP accomplishes this by requiring an 2-bit register per cache block to store its Rereference Prediction Value (RRPV). We propose Static RRIP (SRRIP) that is scan-resistant.
