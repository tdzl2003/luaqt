	for (;;)
	{
		CHECK_ARG_COUNT(/*%return 1+#arguments%*/);
		CHECK_USERDATA_ARG(1);

/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        CHECK_ARG((%s), %d);\n", v.normalizedType, i+1)
		end
		return ret
%*/
		START_ARGREF_FRAME();
		GET_USERDATA((const QMetaObject*), 1, mo);
/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format("        GET_ARG((%s), %d, arg%d);\n", v.normalizedType, i+1, i)
		end
		return ret
%*/
		CLASS* obj = new CLASS_EXTENDED(mo/*% 
		local ret = ""
		for i,v in ipairs(arguments) do
			ret = ret .. string.format(", arg%d", i)
		end
		return ret
%*/);

		LuaQt::InitAndPushObject(L, obj, obj, CLASS_NAME);

		END_ARGREF_FRAME();

		return 1;
	}
