require 'QtWidgets'

local LoginWindow = require("LoginWindow")

local app = QApplication.new(select('#',...) + 1, {'lua', ...})

local wnd = LoginWindow.new()
wnd:show()

QApplication.exec()
