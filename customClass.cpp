#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// custom String class using C

typedef struct yString
{
	uint8_t* data;		// string - unsigned 8-bit int (1 byte per 1 character in the string)
	uint8_t length;		// length of the string
	uint8_t howMuch;	// how much memory is needed
}str_t;

str_t* stringCreate(uint8_t length)						// creating string in memory
{
	str_t* string = (str_t*)malloc(sizeof(str_t));		// take the memory
	string->data = (uint8_t*)malloc(length);			// fill the data
	string->howMuch = 0;
	return string;
} 


void stringFree(str_t* string)				// delete the sting and clean the memory
{
	free(string->data);
	free(string);
}


uint8_t stringLength(str_t* string)		// get the sting length
{
	return string->length;
}


void printString(str_t* string, FILE* file)		// print string into the file
{
	fwrite(string->data, sizeof(uint8_t), string->length, file);
}


str_t* stringDup(const char* str)				// duplicate string
{
	str_t* string = stringCreate((uint8_t)strlen(str));
	memcpy(string->data, str, string->length);
	string->howMuch = string->length;
	return string;
}


size_t stringLength(const char* string)		// custom version of strlen()
{
	size_t length = 0;
	
	while(*string != '\0'){
		length++;
		string++;
	}
	
	return length;
}


str_t* stringConcat(str_t* left, str_t* right)		// concatenation
{
	str_t* string = stringCreate(left->length + right->length);
	memcpy(string->data, left->data, left->length);
	memcpy(string->data + left->length, right->data, right->length);
	string->howMuch = string->length;
	return string;

}


int main(int argc, char** argv)
{
	str_t* helloWorld = stringDup("hello, world");
	printString(helloWorld, stdout);
	
	fprintf(stdout, "\n length = \n  %d", stringLength(helloWorld));
	
	str_t* concated = stringConcat(helloWorld, helloWorld);
	printString(concated, stdout);
	
	stringFree(concated);
	stringFree(helloWorld);
	
	return 0;
}