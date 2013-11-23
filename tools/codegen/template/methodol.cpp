	for (;;)
	{
		CHECK_ARG_COUNT(/*%return #arguments+1%*/);

/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        CHECK_ARG(%s, %d);\n", v.normalizedType, i+1)
		end
		return ret
%*/
		START_ARGREF_FRAME();
		GET_ARG(CLASS*, 1, self);
/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        GET_ARG(%s, %d, arg%d);\n", v.normalizedType, i+1, i)
		end
		return ret
%*/

/*%
		if (normalizedType ~= "void") then
			return "\t\tPUSH_RET_VAL((" .. normalizedType .."),"
		end
		return ""
%*/
		self->/*%return name%*/(
/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("arg%d, ", i)
		end
		return ret:sub(1, -3)
%*/)
/*%
		if (normalizedType ~= "void") then
			return "\t\t)"
		end
		return ""
%*/

		END_ARGREF_FRAME();

/*%
		if (normalizedType ~= "void") then
			return "\t\treturn 1"
		else
			return "\t\treturn 0"
		end
%*/
	}