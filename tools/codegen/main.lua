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
-- 
-- read COPYRIGHT.md for more informations.

local path = require("path")
local json = require("json")

_G.QtPath = "C:\\Qt\\Qt5.1.0x86\\5.1.0\\msvc2012"
_G.QtIncludePath = path.normjoin(QtPath, "include")

local function readJsonFile(path)
	local fd = io.open(path)
	if (not fd) then
		return 
	end
	local str = fd:read("*a")
	fd:close()
	return json.decode(str)
end

_G.config = readJsonFile("config.json")

local excludeClasses = {}
for i,v in ipairs(config.excludeClasses) do
	excludeClasses[v] = true
end

local excludedIncludePath = {}
for i,v in ipairs(config.excludedIncludePath) do
	excludedIncludePath[v] = true
end


local function loadTemplate(path)
	local fd = io.open(path)
	local src = fd:read("*a")
	fd:close()

	return function(args)
		setmetatable(args, {
			__index = _G
		})
		return src:gsub("%/%*%%(.-)%%%*%/", function(s)
			local f = assert(loadstring(s))
			debug.setfenv(f, args)
			return f() or nil
		end) or nil
	end
end

local loadedClassInfo = {}

local function loadClassInfo(class)
	if (loadedClassInfo[class] == nil) then
		loadedClassInfo[class] = readJsonFile("tmp/"..class..".json") or false
	end
	return loadedClassInfo[class]
end

local function getMethodSign(method)
	local ret = {method.name,'(', ''}
	for i,v in ipairs(method.arguments) do
		table.insert(ret, v.normalizedType)
		table.insert(ret, ',')
	end
	table.remove(ret)
	table.insert(ret, ')')
	return table.concat(ret)
end

local function getAbstractMethods(info, map)
	-- first, get all abstract method from all super classes
	map = map or {}

	for i,v in ipairs(info.superclassList) do
		local cinfo = loadClassInfo(v.name) or error("Cannot find info of "..v.name)
		getAbstractMethods(cinfo, map)
		-- for i,v in ipairs(list or {}) do
			-- map[v] = true
		-- end
	end

	-- test if abstract method are implemented.
	for i,v in ipairs(info.methodList) do
		if (not v.isStatic) then
			local sign = getMethodSign(v)
			if (v.isAbstract) then
				map[sign] = true
			else
				map[sign] = nil
			end
		end
	end

	-- local ret = {}
	-- for k,v in pairs(map) do
		-- table.insert(ret, k)
	-- end
	return map
end

local function isDerivedFromQObject(info)
	if (info.classname == "QObject") then
		return true
	end
	for i,v in ipairs(info.superclassList) do
		local cinfo = loadClassInfo(v.name)
		if (cinfo and isDerivedFromQObject(cinfo)) then
			return true
		end
	end
	return false
end

local function isAbstractClass(info)
	local am = getAbstractMethods(info)
	return next(am) and true
end

local packageTemplate = loadTemplate("template/package.cpp")
local function writePackageSource(packageName, classes)
	local fd = io.open("gen/"..packageName.."/"..packageName..".cpp", "w+")

	fd:write(packageTemplate({
			packageName = packageName,
			classes = classes
		}))
	fd:close()
end

local function copyTable(table)
	local ret = {}

	for k,v in pairs(table) do
		if (type(v) == 'table') then
			ret[k] = copyTable(v)
		else
			ret[k] = v
		end
	end
	return ret
end

local function findNestedName(class, name)
	-- find nested enum
	for i,v in ipairs(class.enumList) do
		if (v.name == name) then
			return class.classname.."::"..name
		end
	end
	-- find nested class
	for i,v in ipairs(class.nestedClasses) do
		if (v.classname == name) then
			return class.classname.."::"..name
		end
	end
	-- find flag alias
	for k,v in pairs(class.flagAliases) do
		if (v == name) then
			return class.classname.."::"..name
		end
	end
	-- find in super classes.
	for i,v in ipairs(class.superclassList) do
		local cinfo = loadClassInfo(v.name)
		local ret = findNestedName(cinfo, name)
		if (ret) then
			return ret
		end
	end
