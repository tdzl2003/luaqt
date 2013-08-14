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

for i,fn in ipairs(fileList) do
	local package = packageMap[fn]

	local classes = mocreader.parse(fn, {
		includePath= {QtIncludePath}
	})
	for i,v in ipairs(classes) do
		v.fileName = path.relpath(fn, QtIncludePath)
		print(v.classname, v.fileName)
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

