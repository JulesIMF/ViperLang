# ++
#
# Copyright (c) 2023 JulesIMF, MIPT
#
# Module Name:
#
#     asttypes.py
#
# Abstract:
#
#     
#
# Author / Creation date:
#
#     JulesIMF / 17.03.23
#
# Revision History:
# 
# --


#
# Imports
#

import sys

#
# Definitions
#

asttypes_filename = "../../../Docs/Grammar/nonterminals"
query = "".join(sys.argv)
query = query[query.find('py') + 2:]
query = query.strip()

if query == "predef":
    with open(asttypes_filename) as tfile:
        for type in tfile:
            type = type.strip()
            print(f'class {type};')

elif query == "visitors":
    with open(asttypes_filename) as tfile:
        for type in tfile:
            type = type.strip()
            print(f'virtual void {type}({type}*) = 0;')

elif query == "classtemplate":
    with open(asttypes_filename) as tfile:
        for type in tfile:
            type = type.strip()
            print(
f'''
class {type} : public AstNode
{{
public:
    {type}(Lex::Location location) :
        AstNode(location)
    {{
    }}

    virtual void
    Accept(Visitor& visitor)
    {{
        visitor.As<AstVisitor>().{type}(this);
    }}
}};
''')

elif query == "nullptr":
    with open(asttypes_filename) as tfile:
        for type in tfile:
            type = type.strip()
            print(f'{type}* p{type} = nullptr;')

else:
    if query == "":
        print("Empty query!")
    
    else:
        print(f'Unknown query "{query}"!')

