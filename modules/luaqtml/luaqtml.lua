-- Copyright (C) 2013 tdzl2003.
-- Contact: https://github.com/tdzl2003/luaqt

-- This file is part of the LuaQt Toolkit source.

-- This file is licensed at BSD New license.

-- NOTICE:
-- THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
-- AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
-- IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
-- ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
-- LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
-- CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
-- SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
-- INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
-- CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
-- ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
-- POSSIBILITY OF SUCH DAMAGE. 

-- read COPYRIGHT.md for more informations.

require("QtCore")
local LuaQtHelper = require("LuaQtHelper")

function requireUI(path)
	return loadstring(require("uic").run(path))()
end

local function transArg(f)
	return function()
		local cmd, args = f()
		if (not cmd) then
			return
		end
		local ret = {}
		for v in args:gmatch("[^%s]+") do
			table.insert(ret, v)
		end
		if (#ret > 0) then
			return cmd, ret
		end
		return cmd
	end
end

local function parseFunction(match, typename)
	local name
	local argtypes = {}
	local rettype
	for cmd, args in match do
		if (cmd == "name") then
			name = args[1] or error("Missing argument for @name")
		elseif (cmd == "argument") then
			table.insert(argtypes, args[1] or error("Missing argument for @argument"))
		elseif (cmd == "return") then
			rettype = args[1] or error("Missing argument for @return")
		elseif (cmd == "end") then
			assert(not args or args[1] == typename)
			break
		end
	end
	return name, argtypes, rettype or "void"
end

local function parseConstructor(args, Class, match, define)
	local name, argtypes = parseFunction(match, "constructor")
	name = name or (args and args[1]) or error("Missing argument or @name for @constructor")
	local func = define[name] or error("Missing function definition"..name)


	local env = {}
	local super = Class.superClass
	local mo, self
	function env.super(...)
		self = super.newExtended(mo, ...)

		return self
	end

	setmetatable(env, {__index=_G})

	if (_VERSION == "Lua 5.1") then
		debug.setfenv(func, env)
	else
		debug.setupvalue(func, 1, env)
	end
	LuaQtHelper.addConstructor(Class, argtypes, function(_mo, ...)
		mo = _mo
		func(...)
		return self or error("super() was not called in constructor")
	end)
end

local function parseSlot(args, Class, match, define)
	local name, argtypes, rettype = parseFunction(match, "slot")
	local slotname = (args and args[1]) or error("Missing argument for @slot. @name for @slot used only for overloads.")
	name = name or slotname
	LuaQtHelper.addSlot(Class, rettype, slotname, argtypes, define[name] or error("Missing function definition"..name))
end

local function parseSignal(args, Class, match, define)
	local name, argtypes, rettype = parseFunction(match, "signal")
	name = name or (args and args[1]) or error("Missing argument or @name for @signal")
	LuaQtHelper.addSignal(Class, rettype, name, argtypes)
end

local function parseMethod(args, Class, match, define)
	local name, argtypes, rettype = parseFunction(match, "method")
	local methodname = (args and args[1]) or error("Missing argument for @slot. @name for @method used only for overloads.")
	name = name or methodname
	LuaQtHelper.addMethod(Class, rettype, methodname, argtypes, define[name] or error("Missing function definition"..name))
end

local function parseClass(args, match, define, ret)
	local Class = {
		className = args[1] or error("Missing argument for @class"),
		superClass = QObject
	}
	define = define[Class.className]
	for cmd,args in match do
		if (cmd == "extends") then
			Class.superClass = _G[args[1]] or error("Cannot find super class "+args[1])
		elseif (cmd == "constructor") then
			parseConstructor(args, Class, match, define)
		elseif (cmd == "slot") then
			parseSlot(args, Class, match, define)
		elseif (cmd == "signal") then
			parseSignal(args, Class, match, define)
		elseif (cmd=="method") then
			parseMethod(args, Class, match, define)
		elseif (cmd=="end") then
			assert(not args or args[1] == "class")
			break
		end
	end

	Class = LuaQtHelper.defineQtClass(Class)
	_G[Class.className] = _G[Class.className] or Class
	ret[Class.className] = Class
	return Class
end

function requireQtModule(module)
	if (package.loaded[module]) then
		return package.loaded[module]
	end
	local path, err = package.searchpath(module, package.path)
	if (not path) then
		error("Cannot find module "..module..":"..err)
	end

	local content
	do
		-- read the whole file content
		local fd = io.open(path)
		content = fd:read("*a")
		fd:close()
		fd = nil
	end

	local define = loadstring(content)(module)

	local match = transArg(content:gmatch("%\n%-%-%s-%@%s-(%w+)([^\n]*)"))

	if (match() ~= "luaqt") then
		error("Module "..module.." does not looks like a LuaQt Module.")
	end

	local ret = {}
	for cmd, args in match do
		if (cmd == "class") then
			parseClass(args, match, define, ret)
		end
	end
	package.loaded[module] = ret
	return ret
end
