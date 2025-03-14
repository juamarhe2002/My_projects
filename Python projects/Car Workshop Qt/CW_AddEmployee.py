# This Python file uses the following encoding: utf-8
from PySide6.QtWidgets import QWidget, QLabel, QLineEdit, QSizePolicy, QHBoxLayout, QVBoxLayout, QPushButton, QMessageBox
import sqlite3

class CW_AddEmployee(QWidget):
    def __init__(self, win_employeeManager):
        super().__init__()
        self.win_employee = win_employeeManager

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Add Employee")

        lbl_name = QLabel("Name of the Employee: ")
        self.le_name = QLineEdit()
        self.le_name.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_name = QHBoxLayout()
        lay_name.addWidget(lbl_name, 1)
        lay_name.addWidget(self.le_name, 3)

        lbl_priceHour = QLabel("Price per Hour: ")
        self.le_priceHour = QLineEdit()
        self.le_priceHour.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_priceHour = QHBoxLayout()
        lay_priceHour.addWidget(lbl_priceHour, 1)
        lay_priceHour.addWidget(self.le_priceHour, 3)

        btn_add = QPushButton("Add")
        btn_add.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_add.clicked.connect(self.addNewEmployee)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_add)
        lay_btn.addWidget(btn_cancel)

        main_lay = QVBoxLayout()
        main_lay.addLayout(lay_name)
        main_lay.addLayout(lay_priceHour)
        main_lay.addLayout(lay_btn)

        self.setLayout(main_lay)

    def cancel(self):
        self.conn.close()
        self.close()

    def addNewEmployee(self):
        name = self.le_name.text()
        priceHour = self.le_priceHour.text()
        if name == "" or name == " ":
            self.error_infoNameIncomplete()
            return

        if self.chk_employeeExists(name):
            self.error_employeeExists()
            return

        if not self.chk_num(priceHour):
            self.error_infoIncorrectNum()
            return

        employee = (name, float(priceHour))
        self.cursor.execute("INSERT INTO employees VALUES (?,?);", employee)
        self.conn.commit()

        self.conn.close()
        self.win_employee.refreshTable()
        self.close()

    def error_infoNameIncomplete(self):
        QMessageBox.critical(self, "Incomplete Name",
                        "The name of the new employee is empty", QMessageBox.Ok)

    def chk_employeeExists(self,nameEmployee):
        self.cursor.execute("SELECT 1 FROM employees WHERE name = ?", (nameEmployee,))
        record = self.cursor.fetchone()
        if record:
            return True
        return False

    def error_employeeExists(self):
        QMessageBox.critical(self, "The employee already exists",
                        "The name of the new employee already exixts on the list", QMessageBox.Ok)

    def chk_num(self, priceHour):
        try:
            float(priceHour)
            return True
        except(ValueError):
            return False

    def error_infoIncorrectNum(self):
        QMessageBox.critical(self, "Incorrect Number",
                    "The format of the price per hour value is incorrect ", QMessageBox.Ok)






