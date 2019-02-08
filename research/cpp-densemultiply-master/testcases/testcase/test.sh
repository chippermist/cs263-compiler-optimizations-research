#Compile the code
# if the file calculate exits then remove it
programname="densemultiple"
hwnum=1
input1=matrix1
input2=matrix2
output=output

# for i in `seq 1 1 3`; do
#     if [ -f ${output}${i}.txt ]; then
#         rm ${output}${i}.txt
#     fi
# done

if [ -f ${programname} ]; then
    rm ${programname}
fi
g++ -std=c++11 *.cpp -o ${programname}
# if the file densemult does not exit then exit the test
if [ ! -f ${programname} ]; then
    echo -e "\033[1;91mCompile FAILED.\033[0m"
    exit
fi
# clean
for i in `seq 1 1 9`; do
    if [ -f ${i}.out ]; then
        rm ${i}.out
    fi
    if [ -f ${i}.stderr ]; then
        rm ${i}.stderr
    fi
    if [ -f ${i}.stdcout ]; then
        rm ${i}.stdcout
    fi
    if [ -f ${i}.diff ]; then
        rm ${i}.diff
    fi
done
# For test case 1
# input 1.txt and output 1.out
timeout -k 5s 5s ./${programname} "A=${input1}1.txt;B=${input2}1.txt;C=${output}1.txt" 1>1.stdcout 2>1.stderr
# compare 1.out with 1.ans, output the difference to 1.diff
diff -iEBwu ans1.txt ${output}1.txt > 1.diff
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
# this line intentionally use different method to call the program
timeout -k 5s 5s ./${programname} A=${input1}2.txt B=${input2}2.txt C=${output}2.txt 1>1.stdcout 2>1.stderr
diff -iEBwu ans2.txt ${output}2.txt > 2.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 2    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 2    \033[1;92mPASSED.\033[0m"
    rm -f 2.diff
fi
# For test case 3
timeout -k 5s 5s ./${programname} "A=${input1}3.txt;B=${input2}3.txt;C=${output}3.txt" 1>1.stdcout 2>1.stderr
diff -iEBwu ans3.txt ${output}3.txt > 1.diff
if [ $? -ne 0 ]; then
    echo -e "Test case 3    \033[1;91mFAILED.\033[0m"
else
    echo -e "Test case 3    \033[1;92mPASSED.\033[0m"
    rm -f 3.diff
fi

