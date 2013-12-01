require 'QtWidgets'

local app = QApplication.new(select('#',...) + 1, {'lua', ...})

local wnd = QWidget.new()

local btn = QPushButton.new("Click me", wnd)

btn:connect("2clicked()", function ()
   print("Oow..")    
end)

wnd:show()

QApplication.exec()
