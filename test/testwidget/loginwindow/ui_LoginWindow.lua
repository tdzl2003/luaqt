local ui_LoginWindow = {}

function ui_LoginWindow.setupUi(self)
	if (self:objectName() == "") then
		self:setObjectName("LoginWindow")
	end
	self:resize(400, 300)
	local verticleLayout = QVBoxLayout.new(self)
	verticleLayout:setSpacing(6)
	verticleLayout:setContentsMargins(11, 11, 11, 11);
	verticleLayout:setObjectName("verticleLayout")
	local gridLayout = QGridLayout.new()
	gridLayout:setSpacing(6)
	gridLayout:setObjectName("gridLayout")
	gridLayout:setVerticalSpacing(48);
	local label_2 = QLabel.new(self)
	label_2:setObjectName("label_2")

	gridLayout:addWidget(label_2, 1, 0, 1, 1)

	local edit_Pwd = QLineEdit.new(self)
	edit_Pwd:setObjectName("edit_Pwd")
	edit_Pwd:setEchoMode(2)

	gridLayout:addWidget(edit_Pwd, 1, 1, 1, 1)

	local edit_ID = QLineEdit.new(self)
	edit_ID:setObjectName("edit_ID")

	gridLayout:addWidget(edit_ID, 0, 1, 1, 1)

	local label = QLabel.new(self)
	label:setObjectName("label")

	gridLayout:addWidget(label, 0, 0, 1, 1)

	local btn_Login = QPushButton.new(self)
	btn_Login:setObjectName("btn_Login")

	gridLayout:addWidget(btn_Login, 2, 0, 1, 2)

	verticleLayout:addLayout(gridLayout)

	QWidget.setTabOrder(edit_ID, edit_Pwd)
	QWidget.setTabOrder(edit_Pwd, btn_Login)

	local ui = {
		verticleLayout = verticleLayout,
		gridLayout = gridLayout,
		label_2 = label_2,
		edit_Pwd = edit_Pwd,
		edit_ID = edit_ID,
		label = label,
		btn_Login = btn_Login,
	}

	ui_LoginWindow.retranslateUi(self, ui)

	return ui
end

function ui_LoginWindow.retranslateUi(self, ui)
	self:setWindowTitle("Login")
	ui.label_2:setText("Passwd")
	ui.label:setText("ID")
	ui.btn_Login:setText("Login")
end

return ui_LoginWindow
