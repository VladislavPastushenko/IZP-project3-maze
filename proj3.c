#include <stdio.h>a
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Created by Vladislav Pastushenko
// xpastu04
// 15.12.2019

typedef struct {
	int rows;
	int cols;
	unsigned char* cells;
} Map;

typedef struct {
	int stepsQuantity;
	char** steps;
} Way;





// Function "Map Constructor"
// It gets a quantity of rows and cols
// Returns Map with entered quantity of rows and cols
Map mapConstructor(int rows, int cols) {
	Map result;

	if (rows != 0 && cols != 0)
		result.cells = malloc(rows * cols * sizeof(unsigned char));


	result.rows = rows;
	result.cols = cols;

	if (result.cells == NULL)
	{
		result.rows = 0;
		result.cols = 0;
	}

	return result;
}




// Function mapCopyCell
// It gets a pointer to the Map and an array with elements (cells)
// Sets cells in the Map to the transmitted value
// 
int mapCopyCells(Map* map, unsigned char* value) {
	int size = 0;
	while (value[size] != '\0') size++;
	if (size != map->cols * map->rows) return 0;

	for (int i = 0; i < size; i++)
		map->cells[i] = value[i];

	return 1;

}





// Function "mapDestructor"
// It gets a pointer to the map
// Frees memory in map.cells
void mapDestructor(Map* map) {
	if (map->cells != NULL) {
		free(map->cells);
		map->cells = NULL;
	}
}





// Function "decToBin"
// It gets result[] that should have lenght = bit. Result is a string, that will contain decoded intiger (in char* format)
// "X" is an intiger that will be decoded.
// "Bit" is a quantity of bits 
void decToBin(char result[], int x, int bit) {
	char t[bit + 1]; memset(t, '0', bit);
	int i = 0;
	while (x != 0)
	{
		t[i++] = x % 2 + '0';
		x = x / 2;
	}

	strcpy(result, t);
}





// Function "isborder"
// It gets a pointer to the Map, number of the row, number of the coll, and number of the side of the border
// Checks that is border in transmitted place
// Parametr "border" should be integer from 0 to 2
// A left border corresponds to 0, a right border corresponds to 1, and an upper border corresponds to 2
// Returns true if there is border, else 0
bool isborder(Map* map, int r, int c, int border) {

	char temp[2];
	temp[0] = map->cells[r * map->cols + c]; temp[1] = '\0';
	int x = atoi(temp);

	char cell[4];
	decToBin(cell, x, 3);
	return cell[border] == '1';

}







// Function "start_border"
// It gets a Map, number of the row, number of the coll, and intiger "leftright", that shows rule of left (0) or right (1) hand
// Returns a border, with wich should start way int the Map. A left border corresponds to 0, a right border corresponds to 1, and an upper border corresponds to 2.
// Returns -1 if there was error.
int start_border(Map map, int row, int col, int leftright) {
	if (col == 0) {
		if (!(isborder(&map, row, col, 0))) {
			if ((row * map.cols + col) % 2 == 1) {
				if (leftright == 0) return 1;
				else if (leftright == 1) return 2;
			}
			else {
				if (leftright == 0) return 2;
				else if (leftright == 1) return 1;
			}
		}
	}


	if (col == map.cols - 1) {
		if (!(isborder(&map, row, col, 1))) {
			if ((row * map.cols + col) % 2 == 1) {
				if (leftright == 0) return 2;
				else if (leftright == 1) return 0;
			}
			else {
				if (leftright == 0) return 0;
				else if (leftright == 1) return 2;
			}
		}
	}


	if (row == 0) {
		if (!(isborder(&map, row, col, 2))) {
			if ((row * map.cols + col) % 2 == 0) {
				if (leftright == 0) return 1;
				else if (leftright == 1) return 0;
			}
		}
	}

	if (row == map.rows - 1) {
		if (!(isborder(&map, row, col, 2))) {
			if ((row * map.cols + col) % 2 == 1) {
				if (leftright == 0) return 0;
				else if (leftright == 1) return 1;
			}
		}
	}

	return -1;
}










