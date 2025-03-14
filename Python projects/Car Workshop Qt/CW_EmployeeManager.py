# This Python file uses the following encoding: utf-8
from PySide6 import QtCore
from PySide6.QtWidgets import QWidget, QTableView, QPushButton, QSizePolicy, QVBoxLayout, QHBoxLayout
from PySide6.QtSql import *

from CW_AddEmployee import CW_AddEmployee
from CW_RemoveEmployee import CW_RemoveEmployee


class CW_EmployeeManager(QWidget):
    def __init__(self, mainWindow):
        super().__init__()
        self.win_main = mainWindow

        self.setWindowTitle("Manage Employees")

        self.db = QSqlDatabase.addDatabase('QSQLITE')
        self.db.setDatabaseName('CW_DataBase.db')

        # try to open the database
        if not self.db.open():
            raise Error("Could not open the database")

        self.model = QSqlTableModel(self, self.db)
        self.model.setTable('employees')

        self.model.select()

        # Table view of the SQLite table
        self.employeeTab = QTableView(self)
        self.employeeTab.setModel(self.model)
        self.employeeTab.resizeColumnsToContents()

        #Buttons
        btn_addEmployee = QPushButton("Add Employee")
        btn_addEmployee.clicked.connect(self.addEmployee_onClicked)
        btn_addEmployee.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_deleteEmployee = QPushButton("Remove Employee")
        btn_deleteEmployee.clicked.connect(self.deleteEmployee_onClicked)
        btn_deleteEmployee.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_close = QPushButton("Close")
        btn_close.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_close.clicked.connect(self.close_onClicked)

        h_lay_btn = QHBoxLayout()
        h_lay_btn.addWidget(btn_addEmployee)
        h_lay_btn.addWidget(btn_deleteEmployee)
        h_lay_btn.addWidget(btn_close)

        main_layout = QVBoxLayout()
        main_layout.addWidget(self.employeeTab, 3)
        main_layout.addLayout(h_lay_btn, 1)

        self.setLayout(main_layout)

    def addEmployee_onClicked(self):
        self.win_addEmployee = CW_AddEmployee(self)
        self.win_addEmployee.show()

    def deleteEmployee_onClicked(self):
        self.win_remEmployee = CW_RemoveEmployee(self)
        self.win_remEmployee.show()

    def refreshTable(self):
        self.model.select()
        self.employeeTab.setModel(self.model)
        self.employeeTab.resizeColumnsToContents()

    def close_onClicked(self):
        self.win_main.set_values_cb()
        self.win_main.set_timeSlots()
        self.db.close()
        self.close()





