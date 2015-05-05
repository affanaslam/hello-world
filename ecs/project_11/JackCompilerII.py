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
        self.math = {'&':'AND', '|':'OR', '+': 'ADD', '-': 'SUB', '=': 'EQ', '>': 'GT', '<': 'LT'}

    
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


    def __init__(self, vmwriter ,tokenizer):

      
        self.tok = tokenizer
        self.vmwriter = vmwriter
        self.symbol = SymbolTable()
        self.w_counter = 0
        self.i_counter = 0
        self.key = {'IDENTIFIER':'identifier', 'STRING_CONST':'stringConstant', 'INT_CONST':'integerConstant', 'SYMBOL':'symbol', 'KEYWORD':'keyword'}
        self.sym = {'<':'&lt;','>':'&gt;','"':'&quot;','&':'&amp;'}
        self.exp_sym = ['+','=','-','*','/','&','|','~','<','>']
    

        
    
    def compileClass(self):

      self.write_tok()
      self.name_class = self.write_tok()
      self.write_tok()
      while self.do_compileClassVarDec():
        self.compileClassVarDec()
      while self.do_compileClassVarDec():
        self.compileClassVarDec()
      self.vmwriter.close()
        

    def do_compileClassVarDec(self):
        
        return self.upcoming_tok()[0] in ('static','field')

    def do_compileSubroutine(self):
        return self.upcoming_tok()[0] in ('function','constructor','method')
    
    def compileClassVarDec(self):

      kind = self.write_tok().upper() #handle this in the SymbolTalbe()
      type = self.write_tok()
      name = self.write_tok()

      self.symbol.define(name, type , kind)

      while self.upcoming_tok()[0] != ';':
        self.write_tok()
        name = self.write_tok()
        self.symbol.define(name,type , kind)

      self.write_tok()
  
        

    def compileSubroutine(self):

      kind = self.write_tok()
      arg_kind = 'ARG'
      self.write_tok()
      nameSub = self.write_tok()
      self.symbol.startSubroutine()
      if kind == 'constructor':
        number_of_fields = self.symbol.varCount('FIELD')
        self.vmwriter.writePush('CONST', number_of_fields)
        self.vmwriter.writeCall('Memory.alloc',1)
        self.vmwriter.writePop('POINTER', 0)
      elif kind == 'method':
        self.vmwriter.writePush('ARG', 0)
        self.vmwriter.writePop('POINTER', 0)
        self.symbol.define('instance', self.name_class, arg_kind)
      self.write_tok()
      self.compileParameterList()
      self.write_tok()
      self.write_tok()
      while self.upcoming_tok()[0] == 'var':
        self.compileVarDec()
      number_of_local_vars = self.symbol.varCount('VAR')
      name_of_function = self.name_class + '.' + nameSub
      self.vmwriter.writeFunction(name_of_function, number_of_local_vars)
      
  
    
    def compileParameterList(self):


      if upcoming_tok()[0] != ')':

        kind = 'ARG'
        type = self.write_tok()
        name = self.write_tok()
        self.symbol.define(name, type, kind)

      while upcoming_tok()[0] != ')':
        kind = 'VAR'
        self.write_tok()
        type = self.write_tok()
        name = self.write_tok()
        self.symbol.define(name, type, kind)
      
 

    def compileVarDec(self):
      kind = 'VAR'

      self.write_tok()
      type = self.write_tok()
      name = self.write_tok()

      self.symbol.define(name, type, kind)

      while upcoming_tok()[0] != ';':
        self.write_tok()
        name = self.write_tok()
        self.symbol.define(name, type, kind)
      self.write_tok()        

    def compileStatements(self):
        
        
        while self.upcoming_tok()[0] in ['do','let','while','return','if']:

          tok = self.write_tok()
          
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
        

    def compileDo(self):
        '''CE.compileDo() -> None

        Compiles a do statement.
        '''
   

        

    def compileLet(self):
        '''CE.compileLet() -> None

        Compiles a let statement.

        
        '''



    def compileWhile(self):
        '''CE.compileWhile() -> None

        Compiles a while statement.
        '''

    
    def compileReturn(self):
        
        constant = 'CONST'
        
        if self.upcoming_tok()[0] == ';':
          
          
          self.compileExpression()

        else:

          self.vmwriter.writePush(constant, 0)

        self.vmwriter.writeReturn()
        self.write_tok()

    
    def compileIf(self):

      ifTrue = 'IF_TRUE' + self.i_counter + '\n'
      ifFalse = 'IF_FALSE' + self.i_counter + '\n'
      ifEnd = 'IF_END' + self.i_counter + '\n'
      self.i_counter = self.i_counter + 1
      self.write_tok()
      self.compileExpression()   
      self.write_tok()    
      self.write_tok()
      self.vmwriter.writeIf(ifTrue)
      self.vmwriter.writeGoto(ifFalse)
      self.vmwriter.writeLabel(ifTrue)
      self.compileStatements() 
      self.vmwriter.writeGoto(ifEnd)
      self.write_tok() 

      self.vm_writer.writeLabel(ifFalse)

      if self.upcoming_tok()[0] == 'else': 
        self.write_tok() 
        self.write_tok() 
        self.compileStatements()
        self.write_tok()

      self.vmwriter.writeLabel(ifEnd)

      
    def compileExpression(self):
      
     self.compileTerm() 

     while upcoming_tok()[0] in self.exp_sym  :
       sym = self.write_tok()
       self.compileTerm() 

     if sym in self.exp_sym:
       
      self.vmwriter.writeArithmetic(self.math[sym])

     elif sym == '/':
      self.vmwriter.writeCall('Math.divide', 2)
     elif sym == '*':
     
      self.vmwriter.writeCall('Math.multiply', 2)

        

    def compileTerm(self):

      pass




         
        

    def compileExpressionList(self):

      pass



 
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
##        if tok in ['<','>','"','&']: tok = self.sym[tok]
        return tok    

    

