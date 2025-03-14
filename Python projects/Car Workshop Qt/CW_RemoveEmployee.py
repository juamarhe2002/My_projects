# This Python file uses the following encoding: utf-8
from PySide6.QtWidgets import QWidget, QComboBox, QLabel, QLineEdit, QSizePolicy, QHBoxLayout, QPushButton, QVBoxLayout, QMessageBox
import sqlite3


class CW_RemoveEmployee(QWidget):
    def __init__(self, employeeWindow):
        super().__init__()
        self.win_employee = employeeWindow
        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Remove Employee")

        lbl_name = QLabel("Name of the Employee: ")
        self.cb_name = QComboBox()
        self.set_values_cb()
        self.cb_name.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_name = QHBoxLayout()
        lay_name.addWidget(lbl_name, 1)
        lay_name.addWidget(self.cb_name, 2)

        btn_rem = QPushButton("Remove")
        btn_rem.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_rem.clicked.connect(self.removeEmployee)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_rem)
        lay_btn.addWidget(btn_cancel)

        main_lay = QVBoxLayout()
        main_lay.addLayout(lay_name)
        main_lay.addLayout(lay_btn)

        self.setLayout(main_lay)

    def cancel(self):
        self.conn.close()
        self.close()

    def set_values_cb(self):
        self.cursor.execute("SELECT * FROM employees")
        items = self.cursor.fetchall()
        employeeNameList = []

        for employeeName in items:
            employeeNameList.append(employeeName[0]) #Append the names of the employees.

        self.cb_name.addItems(employeeNameList)

    def removeEmployee(self):
        name = self.cb_name.currentText()

        if self.chk_ticketsEmployee(name):
            self.error_activeTickets()
            return

        self.cursor.execute("DELETE from employees WHERE name = ?", (name,))
        self.conn.commit()

        self.win_employee.refreshTable()
        self.conn.close()
        self.close()

    def chk_ticketsEmployee(self, nameEmployee):
        self.cursor.execute("SELECT 1 FROM tickets WHERE employee = ?", (nameEmployee,))
        record = self.cursor.fetchone()
        if record:
            return True
        return False

    def error_activeTickets(self):
        QMessageBox.critical(self, "The employee has active tickets",
                        "The selected employee has currently active tikets to work on.", QMessageBox.Ok)
