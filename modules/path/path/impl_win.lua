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

local impl = {}
local ffi = require("ffi")
local C = ffi.C

if (jit.arch=="x64") then
	ffi.cdef[[
		typedef __int64        intptr_t;
	]]
elseif (jit.arch=="x86") then
	ffi.cdef[[
		typedef int            intptr_t;
	]]
else
	error("Unsupported architecture"..jit.arch)
end

ffi.cdef[[
    void* malloc(size_t size);
    void free(void* data);
    char* _getcwd(char* buffer, int maxlen);


	typedef unsigned int _dev_t;        /* device code */
	typedef unsigned short _ino_t;      /* i-node number (not used on DOS) */
	typedef __int64 __time64_t;     /* 64-bit time value */

    typedef struct {
        _dev_t     st_dev;
        _ino_t     st_ino;
        unsigned short st_mode;
        short      st_nlink;
        short      st_uid;
        short      st_gid;
        _dev_t     st_rdev;
        __int64    st_size;
        __time64_t st_atime;
        __time64_t st_mtime;
        __time64_t st_ctime;
    } _stat64info;

	int __cdecl _stat64(const char * _Name, _stat64info * _Stat);

	extern int * __cdecl _errno(void);

	typedef struct  {
        unsigned    attrib;
        __time64_t  time_create;    /* -1 for FAT file systems */
        __time64_t  time_access;    /* -1 for FAT file systems */
        __time64_t  time_write;
        __int64     size;
        char        name[260];
	} __finddata64_t;

	intptr_t __cdecl _findfirst64(const char * _Filename, __finddata64_t * _FindData);
	int __cdecl _findnext64(intptr_t _FindHandle, __finddata64_t * _FindData);
]]

function impl.current()
    local buff = C.malloc(256)
    local ret = ffi.string(C._getcwd(buff, 256))
    C.free(buff)	
    return ret
end

local function errno()
	return C._errno()[0]
end

function impl.stat(fn)
	local ret = ffi.new("_stat64info[1]")
	local iret = C._stat64(fn, ret);
	if (iret == 0) then
		return ret[0]
	end

	return nil, errno()
end
local stat = impl.stat

function impl.isdir(fn)
	local st = stat(fn)
	return st and (bit.band(st.st_mode, 0x4000) ~= 0)
end

function impl.exists(fn)
	return stat(fn) and true or false
end

local function listFile(dir, filter)
	local pattern = require("path").normjoin(dir, "*")
	local ret = {}

	local c_file = ffi.new("__finddata64_t[1]")

	local handle = C._findfirst64(pattern, c_file);
	if (handle == -1) then
		return ret;
	end

	while true do
		if (filter(c_file)) then
			table.insert(ret, ffi.string(c_file[0].name))
		end

		if (C._findnext64(handle, c_file) ~= 0) then
			return ret
		end
	end
end

function impl.listAll(dir)
	return listFile(dir, function()
		return true
	end)
end

function impl.listFiles(dir)
	return listFile(dir, function(cf)
		return bit.band(cf[0].attrib, 0x10) == 0
	end)
end

function impl.listSubdirs(dir)
	return listFile(dir, function(cf)
		return bit.band(cf[0].attrib, 0x10) ~= 0
	end)
end

return impl