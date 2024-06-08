# hjm
basic utilities for applying the heath jarrow morton model to a forward market


g++ -lgsl -lm -lgslcblas -std=c++17  -stdlib=libc++  -g main.cpp  $(find src -type f -iregex ".*\.cpp") -o a