end

local function parseNestedName(class, name)
	return name:gsub("(%:*)(%w+)", function(d, s)
		if (d == "::") then
			return
		end
		return findNestedName(class, s)
	end)
end

local constructorTemplate = loadTemplate("template/constructor.cpp")
local constructorOLTemplate = loadTemplate("template/constructorol.cpp")
local methodTemplate = loadTemplate("template/method.cpp")
local methodOLTemplate = loadTemplate("template/methodol.cpp")
local function printMethods(class, name, methods, isConstructor)
	local template = isConstructor and constructorTemplate or methodTemplate
	local overloadTemplate = isConstructor and constructorOLTemplate or methodOLTemplate

	do
		local genMethods = {}

		for i,v in ipairs(methods) do
			table.insert(genMethods, v)
			while (#v.arguments >0 and v.arguments[#v.arguments].isDefault) do
				v = copyTable(v)
				table.remove(v.arguments)
				table.insert(genMethods, v)
			end
		end

		methods = genMethods
	end

	-- parse nested enum&class argument
	do
		for i,v in ipairs(methods) do
			for j,arg in ipairs(v.arguments) do
				arg.normalizedType = parseNestedName(class, arg.normalizedType)
			end
		end
	end

	local function overloads()
		local ret = {}
		for i,v in ipairs(methods) do
			v.normalizedType = parseNestedName(class, v.normalizedType)
			table.insert(ret, overloadTemplate(v))
		end
		return table.concat(ret, '\n');
	end

	return template({
			name = name,
			class = class,
			methods = methods,
			overloads = overloads
		})
end

local funcs = {}

function funcs:constructors()
	return printMethods(self, self.classname..'_constructor', self.constructorList, true)
end

local function getMethodNames(self)
	local ret = {}
	local operators = {}
	for i, v in ipairs(self.methodList) do
		if (v.access == "public") then
			local tmp = ret
			if (v.name:sub(1, 9) == "operator ") then
				tmp = operators
			end
			if (tmp[v.name]) then
				table.insert(tmp[v.name], v)
			else
				tmp[v.name] = {v}
			end
		end
	end
	for i, v in ipairs(self.slotList) do
		if (v.access == "public") then
			local tmp = ret
			if (v.name:sub(1, 9) == "operator ") then
				tmp = operators
			end
			if (tmp[v.name]) then
				table.insert(tmp[v.name], v)
			else
				tmp[v.name] = {v}
			end
		end
	end
	return ret
end

local function getExcludedMethods(self)
	local excludedMethods = config.excludedMethods[self.classname]
	if (not excludedMethods) then
		return {}
	end
	local ret = {}
	for i,v in ipairs(excludedMethods) do
		ret[v] = true
	end
	return ret
end

function funcs:methodImpls()
	local ret = {}
	local methods = getMethodNames(self)
	local excludedMethods = getExcludedMethods(self)
	for k,v in pairs(methods) do
		if (not excludedMethods[k]) then
			table.insert(ret, printMethods(self, self.classname..'_'..k, v, false))
		end
	end
	return table.concat(ret, '\n')
end

function funcs:methodTable()
	local ret = {}
	local methods = getMethodNames(self)
	local excludedMethods = getExcludedMethods(self)
	for k,v in pairs(methods) do
		if (not excludedMethods[k]) then
			table.insert(ret, '\t{"'..k..'", '..self.classname..'_'..k..'},\n')
		end
	end
	return table.concat(ret)
end

function funcs:depHeaders()
	local classes = {}
	for i,v in ipairs(self.constructorList) do
		for j,arg in ipairs(v.arguments) do
			for type in arg.type.rawName:gmatch("%w+") do
				classes[type] = true
			end
		end
	end
	for i,v in ipairs(self.methodList) do
		for j,arg in ipairs(v.arguments) do
			for type in arg.type.rawName:gmatch("%w+") do
				classes[type] = true
			end
		end
		for type in v.type.rawName:gmatch("%w+") do
			classes[type] = true
		end
	end
	local ret = {}
	local mark = {}
	for k,v in pairs(classes) do
		local cinfo = loadClassInfo(k)
		local fn = cinfo and cinfo.fileName:gsub("%\\", "/")
		if (cinfo and fn and not mark[fn] and not excludedIncludePath[fn]) then
			mark[fn] = true
			table.insert(ret, string.format("#include <%s>\n", fn))
		end

		fn = config.classIncludePath[k]
		if (fn and not mark[fn]) then
			mark[fn] = true
			table.insert(ret, string.format("#include <%s>\n", fn))
		end
	end
	return table.concat(ret)
end

local casterTemplate = loadTemplate("template/caster.cpp")
function generateCasters(self, ret, route)
	if (#route > 1) then
		table.insert(ret, casterTemplate({
				route = route,
				class = self,
			}))
	end
	for i,v in ipairs(self.superclassList) do
		if (v.access == "public") then
			table.insert(route, v.name)
			generateCasters(loadClassInfo(v.name), ret, route)
			table.remove(route)
		end
	end
end

function generateCasterList(self, ret, route)
	if (#route > 1) then
		table.insert(ret, string.format(
				'\t{"%s", %s},\n'
			, route[#route], table.concat(route, '_')))
	end
	for i,v in ipairs(self.superclassList) do
		if (v.access == "public") then
			table.insert(route, v.name)
			generateCasterList(loadClassInfo(v.name), ret, route)
			table.remove(route)
		end
	end
end

function funcs:casters()
	local ret = {}
	generateCasters(self, ret, {self.classname})
	return table.concat(ret)
end

function funcs:casterList()
	local ret = {}
	generateCasterList(self, ret, {self.classname})
	return table.concat(ret)
end

function funcs:declareInitSuperMethods()
	local ret = {}
	for i = #self.superclassList, 1, -1 do
		if (self.superclassList[i].access == "public") then
			table.insert(ret, string.format("void %s_initMethods(lua_State *L);\n", self.superclassList[i].name))
		end
	end
	return table.concat(ret)
end

function funcs:initSuperMethods()
	local ret = {}
	for i = #self.superclassList, 1, -1 do
		if (self.superclassList[i].access == "public") then
			table.insert(ret, string.format("\t%s_initMethods(L);\n", self.superclassList[i].name))
		end
	end
	return table.concat(ret)
end

local classTemplate = loadTemplate("template/class.cpp")
local function writeClassSource(packageName, class)
	class.isAbstract = isAbstractClass(class)
	class = copyTable(class)
	for k,v in pairs(funcs) do
		class[k] = class[k] or function(...)
			return v(class, ...)
		end
	end

	local fd = io.open("gen/"..packageName.."/def"..class.classname..".cpp", "w+")
	fd:write(classTemplate(class))
	fd:close()
end

print("reading class info")
local packages = readJsonFile("tmp/classList.json")

for k,classes in pairs(packages) do
	print('Package: '..k)
	local pkgdir = "gen/"..k
	path.mkdir(pkgdir)
	local validClasses = {}
	for i,class in ipairs(classes) do
		print('\tClass: '..class)
		local info = loadClassInfo(class)
		-- if (info.hasQObject and not isDerivedFromQObject(info)) then
			-- print("Warning: hasQObject but not derived from QObject.")
		-- end
		assert(info.classname=="Qt" or (not info.hasQObject) or isDerivedFromQObject(info))
		if (excludeClasses[class]) then
			print("\t\tExcluded.")
		elseif (info and info.hasQObject and info.name ~= "Qt") then
			writeClassSource(k, info)
			table.insert(validClasses, class)
		else
			print('\t\tIgnore non-QObject type.')
		end
		-- collectgarbage()
	end
	writePackageSource(k, validClasses)
end
