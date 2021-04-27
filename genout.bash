# make clean
projectName="./Project04"
# rm encounter.o inventory.o $projectName
make clean
make


valgrind  --leak-check=full --log-file="m_valgrind_1.txt" $projectName input_1.txt > output_1.txt
valgrind  --leak-check=full --log-file="m_valgrind_2.txt" $projectName input_2.txt > output_2.txt
valgrind  --leak-check=full --log-file="m_valgrind_3.txt" $projectName input_3.txt > output_3.txt
valgrind  --leak-check=full --log-file="m_valgrind_4.txt" $projectName input_4.txt > output_4.txt
valgrind  --leak-check=full --log-file="m_valgrind_5.txt" $projectName input_5.txt > output_5.txt

# ./Project02 input_1.txt > output_1.txt
# ./Project02 input_2.txt > output_2.txt
# ./Project02 input_3.txt > output_3.txt
# ./Project02 input_4.txt > output_4.txt
# ./Project02 input_5.txt > output_5.txt