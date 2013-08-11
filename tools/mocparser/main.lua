local path = require("path")
local mocreader = require("mocreader")
local json = require("json")

_G.QtPath = "C:\\Qt\\Qt5.1.0x86\\5.1.0\\msvc2012"
_G.QtIncludePath = path.normjoin(QtPath, "include")

local fileList = {}
local packageMap = {}

local classList = {}

print("Listing Qt header files...")
do
	for i,package in ipairs(path.listSubdirs(_G.QtIncludePath)) do
		if (package ~= '.' and package ~= '..') then
			local packageBase = path.normjoin(QtIncludePath, package)
			classList[package] = {}

			for j,file in ipairs(path.listFiles(packageBase)) do
				local srcPath = path.normjoin(packageBase, file)
				packageMap[srcPath] = package
				table.insert(fileList, srcPath)
			end
		end
	end
end

print("parsing...")

for i,v in ipairs(fileList) do
	local package = packageMap[v]

	local classes = mocreader.parse(v, {
		includePath= {QtIncludePath}
	})
	for i,v in ipairs(classes) do
		print(v.classname)
		table.insert(classList[package], v.classname)
		local fd = io.open(path.normalize("tmp/"..v.classname..".json"), "w")
		fd:write(json.encode(v));
		fd:close()
	end

end

local fd = io.open("tmp/classList.json", "w")
fd:write(json.encode(classList))
fd:close()

print("done.")

