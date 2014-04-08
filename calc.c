#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mystd.h"


typedef enum {
  START_PAREN,
  PLUS_OR_MINUS,
  TIMES_OR_DIVID,
  END_PAREN,
} priority_type;


#define RES_BUF_SIZE 0xFFFF
#define STACK_BUF_SIZE 0xFF

double result_buf[RES_BUF_SIZE];

static int result_index;
static int temp_val_index;
static Bool is_last_load_char;

char   stack_buf[STACK_BUF_SIZE];
char   temp_val[STACK_BUF_SIZE];

static void calc_init( void );
static void pop_stack( int *sp, char input_char );
static double calc( double a, double b, char ch );


priority_type check_priority( char str )
{

  priority_type ret = PLUS_OR_MINUS;

  switch( str ) {
  case '+':
  case '-':
    ret = PLUS_OR_MINUS;
    break;
  case '*':
  case '/':
    ret = TIMES_OR_DIVID;
    break;
  default:
    break;
  }  

  return ret;
}


int check_number( char str )
{
  int ret = TRUE;

  switch( str ) {
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
  case '.':
    temp_val[temp_val_index] = str;
    temp_val_index++;

    is_last_load_char = FALSE;
    ret = TRUE;
    break;
  case '(':
    ret = FALSE;
    break;
  case ')':
  default:

    /* ")" の後に来る演算子の場合は、値を追加したくない。 */
    if( is_last_load_char != TRUE ) {
      result_buf[result_index] = atof( &temp_val[0] );

#ifdef DEBUG_MODE
      printf(" [debug_number] double == %lf, index : %d \n", result_buf[result_index], result_index);
#endif

      result_index++;
    }
    else {
      is_last_load_char = FALSE;
    }

    /* temp 領域を初期化 */
    memset( &temp_val[0], 0, temp_val_index);
    temp_val_index = 0;

    ret = FALSE;
    break;
  }

  return ret;
  
}



void get_RPN ( char *input )
{
  int length = strlen( input );
  int i=0;
  int sp=0;

  calc_init();

  for( i = 0; i < length; i++  ) {
    if( check_number( input[i] ) == FALSE ) {

      if( input[i] == ')' ){
	/* 最初の括弧まで計算。 */
	pop_stack( &sp, input[i] );
      }
      else if( input[i] == '(' ){
	stack_buf[sp++] = input[i];
      }
      else{
	if( sp == 0 ){
	  stack_buf[sp++] = input[i];
	}
	else{
	  priority_type cur_sign   =  check_priority( input[i] );
	  priority_type stack_sign =  check_priority( stack_buf[sp-1] );

	  /* 演算子の優先度を確認 */
	  /* "*", "/" の場合は、スタックに追加 */
	  if( cur_sign >= stack_sign ){
	    stack_buf[sp++] = input[i];
	  }
	  else{
	    pop_stack( &sp, input[i] );
	    stack_buf[sp++] = input[i];
	  }
	}
      }
    }
  }


  /* 最終の文字が ')' でなければ、数値の変換が必要。 */
  if( input[ length-1 ] != ')' ){
    result_buf[result_index++] = atof( &temp_val[0] );
  }

  pop_stack( &sp, 0 );

  return;
}


void pop_stack( int *sp, char input_char )
{
  double a;
  double b;

  (*sp)--;
  result_index--;

  while( *sp >= 0) {
    if (stack_buf[*sp] == '(') {
      is_last_load_char = TRUE;
      
      /* ")" じゃなかったら、"(" を残しておく必要がある。 */
      if( input_char != ')') {
	(*sp)++;
      }
#ifdef DEBUG_MODE
      printf(" [debug_stack] ::::: pop break : %c \n", stack_buf[*sp]);
#endif
      break;
    }


    a = result_buf[result_index--];
    b = result_buf[result_index];   
    
    result_buf[result_index]   = calc( a, b, stack_buf[*sp] );
    result_buf[result_index+1] = 0;

#ifdef DEBUG_MODE
    printf(" [debug_stack] res_index = %d, %lf \n",result_index ,result_buf[result_index]);    
#endif

    (*sp)--;
  }

  if( *sp < 0 ) {
    *sp = 0;
  }
  
  result_index++;
}


double calc( double a, double b, char ch )
{

  double result;

#ifdef DEBUG_MODE
  printf(" [debug calc] %lf, %lf, %c \n", a, b, ch);
#endif

  switch( ch ) {
  case '+':
    result = b + a;
    break;
  case '-':
    result = b - a;
    break;
  case '*':
    result = b * a;
    break;
  case '/':
    result = b / a;
    break;
  default:
    break;
  }  

  return result;
}



void calc_init( void )
{
  result_index      = 0;
  temp_val_index    = 0;
  is_last_load_char = FALSE;

  memset(result_buf, 0, RES_BUF_SIZE );
  memset(stack_buf,  0, STACK_BUF_SIZE );
  memset(temp_val,   0, STACK_BUF_SIZE );
}

/*
 * Local Variables:
 * tab-width: 2
 * End:
 */