class VMWriter:



  def __init__(self, output_file):
    self.output = output_file

  def writePush(self, segment, index):
      seg = '' 
      if segment == 'CONST': seg = 'constant'
      elif segment == 'ARG' : seg = 'argument'
      else: seg = segment.lower()
      self.write_out('pop '+ seg + ' ' + str(index)) 


  def writePop(self, segment, index):
      seg = '' 
      if segment == 'CONST': seg = 'constant'
      elif segment == 'ARG' : seg = 'argument'
      else: seg = segment.lower()
      self.write_out('pop '+ seg + ' ' + str(index))


  def writeArithmetic(self, command):
    self.write_out(command.lower())

  def writeLabel(self, label):
    self.write_out('label ' + label)


  def writeGoto(self, label):
    self.write_out('goto ' + label)


  def writeIf(self, label):
    self.write_out('if-goto ' + label)

  def writeCall(self, name, nArgs):
    self.write_out('call ' + name + ' '+ str(nArgs) )

  def writeFunction(self, name, nLocals):
    self.write_out('function ' + name + ' ' + str(nLocals))

  def writeReturn(self):
    self.write_out('return')

  def close(self):
    self.output.close()


  def write_out(self, string):
    self.output.write(string + '\n')



class SymbolTable:

  def __init__(self):
      
    self.ARG = 0
    self.FIELD = 0
    self.STATIC = 0
    self.VAR = 0
    self.varnumbers = {'ARG':0,'STATIC':0,'VAR':0, 'FIELD':0}

    self.subroutine = {}
    self.field = {}
    self.static = {}

  def startSubroutine(self):
    self.subroutine = {}


  def define(self, name, type, kind):
    number = None

    if kind in ('ARG', 'VAR'):
      if kind == 'ARG':
        number = self.ARG
        self.ARG =  self.ARG + 1
      elif kind == 'VAR':
        number = self.VAR
        self.VAR = self.VAR + 1

      self.subroutine[name] = (type, kind, number)
    
    
  

    elif kind in('STATIC','FIELD'):
      if kind == 'STATIC':
        number = self.STATIC
        self.STATIC = self.STATIC + 1
        self.static[name] = (type, kind, number)
      elif kind == 'FIELD':
        number = self.FIELD
        self.FIELD = self.FIELD +  1
        self.field[name] = (type, kind, number)

    self.varnumbers['ARG'] = self.ARG
    self.varnumbers['VAR'] = self.VAR
    self.varnumbers['STATIC'] = self.STATIC
    self.varnumbers['FIELD'] = self.FIELD


  def varCount(self, kind):
    print(self.varnumbers)
    
    return self.varnumbers[kind]

  def typeOf(self, name):
    if name in self.subroutine.keys():
      return self.subroutine[name][0]
    elif name in self.field.keys():
      return self.field[name][0]
    elif name in self.static.keys():
      return self.static[name][0]
    else:
      return 'NONE'
    

  def kindOf(self, name):
    print(self.subroutine[name][1])
    if name in self.subroutine.keys():
      return self.subroutine[name][1]
    elif name in self.field.keys():
      return self.field[name][1]
    elif name in self.static.keys():
      return self.static[name][1]
    else:
      return 'NONE'



  def indexOf(self, name):
    if name in self.subroutine.keys():
      return self.subroutine[name][2]
    elif name in self.field.keys():
      return self.field[name][2]
    elif name in self.static.keys():
      return self.static[name][2]
    else:
      return'NONE'
