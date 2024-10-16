# Grammar

'''
stmt : expr 
		| assn
assn : IDEN ASSN expr	
expr : expr PLUS term
expr : expr MINUS term
expr : term
term : term TIMES fact
		| term DIV fact
term : fact
fact : LPAREN expr RPAREN
fact : NUMBER
fact : IDEN
IDEN : LETTER
'''
