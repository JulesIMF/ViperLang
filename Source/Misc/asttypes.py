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


#
# Definitions
#

with open("asttypes") as tfile:
    for type in tfile:
        type = type.strip()
        print(f'class {type};')

print('\n\n')

with open("asttypes") as tfile:
    for type in tfile:
        type = type.strip()
        print(f'virtual void {type}({type}*) = 0;')

print('\n\n')

with open("asttypes") as tfile:
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