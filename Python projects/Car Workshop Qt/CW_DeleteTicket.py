# This Python file uses the following encoding: utf-8
from PySide6.QtWidgets import QWidget, QLabel, QLineEdit, QComboBox, QSizePolicy, QHBoxLayout, QPushButton, QVBoxLayout
import sqlite3



class CW_DeleteTicket(QWidget):
    def __init__(self, ticketWindow):
        super().__init__()
        self.win_ticketManager = ticketWindow

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Delete Ticket")

        lbl_ticket = QLabel("Ticket key: ")
        self.comb_ticket = QComboBox()
        self.set_values_cb()
        self.comb_ticket.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_ticket = QHBoxLayout()
        lay_ticket.addWidget(lbl_ticket, 1)
        lay_ticket.addWidget(self.comb_ticket, 2)

        btn_del = QPushButton("Delete")
        btn_del.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_del.clicked.connect(self.deleteTicket)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_del)
        lay_btn.addWidget(btn_cancel)

        main_lay = QVBoxLayout()
        main_lay.addLayout(lay_ticket)
        main_lay.addLayout(lay_btn)

        self.setLayout(main_lay)

    def cancel(self):
        self.conn.close()
        self.close()

    def set_values_cb(self):
        self.cursor.execute("SELECT key FROM tickets")
        items = self.cursor.fetchall()
        ticketList = []

        for key in items:
            ticketList.append(str(key[0])) #Append the rowids of the tickets.

        self.comb_ticket.addItems(ticketList)

    def deleteTicket(self):
        ticketKey = int(self.comb_ticket.currentText())

        #Removing the parts related to the ticket.
        self.cursor.execute("DELETE from parts WHERE ticket_key = ?", (ticketKey,))
        self.conn.commit()

        #Removing the ticket.
        self.cursor.execute("DELETE from tickets WHERE key = ?", (ticketKey,))
        self.conn.commit()

        self.win_ticketManager.refreshTable()
        self.conn.close()
        self.close()
