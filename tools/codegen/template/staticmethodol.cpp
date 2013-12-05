	for (;;)
	{
		CHECK_ARG_COUNT(/*%return #arguments%*/);

/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        CHECK_ARG((%s), %d);\n", v.normalizedType, i)
		end
		return ret
%*/
		START_ARGREF_FRAME();
/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        GET_ARG((%s), %d, arg%d);\n", v.normalizedType, i, i)
		end
		return ret
%*/

/*%
		if (normalizedType ~= "void") then
			return "\t\tPUSH_RET_VAL((" .. normalizedType .."),"
		end
		return ""
%*/
		CLASS::/*%return name%*/(
/*% 
		local ret = {"\t\t\t"}
		for i,v in ipairs(arguments) do
			table.insert(ret, string.format("arg%d", i))
			table.insert(ret, ", ")
		end
		table.remove(ret)
		return (#ret>0) and table.concat(ret) or ""
%*/
		)
/*%
		if (normalizedType ~= "void") then
			return "\t\t);"
		else
			return ";"
		end
%*/

		END_ARGREF_FRAME();

/*%
		if (normalizedType ~= "void") then
			return "\t\treturn 1;"
		else
			return "\t\treturn 0;"
		end
%*/
	}