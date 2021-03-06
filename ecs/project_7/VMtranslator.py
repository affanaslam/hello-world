#sa00310
import sys
from pathlib import Path
import os
import re

class Parser(object):
    '''Parses a single vm file to provide convenient access to the
    contained commands and their components.

    '''
    '''
the idea is to use 'stacks' like full-fledged parsers (such as LEX); it seems to be a good practice

pseudocode:

_init_

programstack [ ]
// but it checks whether the entire stack is empty is not
then we have:
currentcommand[ ]
it is the command in the list


'''

    def __init__(self, fname):

        infile = open(fname, 'r')
        self._data = infile.read()
        self._datatokens = self._tokens(self._data)[:-1][1:]
        print(self._datatokens)
        self._commandlist = []

    '''
    command list carries the entire expression - as in 'push command 0' whereas command is the current 'command' ('push', 'command' , '0')
    '''


    '''dictionaries for storing constants- copied for the chapter 7 mandual'''

    _type = {'push':'C_PUSH', 'pop':'C_POP', 'add':'C_ARITHMETIC', 'sub':'C_ARITHMETIC', 'neg':'C_ARITHMETIC',
                             'eq' :'C_ARITHMETIC', 'gt' :'C_ARITHMETIC', 'lt' :'C_ARITHMETIC',
                             'and':'C_ARITHMETIC', 'or' :'C_ARITHMETIC', 'not':'C_ARITHMETIC',
                             'call':'C_CALL',      'return':'C_RETURN',  'function':'C_FUNCTION',
                             'label':'C_LABEL',    'goto':'C_GOTO',      'if-goto':'C_IF'
                              }
    _argument2 = ['C_PUSH', 'C_POP', 'C_FUNCTION', 'C_CALL']


    def __str__(self):
        '''Leave as is.'''
        return 'Parser object'

    def hasMoreCommands(self):


        '''P.hasMoreCommands() -> bool

        Returns True if there are commands in the input, False
        otherwise.
        '''
        return self._datatokens != []

    def advance(self):

        if self.hasMoreCommands():
            self._commandlist = self._datatokens.pop(0)





        '''P.advance() -> None

        Makes the next command the current command. Should be called
        only if hasMoreCommands() is True.
        '''
        

    def commandType(self):

        return self._type[self._commandlist[0]]
        '''P.commandType() -> str

        Returns the type of the current VM command: one of
        C_ARITHMETIC
        C_PUSH, C_POP
        C_LABEL
        C_GOTO
        C_IF
        C_FUNCTION
        C_RETURN
        C_CALL
        '''
        pass

    def arg1(self):
        if self.commandType()!= 'C_RETURN':
            if self.commandType() == 'C_ARITHMETIC': return self._commandlist[0]
            else: return self._commandlist[1]


    def arg2(self):

        if self.commandType() in self._argument2:
            return self._commandlist[2]

    def remove(self,string):
        string = re.sub(re.compile("//.*?\n" ) ,"" ,string)
        return string

    def _split_str(self,string):
        ls = string.split('\n')
        lis = []
        for e in ls:
            lis.append(e.split(' '))
        return lis



    def _tokens(self,string):

        rc = self.remove(string)
        ls = self._split_str(rc)
        
        
        for l in ls:
            
            while True:
                
                
                try:
    
                    l.remove('')
                except ValueError:
                    
                     break
        return ls


''' more functions for Parser '''


