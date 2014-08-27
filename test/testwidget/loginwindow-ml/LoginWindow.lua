require 'QtWidgets'
require 'luaqtml'

local ui_LoginWindow = requireUI("./loginwindow.ui")

-- @luaqt
-- @class LoginWindow
-- @	extends QWidget
local LoginWindow = {}

-- @constructor __init__
-- @	argument QWidget*
-- @end constructor
function LoginWindow:__init__(parent)
	self = super(parent)
	self.ui = ui_LoginWindow.setupUi(self)
	self:connect(self.ui.btn_Login, "2clicked(bool)", "1doLogin(bool)")
	self:connect(self.ui.edit_ID, "2cursorPositionChanged(int, int)", "1testPosition(int, int)")
end

-- @signal logined
-- @	return void
-- @end signal
function LoginWindow:logined()
end

-- @slot doLogin
-- @	argument bool
-- @	return void
-- @end slot
function LoginWindow:doLogin(arg)
	self:logined()
end

-- @slot testPosition
-- @	argument int
-- @	argument int
-- @	return void
-- @end slot
function LoginWindow:testPosition(f, t)
	print(f, t)
end



-- @end class

return {
	LoginWindow = LoginWindow
}
