#!/bin/bash
subtasks=( "G1" "G2" "G3" "Arrays" "BooleanExpressions" "CallingMethodsOfClass(withInherit)" "CastFunctions" "Class(Simple)" "ConcatArraysAndStringsAndCompareString" "ConditionalStatements" "FloatExpressions" "Functions" "GlobalVariables" "Inheritance" "IntegerExpressions" "Interface" "LoopStatements" "ReadAndWrite" "SemanticError(type1)" "SemanticError(type2)" "SemanticError(type3)" "SemanticError(type4)" "SemanticError(type5)" "StringExpressions" )
scores=( 10 20 30 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 10 )
mkdir -p out
mkdir -p report
cd ./tests
prefix="" ;
score=0;
dirlist=(`ls`) ;
OUTPUT_DIRECTORY="out/"
TEST_DIRECTORY="tests/"
REPORT_DIRECTORY="report/"

cd ../src

make clean
make

cd ..

for folder in ${dirlist[*]};
do
	NUMBER_OF_PASSED=0
	NUMBER_OF_FAILED=0
	echo "Subtask $folder -------------------------------------"
	cd ./out
	mkdir -p $folder
	cd ../report
	mkdir -p $folder
	cd ..
	cd ./tests
	cd $folder	
	testlist=(`ls ${prefix}*.d`);
	cd ../../
	for filelist in ${testlist[*]};
	do
		filename=`echo $filelist | cut -d'.' -f1`;
		output_filename="$filename.out"
		output_asm="$filename.s"
		program_input="$filename.in"
		report_filename="$filename.report.txt"
		echo "Running Test $filename -------------------------------------"
		if [[ $? -eq 1 ]]; then
			echo "Bison Parse Error!"
		else
			./main -i "$folder/$filelist" -o "$folder/$output_asm"
			if [ $? -eq 0 ]; then
				echo "MIPS Generated Successfuly!"
					timeout 2 spim -a -f "$OUTPUT_DIRECTORY$folder/$output_asm" < "$TEST_DIRECTORY$folder/$program_input" > "$OUTPUT_DIRECTORY$folder/$output_filename"
				if [ $? -eq 0 ]; then
					echo "Code Executed Successfuly!"
					if command -v python3; then
						python3 comp.py -a "$OUTPUT_DIRECTORY$folder/$output_filename" -b "$TEST_DIRECTORY$folder/$output_filename" -o "$REPORT_DIRECTORY$folder/$report_filename"
					else
							python comp.py -a "$OUTPUT_DIRECTORY$folder/$output_filename" -b "$TEST_DIRECTORY$folder/$output_filename" -o "$REPORT_DIRECTORY$folder/$report_filename"
					fi
					if [[ $? = 0 ]]; then
						((NUMBER_OF_PASSED++))
						echo "++++ test passed"
					else
						((NUMBER_OF_FAILED++))
						echo "---- test failed !"
						echo
					fi 
				else
						echo "Code did not execute successfuly!"
					((NUMBER_OF_FAILED++))
				fi
			fi
		fi
	done

	echo "Passed : $NUMBER_OF_PASSED"
	echo "Failed : $NUMBER_OF_FAILED"
	
	echo "Subtask score: "
	len=${#subtasks[@]}
	for (( i=0; i<$len; i++ ))
	do
		if [[ "${subtasks[$i]}" == "$folder" ]]; then
			subtask_score=$(( $NUMBER_OF_PASSED/($NUMBER_OF_PASSED + $NUMBER_OF_FAILED) * ${scores[$i]} ));
			echo $subtask_score;
			(( score+= $NUMBER_OF_PASSED/($NUMBER_OF_PASSED + $NUMBER_OF_FAILED) * ${scores[$i]} ));
		fi
	done
	
	
	echo "Subtask $folder done ------------------------------"
	echo $'\n\n'
	
	
done

echo "Final score: "
echo "$score"