class CodeWriter(object):




    _asm = {'index':'', 'loadsp':'@SP \n A=M', 'loadcomp':'M=D', 'inc':'@SP \n M=M+1','dec':'\n @SP \n M=M-1 \n'}

    _math = {'add':'M+D', 'sub':'M-D', 'and':'M&D', 'or':'D|M', 'neg':'-D', 'not':'!D', 'eq':'JEQ', 'lt':'JLT', 'gt':'JGT'}


    '''Translates VM commands into Hack assembly code.'''

    def __init__(self, fname):


        self._l = 0
        self._file = ''

        self._outfile = open(fname, 'w')
        '''Opens the output file at fname and gets ready to write to it.'''

    def __str__(self):
        '''Leave as is.'''
        return 'CodeWriter object.'

    def setFileName(self, fname):

        name,extension = os.path.splitext(fname)
        self._file = name


    def writeArithmetic(self,commandtype,command):
        if commandtype == 'C_ARITHMETIC':
            if command == 'add': self._basic_op(self._math['add'])
            elif command == 'sub':self._basic_op(self._math['sub'])
            elif command == 'and':self._basic_op(self._math['and'])
            elif command == 'or':self._basic_op(self._math['or'])
            elif command == 'neg':self._write_outfile("\n @SP \n M=M-1 \n A=M \n M=-M \n @SP \n M=M+1")
            elif command == 'eq':self._jmp(self._math['eq'])
            elif command == 'lt':self._jmp(self._math['lt'])
            elif command == 'gt':self._jmp(self._math['gt'])
            elif command == 'not':self._write_outfile("\n @SP \n M=M-1 \n A=M \n D=M \n M=!D \n @SP \n M=M+1 \n")
            






        '''CW.writeArithmetic(str) -> None

        Writes to the output file the assmebly code that is the
        translation of the given arithmetic command.
        '''
        

    def writePushPop(self,command, segment, index):
        if command== 'C_PUSH' : self._push(segment, str(index))
        elif command== 'C_POP' :  self._pop(segment, str(index))




    def _pop(self, segment, address):
        if segment not in ['static','temp','pointer']:
            if address == '0':
                self._write_outfile(self._asm['dec']) #@SP  \n M=M-1 
                self._write_outfile(self._asm['loadsp'][6:]) #A=M
                self._write_outfile(self._asm['loadcomp'][::-1]) #D=M
                if segment == 'local': self._asm['index'] = '@LCL \n'
                elif segment == 'argument': self._asm['index'] = '@ARG \n '
                elif segment == 'this': self._asm['index'] = '@THIS \n'
                elif segment == 'that': self._asm['index'] = '@THAT \n'
                self._write_outfile(self._asm['index'])
                self._write_outfile(self._asm['loadsp'][6:])#A=M
                self._write_outfile(self._asm['loadcomp'])#M=D


            elif address!= '0':
                if segment == 'local': self._asm['index'] = '@LCL \n'
                elif segment == 'argument': self._asm['index'] = '@ARG \n'
                elif segment == 'this': self._asm['index'] = '@THIS \n'
                elif segment == 'that': self._asm['index'] = '@THAT \n'
                
                
                self._write_outfile(self._asm['index'])
                self._write_outfile(self._asm['loadcomp'][::-1])
                self._asm['index'] = '@'+address+'\n D=D+A'
                self._write_outfile(self._asm['index'])
                self._asm['index'] = '@R13\n'
                self._write_outfile(self._asm['index'])
                self._write_outfile(self._asm['loadcomp'])
                self._asm['index'] = '@SP \n'
                self._write_outfile(self._asm['index'])
                self._write_outfile('AM=M-1 \n')
                self._write_outfile(self._asm['loadcomp'][::-1])
                self._asm['index'] = '@R13\n'
                self._write_outfile(self._asm['index'])
                self._write_outfile(self._asm['loadsp'][6:])
                self._write_outfile(self._asm['loadcomp'])
        elif segment == 'static':
            
            self._write_outfile('@'+self._file + str(address) +'\n D=A \n @R13 \n M=D \n @SP \n AM=M-1\n D=M \n @R13 \n A=M \n M=D \n' )
        elif segment == 'temp':
            self._write_outfile('@'+str((5+int(address)))+'\n D=A \n @R13 \n M=D \n @SP \n AM=M-1 \n D=M \n @R13 \n A=M \n M=D \n')
        elif segment == 'pointer':
            self._write_outfile('@'+str((3+int(address)))+'\n D=A \n @R13 \n M=D \n @SP \n AM=M-1 \n D=M \n @R13 \n A=M \n M=D \n')
                

    def _push(self, segment, address):
        
        if segment == 'constant':self._asm['index'] = '@'+address+'\n D=A'
        if segment == 'argument':self._asm['index'] = '@ARG \n D=M \n @'+address+'\n D=A+D \n A=D \n D=M'
        if segment == 'local':self._asm['index'] = '@LCL \n D=M \n @'+address+'\n D=A+D \n A=D \n D=M'
        if segment == 'this':self._asm['index'] = '@THIS \n D=M \n @'+address+'\n D=A+D \n A=D \n D=M'
        if segment == 'that':self._asm['index'] = '@THAT \n D=M \n @'+address+'\n D=A+D \n A=D \n D=M'
        if segment == 'static': self._asm['index'] = '@' +self._file + str(address) +'\n D=M'
        if segment == 'temp': self._asm['index'] = '@'+ str((5+int(address)))+'\n D=M'
        if segment == 'pointer' : self._asm['index'] ='@'+ str((3+int(address)))+'\n D=M'
        self._write_outfile(self._asm['index'])
        self._write_outfile(self._asm['loadsp'])
        self._write_outfile(self._asm['loadcomp'])
        self._write_outfile(self._asm['inc'])
    

    def _write_outfile(self, data):
        self._outfile.write(data + '\n')

    def _basic_op(self,exp):
        self._outfile.write(self._asm['dec'])
        self._outfile.write('A=M \n')
        self._write_outfile(self._asm['loadcomp'][::-1])
        self._outfile.write(self._asm['dec'] )
        self._write_outfile(self._asm['loadsp'][6:])
        self._write_outfile(self._comp('D',exp))
        self._write_outfile(self._asm['loadcomp'])
        self._write_outfile(self._asm['inc'])

    def _comp(self, destination, value):
            
            
                    
           if destination != "":
               return destination + "=" + value
                   
           else:
               return value
            
            

    def _comp_jmp(self, val, jmp):
        if jmp != "": return val + ";" + jmp
           
           
           
           
           

    def _single_var(self,val):
       self._outfile.write(self._asm['dec'])
       self._write_outfile(self._asm['loadcomp'][::-1])
       self._write_outfile(self._comp('D',exp))
       self._write_outfile(self._asm['loadcomp'])
       self._write_outfile(self._asm['inc'])

    def _jmp (self, jump):
           
           self._outfile.write(self._asm['dec'])
           self._write_outfile(self._asm['loadsp'][6:])
           self._write_outfile(self._asm['loadcomp'][::-1])
           self._outfile.write(self._asm['dec'])
           self._write_outfile(self._asm['loadsp'][6:])
           self._write_outfile(self._comp('D','M-D') + '\n')
           start_label = self._generate_jump_command('D',jump)
           self._outfile.write(self._asm['loadsp'])
           self._outfile.write('\n M=0 \n')
           end_label = self._generate_jump_command('0','JMP')
           self._outfile.write(self._label(start_label) + '\n')
           self._outfile.write(self._asm['loadsp'])
           self._outfile.write('\n M=-1 \n')
           self._outfile.write(self._label(end_label) + '\n')
           self._write_outfile(self._asm['inc'])


           

        
    def _generate_jump_command(self, val, jmp):
           
           
          new_label = self._generate_lab()
          self._write_outfile('@' + new_label + '\n')
          self._write_outfile(self._comp_jmp(val,jmp) + '\n')
          return new_label


    def _generate_lab(self):
           self._l += 1
           return 'L' + str((self._l))

        


    def _label (self, lab):
       
      return '(' + lab + ')'
           

        

    def close(self):
           self._outfile.close()

        

