#include <stdio.h>
#include <string.h>

#include "mystd.h"
#include "calc.h"

#define MAX_INPUT_LENGTH 0xFFFF

/* 外部変数 */
static char calc_str[MAX_INPUT_LENGTH];
static int buf_index;

static int paren_start_cnt;
static int paren_end_cnt;


/* 関数 */
static int check_input_data( char *input_str );
static void start_init( void );



int main( void )
{
	double res = 0;
  char  in_str[MAX_INPUT_LENGTH];

	while( TRUE ) {
		start_init();

		printf("kill a program input  \"q\". \n");
		printf("input :: ");

		/* fgets でとると、最後の文字に改行コードが入るのでそれを削除 */
		fgets( in_str, MAX_INPUT_LENGTH, stdin);
    in_str[ strlen(in_str) - 1 ] = '\0';


		if( strcmp(in_str, "q") == 0 ) {
			break;
		}		
		
		if( check_input_data( in_str ) == FALSE ) {
			continue;
		}

		get_RPN( calc_str );

		printf("\n  calc result => %lf \n\n", result_buf[0]);
	
		/* 標準入力を捨てる */
		fflush(stdin);
	}

	return 0;
}


/* スペース取り出して整形 */
void trim( char *str )
{
	if( *str != ' ' ) {
		calc_str[buf_index++] = *str;
	}

	if( *str++ != '\0' ) {
		trim(str);
	}
}


/* 入力データの妥当性チェック */
int check_input_data( char *input_str )
{
	int i;
	int str_length = strlen(input_str);
	Bool last_load_check;


	/* 入力なしの場合 */
	if( str_length == 0 ) {
		printf(" ---[ERROR] Please input expression \n\n");
		return FALSE;
	}

	/* バッファ以上の入力の場合 */
	if( str_length >= MAX_INPUT_LENGTH ) {
		printf(" ---[ERROR] input data error. \n");
		printf(" ---[ERROR] input data size overflow!! \n\n");
		return FALSE;
	}
	
	
	/*  スペースを無視して、calc_str にセットする。 */
	trim(input_str);


	/* 数式の妥当性評価 */
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
			/* "(" の前が演算子でなければエラー */
			if( last_load_check != FALSE) {
				printf("\n");
				printf(" ---[ERROR] input data error. \n");
				printf(" ---[ERROR] Please input number before start paren . \n\n");
				return FALSE;
			}

			paren_start_cnt++;
			last_load_check = TRUE;
			break;
		case ')':
			
			if( paren_start_cnt == 0 ){
				printf("\n");
				printf(" ---[ERROR] input data error. \n");
				printf(" ---[ERROR] Please check consistency of a parenthesis. \n\n");
				return FALSE;
			}
			else {
				paren_start_cnt--;
			}
			
			if( last_load_check != TRUE) {
				printf("\n");
				printf(" ---[ERROR] input data error. \n");
				printf(" ---[ERROR] Please do not put in a sign continuously. \n\n");
				return FALSE;
			}
			else {
				last_load_check = TRUE;
			}
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '.':
		 
			/* "1++2*5" みたいなのを検知 */
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
			/* 入力対象外データがきたとき  */
			printf("\n");
			printf(" ---[ERROR] input data error. \n");
			printf(" ---[ERROR]  index :%d,  error data :%c \n\n",i , calc_str[i]);
			return FALSE;

		}
	}
	
	/* 最終文字が数字 or 括弧でない場合はエラー */
	if( last_load_check == FALSE ) {
			printf("\n");
			printf(" ---[ERROR] input last data error. \n");
			printf(" ---[ERROR] not support last input '+', '-', '*', '/' \n\n");
			return FALSE;
	}
	
	/* 括弧の整合性がとれてない場合はエラー */
	if( paren_start_cnt != paren_end_cnt ) {
		printf("\n");
		printf(" ---[ERROR] input data error. \n");
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
