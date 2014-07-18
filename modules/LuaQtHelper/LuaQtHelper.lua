local LuaQt = require("LuaQt")
require("QtCore")

local helper = {}

function helper.addConstructor(mo, arguments, creator)
	mo.constructorList = mo.constructorList or {}
	local constructor = {
		arguments = arguments,
		creator = creator
	}
	table.insert(mo.constructorList, constructor)
	mo.constructor = creator
end

function helper.addSignal(mo, type, name, arguments)
	mo.signalList = mo.signalList or {}
	local signal = {
		type = type,
		name = name,
		arguments = arguments,
	}

	table.insert(mo.signalList, signal)
end

function helper.addSlot(mo, type, name, arguments, func)
	mo.slotList = mo.slotList or {}
	local slot = {
		type = type,
		name = name,
		arguments = arguments,
		func = func
	}

	table.insert(mo.slotList, slot)
end

function helper.addMethod(mo, type, name, arguments, func)
	mo.methodList = mo.methodList or {}
	local method = {
		type = type,
		name = name,
		arguments = arguments,
		func = func
	}

	table.insert(mo.methodList, method)
end

local function buildMetaInfo(mo)
	local strings = {}
	local stringMap = {}
	local metaDatas = {}
	local function addUint(i)
		table.insert(metaDatas, i)
	end
	local function addString(str, flag)
		if (not stringMap[str]) then
			stringMap[str] = #strings
			table.insert(strings, str)
		end
		local v = stringMap[str]
		if (flag) then
			v = v+ flag
		end
		table.insert(metaDatas, v)
	end
	local function addPlaceHolder()
		table.insert(metaDatas, 0)
		local pos = #metaDatas
		return function (val)
			metaDatas[pos] = val or #metaDatas
		end
	end
	local function addType(typeName)
		local typeid = LuaQt.getTypeId(typeName)
		if (not typeid) then
			addString(typeName, 0x80000000)
		else
			addUint(typeid)
		end
	end
-- content:
	addUint(7)					-- revision
	addString(mo.className)		-- classname
	addUint(0)	addUint(0)		-- classinfo
	addUint(#mo.slotList + #mo.signalList) addUint(14)		--methods
	addUint(0)  addUint(0)		-- properties
	addUint(0)	addUint(0)		-- enums/sets
	addUint(#mo.constructorList)	local consOfs = addPlaceHolder() 	--constructors
	addUint(0)					-- flags
	addUint(#mo.signalList)		-- signalCount

-- signals: name, argc, parameters, tag, flags
	local signalParamHolders = {}
	for i,v in ipairs(mo.signalList) do
		addString(v.name)							-- name
		addUint(#v.arguments)						-- argc
		signalParamHolders[i] = addPlaceHolder()	-- parameters
		addString("")								-- tag
		addUint(0)									-- flags
	end

	local slotParamHolders = {}
	for i,v in ipairs(mo.slotList) do
		addString(v.name)							-- name
		addUint(#v.arguments)						-- argc
		slotParamHolders[i] = addPlaceHolder()	-- parameters
		addString("")								-- tag
		addUint(0)									-- flags
	end
	
	for i,v in ipairs(mo.signalList) do
		signalParamHolders[i]()
		addType(v.type)								-- return type
		for j,arg in ipairs(v.arguments) do
			addType(arg)							-- argument type
		end
		for j,arg in ipairs(v.arguments) do
			addString("")							-- argument name
		end
	end

	for i,v in ipairs(mo.slotList) do
		slotParamHolders[i]()
		addType(v.type)								-- return type
		for j,arg in ipairs(v.arguments) do
			addType(arg)							-- argument type
		end
		for j,arg in ipairs(v.arguments) do
			addString("")							-- argument name
		end
	end

	consOfs()
	local consParamHolders = {}
	for i,v in ipairs(mo.constructorList) do
		addString(mo.className)
		addUint(#v.arguments)
		consParamHolders[i] = addPlaceHolder()	-- parameters
		addString("")								-- tag
		addUint(0)									-- flags
	end

	for i,v in ipairs(mo.constructorList) do
		consParamHolders[i]()
		addType("")									-- return type
		for j,arg in ipairs(v.arguments) do
			addType(arg)							-- argument type
		end
		for j,arg in ipairs(v.arguments) do
			addString("")						-- argument name
		end
	end

	addUint(0)

	return strings, metaDatas
end

local function unpackArgs(args, argtable)
	local ret = {}
	for i,v in ipairs(argtable) do
		ret[i] = v(args, i)
	end
	return unpack(ret)
end

local function nop()
end

local function parseType(n)
	if (LuaQt.transArg[n]) then
		return LuaQt.transArg[n]
	end

	local a, b = n:match("(%w+)%<(.+)%>")
	if (a) then
		print("Warning: Template argument is not supported:" + n);
		return nop
	end

	local pointer = n:match("(%w+)%*")
	if (pointer) then
		-- try QObject classes
		if (_G[pointer] and type(_G[pointer]) == 'table' and _G[pointer].transPointerArg) then
			return _G[pointer].transPointerArg
		end
	end

	print("Warning: Argument type not supported: " .. n);
	return nop
end

local function getArgHelper(types)
	local ret = {}
	for i, v in ipairs(types) do
		ret[i] = parseType(v)
	end
	return ret
end

local function defineMetaCall(mo)
	local invoke = {}
	local argtable = {}

	local function metaCall(c, id, self, args)
		return c == 0  and invoke[id] and invoke[id](self, unpackArgs(args, argtable[id]))
	end

	-- InvokeMetaMethod
	do
		local localid = 1

		for i,v in ipairs(mo.signalList) do
			invoke[localid] = v.func
			argtable[localid] = getArgHelper(v.arguments)
			localid = localid + 1
		end

		for i,v in ipairs(mo.slotList) do
			invoke[localid] = v.func
			argtable[localid] = getArgHelper(v.arguments)
			localid = localid + 1
		end
	end

	return metaCall
end

function helper.defineQtClass(mo)
	mo.signalList = mo.signalList or {}
	mo.slotList = mo.slotList or {}
	mo.methodList = mo.methodList or {}
	
	local stringData, metaData = buildMetaInfo(mo)

	local _metaObject = LuaQt.defineMetaObject(
			stringData,
			metaData,
			mo.superClass and mo.superClass._metaObject or QObject._metaObject,
			defineMetaCall(mo)
		)
	mo._metaObject = _metaObject

	local methods = {}
	mo.methods = methods
	for k,v in pairs(mo.superClass.methods) do
		methods[k] = methods[k] or v
	end

	local getters = {}
	mo.getters = getters
	for k,v in pairs(mo.superClass.getters) do
		getters[k] = getters[k] or v
	end

	for i,v in ipairs(mo.methodList) do
		methods[v.name] = v.func
	end

	for i,v in ipairs(mo.slotList) do
		methods[v.name] = v.func
	end

	for i,v in ipairs(mo.signalList) do
		methods[v.name] = function(self)
			LuaQt.activate(self, _metaObject, i-1, {})
		end
	end

	mo.__index = function(t, k)
		return (getters[k] and getters[k](t)) or methods[k]
	end

	local creator = mo.constructor
	function mo.new(...)
		local ret = creator(_metaObject, ...)
		setmetatable(ret, mo)
		return ret
	end
	function mo.newExtended(mo, ...)
		return creator(mo, ...)
	end

	return mo
end

return helper
