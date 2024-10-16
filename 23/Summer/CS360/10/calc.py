#!/usr/bin/python3
#
#  stmt : expr 
#  expr : expr PLUS term
#  expr : expr MINUS term
#  expr : term
#  term : term TIMES fact
#       | term DIV fact
#  term : fact
#  fact : LPAREN expr RPAREN
#  fact : NUMBER
#


from sys import stdin, stdout, stderr, argv


######   LEXER   ###############################
# Note:  This is precisely the same lexer that exp1 uses.  Could've pulled
# it out to a different file.

from ply import lex

	# this takes the place of the enum, in C.  These are your token types.
tokens = (
	'PLUS',
	'MINUS',
	'TIMES',
	'DIV',
	'EXP',
	'LPAREN',
	'RPAREN',
	'NUMBER',
)

# Now, this section.  We have a mapping, REs to token types (please note
# the t_ prefix).  They simply return the type.

	# t_ignore is special, and does just what it says.  Spaces and tabs
t_ignore = ' \t'

t_PLUS		= r'\+'
t_MINUS   = r'-'
t_TIMES		= r'\*'
t_DIV     = r'/'
t_EXP		= r'\^'
t_LPAREN	= r'\('
t_RPAREN	= r'\)'

	# for tokens that require an action, we actually define functions (again,
	# note the prefixes) and put the pattern (RE) in the doc string for the
	# function.  Nearly magic

def t_NUMBER( t ) :
	r'[0-9]+'

		# t.value holds the string that matched.  Dynamic typing - no unions
	t.value = int( t.value )
	return t

	# These are standard little ditties:
def t_newline( t ):
  r'\n+'
  t.lexer.lineno += len( t.value )

  # Error handling rule
def t_error( t ):
  print( f"Illegal character {t.value[0]} on line {t.lexer.lineno}" )
  t.lexer.lineno += 1
  return t
  #t.lexer.skip( 1 )

  # Here is where we build the lexer, after defining it (above)
lex.lex()

#-----   LEXER (end)   -------------------------------


#-----   YACC   -------------------------------------

import ply.yacc as yacc

	# This is not needed in this example, since 'stmt' is the first rule encountered
start = 'stmt'

	# create a function for each production (note the prefix)
	# The rule is given in the doc string

def p_stmt( p ) :
	'stmt : expr'
	p[0] = p[1]

def p_add( p ) :
	'expr : expr PLUS term'
	p[0] = p[1] + p[3]

def p_sub( p ) :
	'expr : expr MINUS term'
	p[0] = p[1] - p[3]

def p_expr_term( p ) :
	'expr : term'
	p[0] = p[1]

	# or, we can combine similar rules
def p_mult_div( p ) :
	'''term : term TIMES expo 
	        | term DIV expo'''
	if p[2] == '*' :
		p[0] = p[1] * p[3]
	else :
		if p[3] == 0 :
			return p_error( p )
		p[0] = p[1] / p[3]

def p_term_expo( p ):
	'term : expo'
	p[0] = p[1]

def p_expo( p ):
	'expo : fact EXP expo'
	p[0] = p[1]

def p_expo_fact( p ):
	'expo : fact'
	p[0] = p[1]

def p_fact_expr( p ) :
	'fact : LPAREN expr RPAREN'
	p[0] = p[2]

def p_fact_NUM( p ) :
	'fact : NUMBER'
	p[0] = p[1]

# Error rule for syntax errors
def p_error( p ):
	print( "Syntax error in input!" )

	# now, build the parser
yacc.yacc()


#-----   MAIN   -------------------------------------

def main( arg=argv ) :

		# Now, this lexer actually takes a string; it doesn't (that I yet know)
		# read from a file.  So, you can read the file as you like, and feed it
		# to the parser.
	
		# we'll read from stdin
	if stdin.isatty() :
		prompt = '> '
	else :
		prompt = ''
	stdout.write( prompt )
	stdout.flush()
	s = stdin.readline()
	t = s.strip()

	while s and t not in ( 'quit', 'q', '.', 'bye' ) :
		try :
			result = yacc.parse( s )
			print( result )
		except Exception :
			pass
		try :
			stdout.write( prompt )
			stdout.flush()
			s = stdin.readline()
		except EOFError :
			print( "" )
			break
		t = s.strip()


if __name__ == '__main__' :
	main()

