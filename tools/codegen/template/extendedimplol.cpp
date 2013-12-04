		explicit /*%return class.classname%*/_Extended_Impl(const QMetaObject * _mo
			/*%
	local ret = {}
	for i,v in ipairs(func.arguments) do
		table.insert(ret, ",")
		table.insert(ret, v.type.rawName)
		table.insert(ret, "arg"..i)
	end
	return table.concat(ret, " ")
%*/)
			: mo(_mo), /*%return class.classname%*/(/*%
	local ret = {}
	for i = 1, #func.arguments do
		table.insert(ret, "arg"..i)
	end
	return table.concat(ret, ", ")
%*/)
		{
		}
