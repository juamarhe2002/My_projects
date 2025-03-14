# This Python file uses the following encoding: utf-8
from PySide6 import QtGui
from PySide6.QtPrintSupport import QPrinter
from PySide6.QtWidgets import QWidget, QCheckBox, QLabel, QSizePolicy, QHBoxLayout, QVBoxLayout, QPushButton, QComboBox
import sqlite3


class CW_FinalCost(QWidget):
    def __init__(self, ticketWindow):
        super().__init__()
        self.win_ticketManager = ticketWindow

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Final Cost")

        lbl_ticketKey = QLabel("Ticket key: ")
        self.comb_ticketKey = QComboBox()
        self.comb_ticketKey.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.comb_ticketKey.currentIndexChanged.connect(self.update_chkBox)

        lay_ticketKey = QHBoxLayout()
        lay_ticketKey.addWidget(lbl_ticketKey, 1)
        lay_ticketKey.addWidget(self.comb_ticketKey, 3)

        self.chk_finalCostPaid = QCheckBox("Final cost paid by client.")
        self.chk_finalCostPaid.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        self.set_values_cb()

        # Buttons
        btn_save = QPushButton("Save")
        btn_save.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_save.clicked.connect(self.save_info)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_save)
        lay_btn.addWidget(btn_cancel)

        #Main layout
        main_layout = QVBoxLayout()
        main_layout.addLayout(lay_ticketKey, 1)
        main_layout.addWidget(self.chk_finalCostPaid, 1)
        main_layout.addLayout(lay_btn, 1)

        self.setLayout(main_layout)

    def cancel(self):
        self.conn.close()
        self.close()

    def set_values_cb(self):
        self.cursor.execute("SELECT key FROM tickets")
        items = self.cursor.fetchall()
        ticketList = []

        for key in items:
            ticketList.append(str(key[0])) #Append the rowids of the tickets.

        self.comb_ticketKey.addItems(ticketList)
        self.update_chkBox()

    def update_chkBox(self):
        selected = self.comb_ticketKey.currentText()
        self.cursor.execute("SELECT Price_paid FROM tickets WHERE key = ?", (int(selected),))
        value = self.cursor.fetchone()

        self.chk_finalCostPaid.setChecked(value[0] > 0)

    def calculate_finalCost(self):
        selected = self.comb_ticketKey.currentText()
        self.cursor.execute("SELECT * FROM parts WHERE ticket_key = ?", (int(selected),))
        parts = self.cursor.fetchall()

        finalCost = 0
        for part in parts:
            finalCost += part[4]

        return finalCost


    def save_info(self):
        if self.chk_finalCostPaid.isChecked():
            finalCost = self.calculate_finalCost()
        else:
            finalCost = 0

        selected = int(self.comb_ticketKey.currentText())
        update = (finalCost, selected)
        self.cursor.execute("UPDATE tickets SET Price_paid = ? WHERE key = ?", update)
        self.conn.commit()

        self.save_pdfDocument(selected)

        self.win_ticketManager.refreshTable()
        self.conn.close()
        self.close()

    def save_pdfDocument(self, ticket):
        filename = "Final_Cost_Ticket_"+str(ticket)+".pdf"
        printer = QPrinter(QPrinter.PrinterResolution)
        printer.setOutputFormat(QPrinter.PdfFormat)
        printer.setOutputFileName(filename)

        self.cursor.execute("SELECT * FROM tickets WHERE key = ?", (ticket,))
        ticket_info = self.cursor.fetchone()

        self.cursor.execute("SELECT * FROM parts WHERE ticket_key = ?", (ticket,))
        parts = self.cursor.fetchall()

        document = QtGui.QTextDocument()

        cursor = QtGui.QTextCursor(document)

        cursor.beginEditBlock()
        cursor.insertText(f" Final Cost of Ticket No.{ticket} ")
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.insertText(f" Time slot: {ticket_info[6]} ")
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.endEditBlock()

        cursor.beginEditBlock()
        cursor.insertText(" Parts: ")
        cursor.insertBlock()

        for part in parts:
            cursor.insertText(f"Name : {part[1]}")
            cursor.insertBlock()
            cursor.insertText(f"Amount : {part[2]}")
            cursor.insertBlock()
            cursor.insertText(f"Unit Price : {part[3]}")
            cursor.insertBlock()
            cursor.insertText(f"Total Price Part: {part[4]}")
            cursor.insertBlock()
            cursor.insertBlock()

        cursor.endEditBlock()

        final_cost = self.calculate_finalCost()
        cursor.beginEditBlock()
        cursor.insertText(f" FINAL COST OF REPAIR: {final_cost}")
        cursor.endEditBlock()

        document.print_(printer)

