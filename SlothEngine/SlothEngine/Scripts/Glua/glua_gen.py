import os

lua_funcs = dict()
lua_funcs['u32'] = '(u32)lua_tonumber'
lua_funcs['f32'] = '(f32)lua_tonumber'
lua_funcs['int'] = '(int)lua_tonumber'
lua_funcs['Id32'] = '(int)lua_tonumber'
lua_funcs['Id'] = '(int)lua_tonumber'
lua_funcs['float'] = '(float)lua_tonumber'
lua_funcs['char*'] = 'lua_tostring'

lua_pushers = dict()
lua_pushers['u32'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['Id32'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['Id'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['f32'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['int'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['float'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['double'] = 'lua_pushnumber(lua_State, value);'
lua_pushers['char*'] = 'lua_pushstring(lua_State, value);'


class Argument:
    def __init__(self, type, name):
        self.type = type
        self.name = name

        print('Type: ' + type)
        print('Name: ' + name)

    def serialize_cast(self, stack_location):
        lua_func = 'touserdata'
        the_type = self.type.replace('const', '')
        the_type = the_type.replace('&', '').strip(' ')

        lua_func = 'static_cast<{0}>(lua_touserdata'.format(the_type)
        if the_type in lua_funcs.keys():
            lua_func = lua_funcs[the_type]

        return '\t{0} {1} = {2}(pState, {3})'.format(the_type, self.name, lua_func, stack_location)


class Function:
    def __init__(self, class_name='BrokeAssClass', args=[], return_type='void', name='BrokeAssFunction'):
        self.args = list()
        self.return_type = return_type
        self.name = name
        self.class_name = class_name

    def serialize_header(self):
        return 'int {0}_{1}(lua_State* pState)'.format(self.class_name, self.name)

    def parse(self, line):
        open_paren = line.find('(')
        close_paren = line.find(')')
        space = line.rfind(' ', 0, open_paren)

        self.return_type = line[:space].replace('SLTH_API ', '').replace('virtual ', '').lstrip(' \t')
        self.name = line[space + 1:open_paren]
        print('Found function - Name: ' + self.name)

        # deal with arguments
        arg_text = line[open_paren + 1:close_paren]
        args = arg_text.split(',')

        if args[0] != '':
            for arg in args:
                space = arg.rfind(' ')
                self.args.append(Argument(arg[:space], arg[space + 1:]))


def parse_file(filename):
    f = open(filename)

    lines = f.readlines()
    ready_to_parse = False
    class_name = ''
    functions = []

    for line in lines:

        if '//' in line:
            print('Found Comment in: ' + line)
            line = line[0:line.find('//')]
            print('Cleaned: ' + line)

        if len(line) < 1:
            continue

        if 'class' in line and ';' not in line and 'enum' not in line:
            words = line.split(' ')
            class_name = words[1]
            class_name = class_name.rstrip(' \r\n\t')

        if ready_to_parse:
            ready_to_parse = False
            function = Function(class_name)
            function.parse(line)

            functions.append(function)

        if 'GLUA' in line:
            ready_to_parse = True

    f.close()

    if len(functions) == 0:
        return

    f = open(filename.replace('.h', '.gen.h'), 'w')

    f.write('#pragma once\n'
            'namespace glua\n'
            '{\n'
            '\t')

    for function in functions:
        f.write(function.serialize_header() + ';\n')

    f.write('}')

    f.close

    f = open(filename.replace('.h', '.gen.cpp'), 'w')

    f.write('#include "' + filename + '"\n')
    f.write('#include "' + filename.replace('.h', '.gen.h') + '"\n\n')

    # loop through the functions
    for function in functions:
        f.write(function.serialize_header() + '\n')
        f.write('{\n')

        # get 'this' and cast it
        f.write('\tusing namespace slth;\n')
        f.write('\tslth::{0}* p{0} = reinterpret_cast<{0}*>(lua_touserdata(pState, {1}));\n'.
                format(function.class_name, -len(function.args)))

        # get other args
        offset = -len(function.args) - 1
        for arg in function.args:
            f.write(arg.serialize_cast(offset) + ';\n')
            offset += 1

        # call the function and get return type
        f.write('\t')
        if function.return_type != 'void':
            f.write('{0} value = '.format(function.return_type))

        f.write('p{0}->{1}('.format(class_name, function.name))

        # pass the arguments
        arg_string = ''
        for arg in function.args:
            arg_string += arg.name + ', '

        # drop the last comma and space
        arg_string = arg_string[:-2]

        # close the function call
        f.write('{0});\n'.format(arg_string))

        # call the actual function
        if function.return_type != 'void':
            f.write('\t')
            if function.return_type in lua_pushers.keys():
                lua_push = lua_pushers[function.return_type]
            else:
                if '*' in function.return_type:
                    lua_push = 'lua_pushlightuserdata(pState, value);\n'
                else:
                    lua_push = 'lua_pushlightuserdata(pState, &value);\n'
            f.write(lua_push)
            f.write('\treturn 1;\n')
        else:
            f.write('\treturn 0;\n')

        f.write('}\n\n')

    f.close()

    # TODO: remember all the functions that have been generated
    # TODO: write a function that will register every single one with the lua state
    #   with lua_State ( lua_pushcfunction )


for root, dirs, files in os.walk('.'):
    for f in files:
        if '.h' in f and '.gen' not in f:
            parse_file(f)
            print('Parsing: ' + f)
