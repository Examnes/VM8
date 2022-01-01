import os
import json

code = ""

headers = os.listdir("./include/commands")
code = code.join(f"#include \"commands/{header}\"\n" for header in headers)
code += "#include <map>\n"
code += "#include \"types.h\"\n"
code += "#include \"memory.h\"\n"
code += "#include \"base_command_handler.h\"\n"
code += "class command_handlers_provider {\npublic: \n\tstatic std::map<code_t,command_handler*> get_command_handlers(memory& mem,state& s)\n\t{\n"
code += "\t\tstd::map<code_t,command_handler*> m = std::map<code_t,command_handler*>();\n"
with open('opcodes.json') as json_file:
    data = json.load(json_file)
    for p in data['opcodes']:
        code += f"\t\tm.insert ( std::pair<code_t,command_handler*>({p['cop']},new {p['name']}_command_handler(mem,s,{p['size']})) );\n"
code += "\t\treturn m;\n\t}\n};"
f = open("include/command_handlers_provider.h", "w")
f.write(code)
f.close()

print("handlers combined")


code = ""
