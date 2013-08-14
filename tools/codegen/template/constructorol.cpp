	for (;;)
	{
		CHECK_ARG_COUNT(/*%return #arguments%*/);

/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        CHECK_ARG(%s, %d);\n", v.normalizedType, i)
		end
		return ret
%*/
		START_ARGREF_FRAME();
/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        GET_ARG(%s, %d, arg%d);\n", v.normalizedType, i, i)
		end
		return ret
%*/
		CLASS* obj = new CLASS(arg1, arg2);

		LuaQt::InitAndPushObject(L, obj, obj, CLASS_NAME);

		END_ARGREF_FRAME();

		return 1;
	}