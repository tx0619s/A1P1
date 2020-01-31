N := sorer

all: clean $(N) test

$(N):
	g++ -o $(N) -g -std=c++11 main.cpp

clean:
	rm -f $(N)

test:
	./$(N) -f "data.sor" -from 0 -len 100 -print_col_type 0
	./$(N) -f "data.sor" -from 0 -len 100 -print_col_type 2
	./$(N) -f "data.sor" -from 0 -len 100 -is_missing_idx 2 0
	./$(N) -f "data.sor" -from 0 -len 100 -is_missing_idx 2 1
	./$(N) -f "data.sor" -from 0 -len 100 -is_missing_idx 2 2
	./$(N) -f "data.sor" -from 0 -len 100 -print_col_idx 2 0
	./$(N) -f "data.sor" -from 5 -len 100 -print_col_idx 1 0
	./$(N) -f "data.sor" -from 0 -len 100 -print_col_idx 2 3
	./$(N) -f "data.sor" -from 0 -len 100 -print_col_idx 1 3
