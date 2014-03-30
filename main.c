#include <stdio.h>
#include <string.h>
#include "mystd.h"


#define MAX_INPUT_LENGTH 256


static int check_input_data(char *input_str);


char calc_str[MAX_INPUT_LENGTH];
int buf_index;


int main(void)
{
	double res=0;
  char in_str[MAX_INPUT_LENGTH];

	while(TRUE) {
		printf("kill a program input  \"q\". \n");
		
		buf_index = 0;
		printf("input :: ");
		gets( in_str );
		
		if( strcmp(in_str, "q") == 0 ) {
			break;
		}		
		
		if( check_input_data( in_str ) == FALSE ) {
			continue;
		}

		printf("\n  calc result => %s \n\n", calc_str);
	
	}

	return 0;
}


/* スペース取り出して整形 */
void trim( char *str )
{


	if( *str != ' ' )
		{
			calc_str[buf_index++] = *str;
		}

	if(*str++) 
		{
			trim(str);
		}
}


int check_input_data(char *input_str)
{
	int i;
	int str_length = strlen(input_str);
	BOOL last_load_check;

	if( str_length >= MAX_INPUT_LENGTH ) {
		printf("\n");
		printf(" ---[ERROR] input data error. \n");
		printf(" ---[ERROR] input data size overflow!! \n\n");
		return FALSE;
	}
	
	/*  スペースを無視して、calc_str にセットする。 */
	trim(input_str);
	

	for( i=0; i < MAX_INPUT_LENGTH; i++ ) {
		if( calc_str[i] == '\0' ) {
			break;
		}
		
		switch( calc_str[i] ) {
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
		case '(':
		case ')':
			last_load_check = TRUE;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			last_load_check = FALSE;
			break;
		default:
			printf("\n");
			printf(" ---[ERROR] input data error. \n");
			printf(" ---[ERROR]  index :%d,  error data :%c \n\n",i , calc_str[i]);
			return FALSE;

		}
	}
	

	if( last_load_check == FALSE ) {
			printf("\n");
			printf(" ---[ERROR] input last data error. \n");
			printf(" ---[ERROR] not support last input '+', '-', '*', '/' \n\n");
			return FALSE;
	}

	return TRUE;
}


void read_data(void)
{

}


double calc_proc(char *input_str)
{
	return 0;
}


/*
 * Local Variables:
 * tab-width: 2
 * End:
 */
