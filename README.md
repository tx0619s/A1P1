Author: Xiaocheng Zhang/Tian Xia
Date: 1/24/2020
Assignment: A1 PART 1

Description:
This code could be seperated into four parts: 1) reading command flags 
2) reading sor file 3) detect data type 4) output answers.

In part one & part two, We created Hashmap Class to store command flags
and data value. They are called command_map and data_map. The command_map stores 
flags' name as key and flags' value as value. The data_map stores row's index as 
key and the list of fields in that row as value. Each field has been filtered 
out empty space and invalid fields will be REPLACED BY "<>". We don't ignore 
anything during reading file. You can find the code of reading command in helper1.h 
and the code of reading file in helper1.h and helper2.h 

In part three, we get the longest row in data_map and detect data type for each 
column. We use 1 as STRING, 2 as FLOAT, 3 as INT, 4 as BOOL, 5 as MISSING VALUE. 
Thus, you may see those representation in column_type string list. You can find 
the code of identifying data type in helper3.h

Having stored and identified all relevant information, we can simply output the answer. 
You can find the code of this part in main.cpp

