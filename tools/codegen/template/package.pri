
SOURCES += ../../../gen//*%return packageName%*///*%return packageName%*/.cpp
/*%
	local ret = {}
	for i,v in ipairs(classes) do
		table.insert(ret, string.format("SOURCES += ../../../gen/%s/def%s.cpp\n", packageName, v))
	end
	return table.concat(ret)
%*/