// Function "labirinthR"
// It gets a Map, number of the row, number of the coll, and number of a border
// Goes through the Map with ***!Right!***-hands rule and prints every step (except first)
// Parametr "border" should be integer from 0 to 2
// A left border corresponds to 0, a right border corresponds to 1, and an upper border corresponds to 2.
int labirinthR(Map map, int row, int col, int border) {
	if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;

	if ((row * map.cols + col) % 2 == 1) {
		switch (border) {

		case 2:
			if (isborder(&map, row, col, 2)) border = 1;
			else {
				border = 0;
				row++;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 0:
			if (isborder(&map, row, col, 0)) border = 2;
			else {
				col--;
				border = 2;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 1:
			if (isborder(&map, row, col, 1)) border = 0;
			else {
				col++;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;
		}
	}
	else {
		switch (border) {

		case 1:
			if (isborder(&map, row, col, 1)) border = 2;
			else {
				border = 2;
				col++;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 2:
			if (isborder(&map, row, col, 2)) border = 0;
			else {
				border = 1;
				row--;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 0:
			if (isborder(&map, row, col, 0)) border = 1;
			else {
				border = 0;
				col--;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;
		}

	}

	labirinthR(map, row, col, border);
	return 1;
}





// Function "labirinthL"
// It gets a Map, number of the row, number of the coll, and number of a border
// Goes through the Map with ***!Left!***-hands rule and prints every step (except first)
// Parametr "border" should be integer from 0 to 2
// A left border corresponds to 0, a right border corresponds to 1, and an upper border corresponds to 2.
int labirinthL(Map map, int row, int col, int border) {
	if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;

	if ((row * map.cols + col) % 2 == 1) {
		switch (border) {

		case 1:
			if (isborder(&map, row, col, 1)) border = 2;
			else {
				border = 2;
				col++;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 2:
			if (isborder(&map, row, col, 2)) border = 0;
			else {
				border = 1;
				row++;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 0:
			if (isborder(&map, row, col, 0)) border = 1;
			else {
				col--;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;
		}
	}
	else {
		switch (border) {

		case 2:
			if (isborder(&map, row, col, 2)) border = 1;
			else {
				border = 0;
				row--;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 0:
			if (isborder(&map, row, col, 0)) border = 2;
			else {
				border = 2;
				col--;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;

		case 1:
			if (isborder(&map, row, col, 1)) border = 0;
			else {
				border = 1;
				col++;
				if (row > map.rows - 1 || col > map.cols - 1 || row < 0 || col < 0) return 1;
				printf("%d,%d\n", row + 1, col + 1);
			}
			break;
		}

	}

	labirinthL(map, row, col, border);
	return 1;
}




int main(int argc, char* argv[]) {

	if (argc < 2) {
		fprintf(stderr, "ERROR: too few arguments\n");
		return 1;
	}




	//
	// --help
	//
	if (strcmp(argv[1], "--help") == 0) {
		printf("\n************* Created by Vladislav Pastushenko xpastu04 *************\n"); // TO DO help
		printf("Brno University of Technology, Faculty of information technology\n");
		printf("Project 3                                               06.12.19\n\n");
		printf("Program tries to find the way through the triangle maze, and\n");
		printf("prints every step in \"col,row\\n\" format.\n\n");
		printf("CORRECT FORMAT: \n");
		printf("$ ./proj3 'flag' 'arguments'\n\n");
		printf("\"--help\": prints recommendations of using the program\n\n");
		printf("\"--test\": check if file with maze is valid\n");
		printf("CORRECT FORMAT: $ ./proj3 --test FileName\n\n");
		printf("\"--lpath\": prints the way through the maze with the left hand rule\n");
		printf("CORRECT FORMAT: $ ./proj3 --lapth row col FileName\n\n");
		printf("\"--rpath\": prints the way through the maze with the left right rule\n");
		printf("CORRECT FORMAT: $ ./proj3 --lapth row col FileName\n");


		printf("\n");
		return 0;
	}





	//
	// --test
	//
	else if (strcmp(argv[1], "--test") == 0) {
		if (argc != 3) {
			fprintf(stderr, "ERROR: invalid quantity of arguments \n");
			return 1;
		}


		// Open file
		FILE* fp;
		if ((fp = fopen(argv[2], "rb+")) == NULL) {
			fprintf(stderr, "ERROR: can't find '%s' file \n", argv[4]);
			fclose(fp);
			return 1;
		}




		// Read and control first 2 numerals from the file
		char rows[32];
		fscanf(fp, "%s", rows);
		for (unsigned c = 0; c < strlen(rows); c++) {
			if (!(rows[c] >= '0' && rows[c] <= '9')) {
				printf("Invalid\n");
				fclose(fp);
				return 1;
			}
		}

		char cols[32];
		fscanf(fp, "%s", cols);
		for (unsigned c = 0; c < strlen(cols); c++) {
			if (!(cols[c] >= '0' && cols[c] <= '9')) {
				printf("Invalid\n");
				fclose(fp);
				return 1;
			}
		}

		int r = atoi(rows);
		int c = atoi(cols);




		//Read and control all else numerals from the file
		char ch[32];

		int i;
		for (i = 0; fscanf(fp, "%s", ch) != -1; i++) {
			if (strlen(ch) > 1) {
				printf("Invalid\n");
				fclose(fp);
				return 1;
			}

			if (!(ch[0] >= '0' && ch[0] <= '7')) {
				printf("Invalid\n");
				fclose(fp);
				return 1;
			}
		}

		if (i != r * c) {
			printf("Invalid\n");
			fclose(fp);
			return 1;
		}

		printf("Valid\n");
		fclose(fp);
		return 1;
	}




	//
	// --rpath || --lpath || --shortest
	// 
	else if (strcmp(argv[1], "--rpath") == 0 || strcmp(argv[1], "--lpath") == 0 || strcmp(argv[1], "--shortest") == 0) {

		// Control quantity of arguments
		if (argc != 5) {
			fprintf(stderr, "ERROR: invalid quantity of arguments \n");
			return 1;
		}




		// Open file
		FILE* fp;
		if ((fp = fopen(argv[4], "rb+")) == NULL) {
			fprintf(stderr, "ERROR: can't find '%s' file \n", argv[4]);
			return 1;
		}




		// Read first 2 numerals from the file and create Map
		char rows[8]; fscanf(fp, "%s", rows);
		char cols[8]; fscanf(fp, "%s", cols);
		Map map = mapConstructor(atoi(rows), atoi(cols));



		// Read all else numerals from the file and set maps cells
		unsigned char* value = malloc(map.cols * map.rows * sizeof(unsigned char));
		unsigned char c[2];

		for (int i = 0; fscanf(fp, "%s", c) != -1; i++)
			value[i] = c[0];

		mapCopyCells(&map, value);
		free(value);




		// Find out border with wich we enter to the Map
		int leftright;
		if (strcmp(argv[1], "--lpath") == 0) leftright = 0;
		else leftright = 1;

		int border = start_border(map, atoi(argv[2]) - 1, atoi(argv[3]) - 1, leftright);

		if (border == -1) {
			fprintf(stderr, "ERROR: you can't enter in this cell \n");
			fclose(fp);
			mapDestructor(&map);
			return 1;
		}





		// Go through the Map and print every step
		if (strcmp(argv[1], "--rpath") == 0) {
			printf("%s,%s\n", argv[2], argv[3]);

			labirinthR(map, atoi(argv[2]) - 1, atoi(argv[3]) - 1, border);
		}
		else if (strcmp(argv[1], "--lpath") == 0) {
			printf("%s,%s\n", argv[2], argv[3]);
			labirinthL(map, atoi(argv[2]) - 1, atoi(argv[3]) - 1, border);
		}





		// Free memory
		mapDestructor(&map);
		fclose(fp);
	}






	//
	// Invalid argument
	//
	else {
		fprintf(stderr, "ERROR: invalid argument '%s'\n", argv[1]);
		return 1;
	}
}
