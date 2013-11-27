int /*%return table.concat(route, '_')%*/(lua_State *L)
{
	CLASS* obj1 = (CLASS*)LuaQt::checkObject(L, 1, CLASS_NAME);
/*%
	local ret = {}
	for i = 2, #route do
		table.insert(ret, string.format("\t%s* obj%d=obj%d;\n", route[i], i, i-1))
	end
	return table.concat(ret)
%*/
	lua_pushlightuserdata(L, obj/*%return #route%*/);
	return 1;
}