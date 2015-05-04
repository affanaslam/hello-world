import sys,re,os
from pathlib import Path

class JackTokenizer(object):
    '''Removes all comments and white space from the input stream and
    breaks it into Jack-language tokens, as specified by the Jack
    grammar.'''
    
    def __init__(self,inputFile):
        '''Constructor - Opens inputFile and gets ready to tokenize it.'''
        infile = open(inputFile, 'r')
        self._data = infile.read()
        self.tok = self.tokens(self._data)
        self.current = ''
        self.keyList = ['class','method','function','constructor','int','boolean','char','void','var','static','field','let','do','if','else','while','return','true','false','null','this']
        self.symList = ['{','}','(',')','[',']','.',',',';','+','-','*','/','&','|','<','>','=','~']
        

    
    def hasMoreTokens(self):

        return self.tok != []

        
        '''JT.hasMoreTokens() -> bool

        Returns True if there are more tokens left, False otherwise.'''
        
    
    def advance(self):

        if self.hasMoreTokens():
            self.current = self.tok.pop(0)
        '''JT.advance() -> None

        Gets the next token from the input and makes it the current
        token. Should only be called if hasmoreTokens() is
        True. Initially there is no current token
        '''

        
    
    def tokenType(self, current_token = None):
        if current_token == None:current_token = self.current 
        if current_token in self.keyList: return 'KEYWORD'
        elif re.match (re.compile(r'\d+'), current_token): return 'INT_CONST'
        elif re.match (re.compile(r'[\w\-]+'), current_token): return 'IDENTIFIER'
        elif current_token in self.symList: return 'SYMBOL'
        elif re.match(re.compile(r'"[^"\n]*"'),current_token):return 'STRING_CONST'

    
        
        '''JT.tokenType() -> str

        Returns the type of the current token which is one of:
        KEYWORD
        SYMBOL
        IDENTIFIER
        INT_CONST
        STRING_CONST
        '''
        pass
    
    def keyWord(self):

        if self.tokenType() == 'KEYWORD' : return self.current
        '''JT.keyWord() -> str

        Returns the keyword which is the current token. Should be
        called only when tokentype() is KEYWORD. Return value is one of:
        CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT,
        BOOLEAN, CHAR, VOID, VAR, STATIC, 'FIELD, LET,
        DO, IF, ELSE, WHILE, RETURN, TRUE, FALSE,
        NULL, THIS
        '''
        
    
    def symbol(self):

        if self.tokenType() == 'SYMBOL' : return self.current
        '''JT.symbol() -> str

        Returns the character which is the current token. Should be
        called only when tokentype() is SYMBOL.
        '''
        
    
    def identifier(self):

        if self.tokenType() == 'IDENTIFIER' : return self.current
        '''JT.identifier() -> str

        Returns the identifier which is the current token. Should be
        called only when tokenType() is IDENTIFIER.
        '''
        
    
    def intVal(self):

        if self.tokenType() == 'INT_CONST' : return self.current
        '''JT.intVal() -> int

        Returns the integer value of the current token. Should be
        called only when tokenType() is INT_CONST.
        '''
        
    
    def stringVal(self):

        if self.tokenType() == 'STRING_CONST' : return self.current[1:][:-2]
        '''JT.stringVal() -> str

        Returns the string value of the current token, without double
        quotes. Should be called only when TokenType() is
        STRING_CONST.
        '''
        
    def remove_comments(self,string):
        pattern = r"(\".*?\"|\'.*?\')|(/\*.*?\*/|//[^\r\n]*$)"
        regex = re.compile(pattern, re.MULTILINE|re.DOTALL)
        def _replacer(match):
            if match.group(2) is not None:
                return "" 
            else: 
                return match.group(1)
        return regex.sub(_replacer, string)


    def tokens(self,string):
        data = self.remove_comments(string)
        pattern = re.compile('class|method|function|constructor|int|boolean|char|void|var|static|field|let|do|if|else|while|return|true|false|null|this|[\\{\\}\\(\\)\\[\\]\\.\\,\\;\\+\\-\\*\\/\\&\\|\\<\\>\\=\\~]|\\d+|"[^"\\n]*"|[\w\-]+')
        return re.findall(pattern, data)
    

    
        
 
    
