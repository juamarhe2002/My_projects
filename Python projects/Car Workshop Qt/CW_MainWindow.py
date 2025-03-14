# This Python file uses the following encoding: utf-8
from PySide6 import QtGui
from PySide6.QtPrintSupport import QPrinter
from PySide6.QtCore import QDate
from PySide6.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QCalendarWidget, QSizePolicy, QComboBox, QLabel, QTableWidget, QAbstractScrollArea
import sqlite3

from CW_EmployeeManager import CW_EmployeeManager
from CW_TicketManager import CW_TicketManager


class CW_MainWindow(QWidget):
    def __init__(self, app):
        self.app = app
        super().__init__()
        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Car Workshop")

        btnEmployees = QPushButton("Manage Employees")
        btnEmployees.clicked.connect(self.manage_employees)
        btnEmployees.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btnTickets = QPushButton("Tickets")
        btnTickets.clicked.connect(self.manage_tickets)
        btnTickets.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btnCalendar = QPushButton("Calendar")
        btnCalendar.clicked.connect(self.save_calendar)
        btnCalendar.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_close = QPushButton("Close App")
        btn_close.clicked.connect(self.close_app)
        btn_close.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        v_lay_btn = QVBoxLayout()
        v_lay_btn.addWidget(btnEmployees)
        v_lay_btn.addWidget(btnTickets)
        v_lay_btn.addWidget(btnCalendar)
        v_lay_btn.addWidget(btn_close)

        lbl_employee = QLabel("Employee: ")

        self.cb_employee = QComboBox(self)
        self.set_values_cb()
        self.cb_employee.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.cb_employee.currentIndexChanged.connect(self.set_timeSlots)

        h_lay_combo = QHBoxLayout()
        h_lay_combo.addWidget(lbl_employee, 1)
        h_lay_combo.addWidget(self.cb_employee, 2)

        #Table of Time slots
        self.timeTable = QTableWidget(9, 2, self)

        slots = ["   8:00 - 9:00 ",
                 "  9:00 - 10:00 ",
                 " 10:00 - 11:00 ",
                 " 11:00 - 12:00 ",
                 " 12:00 - 13:00 ",
                 " 13:00 - 14:00 ",
                 " 14:00 - 15:00 ",
                 " 15:00 - 16:00 ",
                 " 16:00 - 17:00 "
                ]
        i = -1
        for slot in slots:
            i+=1
            self.timeTable.setCellWidget(i, 0, QLabel(slot))
            self.timeTable.setCellWidget(i, 1, QLabel(" no info "))

        self.timeTable.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.timeTable.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContents)
        self.timeTable.resizeColumnsToContents()

        # Layout Displaying the time-slots for the employees.
        v_lay_time = QVBoxLayout()
        v_lay_time.addLayout(h_lay_combo)
        v_lay_time.addWidget(self.timeTable)

        self.calendar = QCalendarWidget(self)
        self.calendar.setMinimumDate(QDate.currentDate())
        self.calendar.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        self.calendar.selectionChanged.connect(self.set_timeSlots)

        main_layout = QHBoxLayout()
        main_layout.addLayout(v_lay_btn, 1)
        main_layout.addLayout(v_lay_time, 3)
        main_layout.addWidget(self.calendar, 4)

        self.setLayout(main_layout)

    def set_timeSlots(self):
        employee = self.cb_employee.currentText()
        if employee == "": # Checks if there are employees
            i = 0
            while i < 9:
                self.timeTable.setCellWidget(i, 1, QLabel(" no info "))
                i+=1

            self.timeTable.resizeColumnsToContents()
            return

        currday = self.calendar.selectedDate()
        currday_str = currday.toString("dd.MM.yyyy")

        i = 0
        while i < 9: #Sets the default availability.
            self.timeTable.setCellWidget(i, 1, QLabel(" available "))
            i+=1

        self.cursor.execute("SELECT Time_slots FROM tickets WHERE Employee = ?", (employee,))
        busyDayTimeList = self.cursor.fetchall()

        for busyDayTime in busyDayTimeList:
            day_time = busyDayTime[0].split()

            if day_time[0] == currday_str:
                hour = day_time[1].split(':')
                numdiff = int(hour[0]) - 8

                self.timeTable.setCellWidget(numdiff, 1, QLabel(" busy "))

        self.timeTable.resizeColumnsToContents()

    def set_values_cb(self):
        self.cursor.execute("SELECT * FROM employees")
        items = self.cursor.fetchall()
        employeeNameList = []

        for employeeName in items:
            employeeNameList.append(employeeName[0]) #Append the names of the employees.

        self.cb_employee.clear()
        self.cb_employee.addItems(employeeNameList)

    def manage_employees(self):
        self.win_employeeManager = CW_EmployeeManager(self)
        self.win_employeeManager.show()

    def manage_tickets(self):
        self.win_ticketManager = CW_TicketManager(self)
        self.win_ticketManager.show()
        self.close()

    def close_app(self):
        self.conn.close()
        self.app.quit()

    def save_calendar(self):
        employee = self.cb_employee.currentText()
        filename = "Calendar_Employee_"+employee+".pdf"
        printer = QPrinter(QPrinter.PrinterResolution)
        printer.setOutputFormat(QPrinter.PdfFormat)
        printer.setOutputFileName(filename)

        document = QtGui.QTextDocument()
        cursor = QtGui.QTextCursor(document)
        cursor.beginEditBlock()
        cursor.insertText(f"Calendar of employee: {employee} ")
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.endEditBlock()

        cursor.insertTable(9, 2)

        for i in range(9):
            for j in range(2):
                lbl = self.timeTable.cellWidget(i, j)
                cursor.insertText(lbl.text())
                cursor.movePosition(QtGui.QTextCursor.NextCell)


        document.print_(printer)


