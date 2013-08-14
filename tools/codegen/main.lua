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
	local str = fd:read("*a")
	fd:close()
	return json.decode(str)
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

local packageTemplate = loadTemplate("template/package.cpp")
local function writePackageSource(packageName, classes)
	local fd = io.open("gen/"..packageName..".cpp", "w+")

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

local constructorTemplate = loadTemplate("template/constructor.cpp")
local constructorOLTemplate = loadTemplate("template/constructorol.cpp")
-- local methodTemplate = loadTemplate("template/method.cpp")
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

	local function overloads()
		local ret = {}
		for i,v in ipairs(methods) do
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

local classTemplate = loadTemplate("template/class.cpp")
local function writeClassSource(packageName, class)
	for k,v in pairs(funcs) do
		class[k] = class[k] or function(...)
			return v(class, ...)
		end
	end

	local fd = io.open("gen/def"..class.classname..".cpp", "w+")
	fd:write(classTemplate(class))
	fd:close()
end

print("reading class info")
local packages = readJsonFile("tmp/classList.json")

for k,classes in pairs(packages) do
	print('Package: '..k)
	writePackageSource(k, classes)
	for i,class in ipairs(classes) do
		print('\tClass: '..class)
		writeClassSource(k, readJsonFile("tmp/"..class..".json"))
		collectgarbage()
	end
end