class CompilationEngine(object):
    '''Effects the actual compilation output. Gets its input from a
    JackTokenizer and emits its parsed structure into an output file.
    
    '''


    def __init__(self,inputFile,outputFile):

            
        '''Constructor - Creates a new compilation engine with inputFile and
        outputFile. The next method called must be compileClass().
        '''

        self._outfile = open(outputFile+'.xml', 'w')
        self.tok = inputFile
        self.in_counter = 1
        
        self.key = {'IDENTIFIER':'identifier', 'STRING_CONST':'stringConstant', 'INT_CONST':'integerConstant', 'SYMBOL':'symbol', 'KEYWORD':'keyword'}
        self.sym = {'<':'&lt;','>':'&gt;','"':'&quot;','&':'&amp;'}
        self.exp_sym = ['+','=','-','*','/','&','|','~','<','>']


        
    
    def compileClass(self):

        self.write_outfile('<class>')
        self.in_scope()
        self.write_tok(['class'])
        self.write_tok(['IDENTIFIER'])
        self.write_tok(['{'])
        while self.do_compileClassVarDec():
            print( self.do_compileClassVarDec())
            self.compileClassVarDec()
        while self.do_compileSubroutine():
            print( self.do_compileClassVarDec())
            self.compileSubroutine()
        self.write_tok(['}'])
        self.out_scope()
        self.write_outfile('</class>')
        self.close_outfile()
        
        

        


    def do_compileClassVarDec(self):
        
        return self.upcoming_tok()[0] in ('static','field')

    def do_compileSubroutine(self):
        return self.upcoming_tok()[0] in ('function','constructor','method')
    
    def compileClassVarDec(self):
        
        '''CE.compileClassVarDec() -> None
        
        Compiles a static declaration or a field declaration.
        '''
        self.write_outfile('<classVarDec>')
        self.in_scope()
        self.write_tok(['field','static'])
        self.write_tok(['KEYWORD','IDENTIFIER'])#optional
        self.write_tok(['IDENTIFIER'])
        while self.upcoming_tok()[0] != ';':
            self.write_tok(',')    
            self.write_tok(['IDENTIFIER'])
        self.write_tok([';'])
        self.out_scope()
        self.write_outfile('</classVarDec>')


        

    def compileSubroutine(self):
        '''CE.compileSubroutine() -> None

        Compiles a complete method, function, or constructor.
        '''
        self.write_outfile('<subroutineDec>')
        self.in_scope()
    

        self.write_tok(['constructor','function','method'])
        self.write_tok(['KEYWORD','IDENTIFIER'])
        self.write_tok(['IDENTIFIER'])
        self.write_tok(['('])
        self.compileParameterList()
        self.write_tok([')'])
        self.write_outfile('<subroutineBody>')
        self.in_scope()
        self.write_tok(['{'])
        while self.upcoming_tok()[0] == 'var':
            self.compileVarDec()
        self.compileStatements()
        self.write_tok(['}'])
        self.out_scope()
        self.write_outfile('</subroutineBody>')

        self.out_scope()
        self.write_outfile('</subroutineDec>')   
    
    def compileParameterList(self):
        '''CE.compileParameterList() -> None

        Compiles a (possible empty) parameter list not including the
        enclosing "()".
        '''
        #the first 'var' before comma is written to the file because 'one' (bool) is False
        #so the loop ignores the 'one' condition and goes to else, it sets the one variable
        #to True then having validated whether the next is keyword or identifier, writes either of them
        #then writes the final idenifier; next time because one is True, it writes the comma until
        #the loop reaches the closing bracket
        self.write_outfile('<parameterList>')
        self.in_scope()
        one = False 

        while self.upcoming_tok()[0] != ')':
            if one:
                self.write_tok([','])
            else:
                one = True
            self.write_tok(['KEYWORD','IDENTIFIER'])
            self.write_tok(['IDENTIFIER'])

        self.out_scope()
        self.write_outfile('</parameterList>')

    def compileVarDec(self):
        '''CE.compileVarDec() -> None

        Compiles a var declaration.
        '''
        self.write_outfile('<varDec>')
        self.in_scope()
        self.write_tok(['var'])
        self.write_tok(['KEYWORD','IDENTIFIER']) #optional
        self.write_tok(['IDENTIFIER'])
        while self.upcoming_tok()[0] != ';':
            self.write_tok([','])    
            self.write_tok(['IDENTIFIER'])
        self.write_tok([';'])
        self.out_scope()
        self.write_outfile('</varDec>')
        

        

    def compileStatements(self):
        '''CE.compileStatements() -> None

        Compiles a sequence of statement not including the enclosing "{}".
        '''
        tok = self.upcoming_tok()[0]
        self.write_outfile('<statements>')
        self.in_scope()
        while tok != '}':
            self.exception(['do','let','while','return','if'])
            if tok == 'do':
                self.compileDo()
            elif tok == 'let':  
                self.compileLet()
            elif tok == 'while':
                self.compileWhile()
            elif tok == 'return':
                self.compileReturn()
            elif tok == 'if':
                self.compileIf()
            tok = self.upcoming_tok()[0]              
        self.out_scope()
        self.write_outfile('</statements>') 

    def compileDo(self):
        '''CE.compileDo() -> None

        Compiles a do statement.
        '''
        self.write_outfile('<doStatement>')
        self.in_scope()

        self.write_tok(['do'])
        self.write_tok(['IDENTIFIER'])
        if self.upcoming_tok()[0] == '.':
            self.write_tok()
            self.write_tok(['IDENTIFIER'])
        self.write_tok(['('])
        self.compileExpressionList()
        self.write_tok([')'])
        self.write_tok([';'])

        self.out_scope()
        self.write_outfile('</doStatement>')
        

    def compileLet(self):
        '''CE.compileLet() -> None

        Compiles a let statement.

        
        '''

        self.write_outfile('<letStatement>')
        self.in_scope()            

        self.write_tok(['let'])
        self.write_tok(['IDENTIFIER'])
        if self.upcoming_tok()[0] == '[':
            self.write_tok()
            self.compileExpression()
            self.write_tok([']'])
        self.write_tok(['='])
        self.compileExpression()
        self.write_tok([';'])
        self.out_scope()
        self.write_outfile('</letStatement>')

    def compileWhile(self):
        '''CE.compileWhile() -> None

        Compiles a while statement.
        '''
        self.write_outfile('<whileStatement>')
        self.in_scope()
        self.write_tok(['while'])
        self.write_tok(['('])
        self.compileExpression()
        self.write_tok([')'])
        self.write_tok(['{'])
        self.compileStatements()
        self.write_tok(['}'])            
        self.out_scope()
        self.write_outfile('</whileStatement>')
    
    def compileReturn(self):
        '''CE.compileReturn() -> None

        Compiles a return statement.
        '''
        self.write_outfile('<returnStatement>')
        self.in_scope()
        self.write_tok(['return'])
        if self.upcoming_tok()[0] != ';':
            self.compileExpression()
        self.write_tok([';'])
        self.out_scope()
        self.write_outfile('</returnStatement>')
    
    def compileIf(self):
        '''CE.compileIf() -> None

        Compiles an if statement possibly with a trailing else clause.
        '''
        self.write_outfile('<ifStatement>')
        self.in_scope()

        self.write_tok(['if'])
        self.write_tok(['('])
        self.compileExpression()
        self.write_tok([')'])
        self.write_tok(['{'])
        self.compileStatements()
        self.write_tok(['}'])
        if self.upcoming_tok()[0] == 'else':
            self.write_tok()
            self.write_tok(['{'])
            self.compileStatements()
            self.write_tok(['}'])        

        self.out_scope()
        self.write_outfile('</ifStatement>')
    
    def compileExpression(self):
        '''CE.compileExpression() -> None
        
        Compiles an expression.
        '''
        self.write_outfile('<expression>')
        self.in_scope()
        self.compileTerm()
        while self.upcoming_tok()[0] in self.exp_sym:         
            self.write_tok()
            self.compileTerm()
        self.out_scope()
        self.write_outfile('</expression>')
        

    def compileTerm(self):
        '''CE.compileTerm() -> None

        Compiles a term. Uses lookahead to decide between alternative
        parsing rules. If the current token is an indentifier, a
        look=ahead token of "[", "(", or "." distinguish between a
        variable, array, and subroutine call. Any other token is not
        part of this term and should not be advanced over.
        '''
        self.write_outfile('<term>')
        self.in_scope()       
        self.dis_var_array_sub()
        self.out_scope()
        self.write_outfile('</term>')



    def dis_var_array_sub(self):
        tok, tok_type = self.upcoming_tok()
        if tok_type in ('KEYWORD', 'INT_CONST', 'STRING_CONST'):
            self.write_tok()
        elif tok_type == 'SYMBOL':
            if tok == '(':
                self.write_tok()
                self.compileExpression()
                self.write_tok(')')
            else:
                self.write_tok(['~','-'])
                self.compileTerm()
        elif tok_type == 'IDENTIFIER':
            self.write_tok()
            tok = self.upcoming_tok()[0]
            if tok == '[':
                self.write_tok()
                self.compileExpression()
                self.write_tok([']'])
            elif tok == '(':
                self.write_tok()
                self.compileExpressionList()
                self.write_tok([')']) 
            elif tok == '.':       
                self.write_tok()
                self.write_tok('IDENTIFIER')
                self.write_tok(['('])
                self.compileExpressionList()
                self.write_tok([')'])
                
    
        
        

    def compileExpressionList(self):
        '''CE.compileExpressionList() -> None

        Compiles a (possibly empty) comma separated list of expressions.
        '''
        self.write_outfile('<expressionList>')
        self.in_scope()        
        f = False

        while self.upcoming_tok()[0] != ')':
            if f:
                self.write_tok([','])
            else:
                f = True
            self.compileExpression()

        self.out_scope()
        self.write_outfile('</expressionList>')

    def token(self):
        
        self.tok.advance() #advances if it has more tokens
        tok_type = self.tok.tokenType()

        if tok_type == 'KEYWORD': return (self.tok.keyWord(), self.key[tok_type])
        elif tok_type == 'IDENTIFIER': return (self.tok.identifier(), self.key[tok_type] )
        elif tok_type == 'INT_CONST': return (self.tok.intVal(),self.key[tok_type])
        elif tok_type == 'STRING_CONST': return ( self.tok.stringVal() ,self.key[tok_type])
        elif tok_type == 'SYMBOL': return (self.tok.symbol(), self.key[tok_type] )


    def exception(self,string):

        
        t = ''
        tok, tok_type = self.upcoming_tok()
