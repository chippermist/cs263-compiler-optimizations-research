#Compile the code
# if the file densemult exits then remove it
if [ -f densemult ]; then
    rm densemult
fi
g++ -std=c++11 *.cpp -o densemult
# if the file densemult does not exit then exit the test
if [ ! -f densemult ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
rm *.out *.stderr *.stdcout
# For test case 1
# input 1.txt and output 1.out
./densemult "A=1.txt;B=1.txt;C=1.out" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu 1.ans 1.out > 1.diff
# if diff returns nothing, it means you pass the test case (Your ourput file 1.out is correct)
if [ $? -ne 0 ]; then
    # display "test case 1 FAILED" to the screen. The word "FAILED" is highlighted in Red color
    echo -e "Test case 1    \033[1;91mFAILED.\033[0m"
else
    # display "test case 1 PASSED" to the screen. The word "PASSED" is highlighted in Green color
    echo -e "Test case 1    \033[1;92mPASSED.\033[0m"
    # remove the file 1.diff
    rm -f 1.diff
fi
# For test case 2
./densemult "A=2.txt;B=2.txt;C=2.out" 1>2.stdcout 2>2.stderr
diff -iEBwu 2.ans 2.out > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
# For test case 3
./densemult "A=3.txt;B=3.txt;C=3.out" 1>3.stdcout 2>3.stderr
diff -iEBwu 3.ans 3.out > 3.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi

