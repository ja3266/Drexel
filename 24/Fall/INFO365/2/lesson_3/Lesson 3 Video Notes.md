- PLSQL - Programming Language SQL. Its a little different than traditional sql.

## Syntax

DECLARE
	<variables>  -- declaring variables like standard conding languages
BEGIN
	<code> 
INSERT INTO TEST_TABLE (CONTENT) VALUES ('one'); -- Inserting variables into the database
EXCEPTION
	WHEN <exception_type> THEN -- error handling for null values, 0s, etc. 
		<code>
...
END;

