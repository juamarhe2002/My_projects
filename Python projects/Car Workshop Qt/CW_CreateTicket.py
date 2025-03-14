# This Python file uses the following encoding: utf-8
from PySide6.QtCore import QDate, QTime
from PySide6.QtWidgets import QWidget, QDateTimeEdit, QLabel, QLineEdit, QTextEdit, QSizePolicy, QHBoxLayout, QVBoxLayout, QPushButton, QMessageBox, QComboBox
import sqlite3


class CW_CreateTicket(QWidget):
    def __init__(self, ticketWindow):
        super().__init__()
        self.win_ticketManager = ticketWindow

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Create Ticket")

        # Options
        lbl_brand = QLabel("Brand: ")
        self.le_brand = QLineEdit()
        self.le_brand.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_brand = QHBoxLayout()
        lay_brand.addWidget(lbl_brand, 1)
        lay_brand.addWidget(self.le_brand, 3)

        lbl_model = QLabel("Model: ")
        self.le_model = QLineEdit()
        self.le_model.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_model = QHBoxLayout()
        lay_model.addWidget(lbl_model, 1)
        lay_model.addWidget(self.le_model, 3)

        lbl_regID = QLabel("Registration ID: ")
        self.le_regID = QLineEdit()
        self.le_regID.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_regID = QHBoxLayout()
        lay_regID.addWidget(lbl_regID, 1)
        lay_regID.addWidget(self.le_regID, 3)

        lbl_desc = QLabel("Description of problem: ")
        self.te_desc = QTextEdit()
        self.te_desc.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        lay_desc = QHBoxLayout()
        lay_desc.addWidget(lbl_desc, 1)
        lay_desc.addWidget(self.te_desc, 3)

        lbl_employee = QLabel("Employee assigned: ")
        self.cb_employee = QComboBox()
        self.set_values_cb()
        self.cb_employee.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_employee = QHBoxLayout()
        lay_employee.addWidget(lbl_employee, 1)
        lay_employee.addWidget(self.cb_employee, 3)

        lbl_timeSlot = QLabel("Time Slot: ")
        self.dte_timeSlot = QDateTimeEdit(QDate.currentDate())
        self.dte_timeSlot.setMinimumDate(QDate.currentDate())
        self.dte_timeSlot.setMinimumTime(QTime(8, 0))
        self.dte_timeSlot.setMaximumTime(QTime(16, 0))
        self.dte_timeSlot.setDisplayFormat("dd.MM.yyyy hh:mm")
        self.dte_timeSlot.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)

        lay_timeSlot = QHBoxLayout()
        lay_timeSlot.addWidget(lbl_timeSlot, 1)
        lay_timeSlot.addWidget(self.dte_timeSlot, 3)

        # Buttons
        btn_add = QPushButton("Add")
        btn_add.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_add.clicked.connect(self.addNewTicket)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_add)
        lay_btn.addWidget(btn_cancel)

        #Main layout
        main_layout = QVBoxLayout()
        main_layout.addLayout(lay_brand, 1)
        main_layout.addLayout(lay_model, 1)
        main_layout.addLayout(lay_regID, 1)
        main_layout.addLayout(lay_desc, 3)
        main_layout.addLayout(lay_employee, 1)
        main_layout.addLayout(lay_timeSlot, 1)
        main_layout.addLayout(lay_btn, 1)

        self.setLayout(main_layout)

    def set_values_cb(self):
        self.cursor.execute("SELECT * FROM employees")
        items = self.cursor.fetchall()
        employeeList = []

        for employee in items:
            employeeList.append(employee[0]) #Append the names of the employees.

        self.cb_employee.addItems(employeeList)

    def cancel(self):
        self.conn.close()
        self.close()

    def addNewTicket(self):
        brand = self.le_brand.text()
        if brand == "" or brand == " " :
            self.error_incompleteField('Brand')
            return

        model = self.le_model.text()
        if model == "" or model == " " :
            self.error_incompleteField('Model')
            return

        regID = self.le_regID.text()
        if regID == "" or regID == " " :
            self.error_incompleteField('Registration ID')
            return

        desc = self.te_desc.toPlainText()
        if desc == "" or desc == " " :
            self.error_incompleteField('Description of the problem')
            return

        employee = self.cb_employee.currentText()
        if employee == "" or employee == " " :
            self.error_incompleteField('Employee assigned')
            return

        dt_timeSlot = self.dte_timeSlot.dateTime()
        timeSlot = dt_timeSlot.toString(self.dte_timeSlot.displayFormat())

        self.cursor.execute("SELECT * FROM tickets ORDER BY key DESC LIMIT 1")
        last = self.cursor.fetchone()

        if not last:
            newKey = 0
        else:
            newKey = last[0] + 1

        ticket = (newKey, brand, model, regID, desc, employee, timeSlot)
        self.cursor.execute("INSERT INTO tickets VALUES (?,?,?, ?, ?, ?, ?, ' ', ' ', ' ', 0);", ticket)
        self.conn.commit()

        self.win_ticketManager.refreshTable()
        self.conn.close()
        self.close()

    def error_incompleteField(self, field):
        QMessageBox.critical(self, "Incomplete Field",
                        f"The following field information is missing: {field}", QMessageBox.Ok)



