local LuaQtHelper = require("LuaQtHelper")
require("QtWidgets")
local ui_LoginWindow = require("ui_LoginWindow")

local LoginWindow = {
	className = "LoginWindow",
	superClass = QWidget,
}

local function newLoginWindow(mo, parent)
	local self = QWidget.newExtended(mo, parent)
	self.ui = ui_LoginWindow.setupUi(self)
	self:connect(self.ui.btn_Login, "2clicked()", "1doLogin()")
	return self
end

LuaQtHelper.addConstructor(LoginWindow, {"QWidget*"}, newLoginWindow)

LuaQtHelper.addSignal(LoginWindow, "void", "logined", {})

LuaQtHelper.addSlot(LoginWindow, "void", "doLogin", {}, function(self)
	self:logined()
	self:close()
end)

LoginWindow = LuaQtHelper.defineQtClass(LoginWindow)
return LoginWindow