F1=sample.entry.test
F2=sample.search.test

touch output1 output2 output_diff

echo "===--- <COMPILING> ---==="

gcc -ansi -pedantic -W -Wall -O2 -g -o asgn asgn.c htable.c mylib.c -lm

echo -e "===--- <DONE> ---===\n\n===--- <OUTPUT (sample, asgn, diff)> ---===\n"

cat $F1 | ./sample-asgn -e &> output1

cat $F1 | ./asgn -e &> output2

diff -y output2 output1 | expand | awk 'BEGIN {FIELDWIDTHS = "60 150"} {print $2}' &> output_diff

pr -Tm output1 output2 output_diff

echo -e "\n===--- <DONE> ---===\n\n"

rm -f output1 output2 output_diff
