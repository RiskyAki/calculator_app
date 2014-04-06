#include <stdio.h>
#include <string.h>

#include "mystd.h"
#include "calc.h"

#define MAX_INPUT_LENGTH 0xFFFF


static int check_input_data( char *input_str );
static void start_init( void );


static char calc_str[MAX_INPUT_LENGTH];
static int buf_index;

static int paren_start_cnt;
static int paren_end_cnt;

int main( void )
{
	double res=0;
  char in_str[MAX_INPUT_LENGTH];

	while( TRUE ) {
		start_init();

		printf("kill a program input  \"q\". \n");
		printf("input :: ");

		gets( in_str );
		
		if( strcmp(in_str, "q") == 0 ) {
			break;
		}		
		
		if( check_input_data( in_str ) == FALSE ) {
			continue;
		}

		get_RPN( calc_str );

		printf("\n  calc result => %lf \n\n", result_buf[0]);
	
	}

	return 0;
}


/* スペース取り出して整形 */
void trim( char *str )
{
	if( *str != ' ' ) {
		calc_str[buf_index++] = *str;
	}

	if(*str++) {
		trim(str);
	}
}


int check_input_data( char *input_str )
{
	int i;
	int str_length = strlen(input_str);
	Bool last_load_check;

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
			last_load_check = TRUE;
			break;
		case '(':
			paren_start_cnt++;
			last_load_check = TRUE;
			break;
		case ')':
			paren_end_cnt++;
			last_load_check = TRUE;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '.':
			if( last_load_check != TRUE) {
				printf("\n");
				printf(" ---[ERROR] input last data error. \n");
				printf(" ---[ERROR] Please do not put in a sign continuously. \n\n");
				return FALSE;
			}
			else {
				last_load_check = FALSE;
			}

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
	
	if( paren_start_cnt != paren_end_cnt ) {
		printf("\n");
		printf(" ---[ERROR] input last data error. \n");
		printf(" ---[ERROR] Please check consistency of a parenthesis. \n\n");
		return FALSE;
	}

	return TRUE;
}


void start_init( void )
{
		buf_index       = 0;
		paren_start_cnt = 0;
		paren_end_cnt   = 0;
}


/*
 * Local Variables:
 * tab-width: 2
 * End:
 */
