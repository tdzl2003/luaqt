class signal_/*%return class.classname%*/_/*%return id%*/_callback
	: public LuaQt::generic_callback
{
public:
	signal_/*%return class.classname%*/_/*%return id%*/_callback(lua_State *L)
		: LuaQt::generic_callback(L)
	{
	}
	~signal_/*%return class.classname%*/_/*%return id%*/_callback()
	{
	}
	void operator() (/*%
local ret = {}
	for i,v in ipairs(arguments) do
		table.insert(ret, string.format("%s arg%d", 
			v.normalizedType, 
			i
		))
	end
return table.concat(ret, ', ')
%*/)
	{
		this->push();
/*%
local ret = {}
	for i,v in ipairs(arguments) do
		table.insert(ret, string.format("\t\tPUSH_RET_VAL((%s), arg%d);", 
			v.normalizedType,
			i
		))
	end
return table.concat(ret, '\n');
%*/
		lua_call(L, /*%return #arguments%*/, 0);
	}
};

int signal_/*%return class.classname%*/_/*%return id%*/(lua_State *L)
{
	for (;;){
		CHECK_ARG_COUNT(2);
		CHECK_ARG((CLASS*), 1);
		CHECK_LUAFUNCTION_ARG(2);

		START_ARGREF_FRAME();
		GET_ARG((CLASS*), 1, self);

		QObject::connect(self, static_cast</*%
		return type.rawName
%*/(CLASS::*)(/*%
		local ret = {}
		for i, v in ipairs(arguments) do
			table.insert(ret, v.type.rawName)
		end
		return table.concat(ret, ", ")
%*/)>(&CLASS::/*%return name%*/), signal_/*%return class.classname%*/_/*%return id%*/_callback(L));

		END_ARGREF_FRAME();
		return 0;
	}

	return luaL_error(L, "No valid overload found.");
}