##        print(tok, tok_type)

        try:
            

            for i in string:        
                if tok != i or tok_type != i:
                    t = t + i

            return ('Unexpected token:' + tok + ' ' + tok_type + ',Expected:' + t)

        except:

            print (Exception)
            
        



    def upcoming_tok(self):

        try:
            
    
            return self.tok.tok[0], self.tok.tokenType(self.tok.tok[0])

        except:

            return '0'

        
    

    def write_tok(self, val= None):
        if val != None: self.exception(val)
        tok, tok_type = self.token()
        if tok in ['<','>','"','&']: tok = self.sym[tok]
        self.write_outfile('<'+ str(tok_type) +'> ' + str(tok) +' </'+tok_type+'>')    
        

        

    def in_scope (self):
        '''
        the in_scope() func increments the counter in order to father the next tag -or
        to write the next (child) tag within the scope of the previous tag     
        '''
        self.in_counter = self.in_counter + 1 

    def out_scope (self):

        self.in_counter = self.in_counter - 1

        
    def indentation(self):

        return ('  ' * self.in_counter)

    def write_outfile(self,data):
 
        
        self._outfile.write(self.indentation() + data + '\n')

    def close_outfile(self):

        self._outfile.close()

    

def printUsage():
    '''printUsage() -> None
    
    Prints infomration on how to invoke this program.
    '''
    print("Usage: {} dir".format(sys.argv[0]))
    print("dir is the program directory - it contains the .jack file(s) to be compiled.")

def getFileNames():
    '''getFileNames() -> list

    Returns a list containing the names of the Jack files in the given
    directory name. Prints help and exits this program gracefully if
    the program is invoked incorrectly.
    '''
    if len(sys.argv) != 2:
        printUsage()
        print('Invalid call:', str(sys.argv).translate(str.maketrans('','',"',[]")))
        sys.exit()
    p = Path(sys.argv[1])
    if not p.is_dir():
        printUsage()
        print('{} is not a directory'.format(p))
        sys.exit()
    jackFiles = list(p.glob('*.jack'))
    jackFiles = [str(f) for f in jackFiles]
    return jackFiles

def main():
    '''Compiles the Jack program in the directory whose name is supplied
    through the command line when invoking this program.
    '''
    jackFiles = getFileNames()
    vmFiles = [s.replace('.jack','.vm') for s in jackFiles]

        
    



    
    # jackFiles contains the names of the Jack files to be compiled.
    # vmFiles contains the names of the corresponding vm files to be written to.
    

if __name__ == '__main__':
    '''Leave as is.'''
    main()
