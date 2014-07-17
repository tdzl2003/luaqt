local LuaQtHelper = require("LuaQtHelper")
require("QtWidgets")
-- local ui_LoginWindow = require("ui_LoginWindow")
local ui_LoginWindow = loadstring(require("uic").run("loginwindow.ui"))()

local LoginWindow = {
	className = "LoginWindow",
	superClass = QWidget,
}

local function newLoginWindow(mo, parent)
	local self = QWidget.newExtended(mo, parent)
	self.ui = ui_LoginWindow.setupUi(self)
	self:connect(self.ui.btn_Login, "2clicked(bool)", "1doLogin(bool)")
	self:connect(self.ui.edit_ID, "2cursorPositionChanged(int,int)", "1testPosition(int,int)")
	return self
end

LuaQtHelper.addConstructor(LoginWindow, {"QWidget*"}, newLoginWindow)

LuaQtHelper.addSignal(LoginWindow, "void", "logined", {})

LuaQtHelper.addSlot(LoginWindow, "void", "doLogin", {"bool"}, function(self, ...)
	print(...)
	self:logined()
end)

LuaQtHelper.addSlot(LoginWindow, "void", "testPosition", {"int", "int"}, function(self, ...)
	print(...)
	self:logined()
end)

LoginWindow = LuaQtHelper.defineQtClass(LoginWindow)
return LoginWindow