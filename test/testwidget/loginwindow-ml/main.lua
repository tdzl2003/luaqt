require 'QtWidgets'
require 'luaqtml'

local LoginWindow = requireQtModule("LoginWindow").LoginWindow

local app = QApplication.new(select('#',...) + 1, {'lua', ...})

local wnd = LoginWindow.new()
wnd:show()

QApplication.exec()