def printUsage():
    '''printUsage() -> None

    Prints infomration on how to call this file.
    '''
    print("Usage: VMtranslator source")
    print("source is one of")
    print("\ta .vm file\n\ta directory containing .vm files")

def getFileNames():
    '''getFileNames() -> tuple

    Returns a tuple contianing the name of the output ASM file and a
    list of names of the VM files to operate on, as per the call to
    the program from command line.
    '''
    if len(sys.argv) != 2:
        printUsage()
        print('Invalid call:')
        for x in sys.argv:
            print(x)
        print()
        sys.exit()  # End program.
    p = Path(sys.argv[1])
    fname = str(p)
    if p.is_dir():
        while fname[-1] == '/':
            fname = fname[:-1]
        asmFname = fname + '.asm'
        vmFiles = list(p.glob('*.vm'))
    elif fname[-3:] == '.vm' and p.exists():
        asmFname = fname[:-3]+'.asm'
        vmFiles = [p]
    else:
        printUsage()
        print('Invalid file:', fname,'\nAborting!')
        sys.exit() # End program.
    vmFiles = [str(f) for f in vmFiles]
    return (asmFname, vmFiles)

def main():
    asmFname, vmFiles = getFileNames()
    #asmFname, vmFiles = ('SimpleAdd.asm',['SimpleAdd.vm']) without commandline
    CW = CodeWriter(asmFname)

    push_pop = ['C_PUSH','C_POP']


    for f in vmFiles:
        P= Parser(f)
        CW.setFileName(f)
        while P.hasMoreCommands():
            P.advance()
            CT = P.commandType()
            if CT == 'C_ARITHMETIC':
                print(P.arg1())
                CW.writeArithmetic(P.commandType(),P.arg1())
            elif CT in push_pop:
                print(P.commandType(),P.arg1(),P.arg2())
                CW.writePushPop(P.commandType(),P.arg1(),P.arg2())
    CW._write_outfile('(_1) \n @_1 \n 0;JMP')

    CW.close()


    # asmFname now contains the name of the file to output to.
    # vmFiles is a list contianing the names of VM files to be translated.



if __name__ == "__main__":
    # Leave as is.
    main()

                        
                        
                        
