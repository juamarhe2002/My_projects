# This Python file uses the following encoding: utf-8
from PySide6.QtWidgets import QWidget,QLabel, QComboBox, QTableView, QPushButton, QSizePolicy, QVBoxLayout, QHBoxLayout
from PySide6.QtSql import *
import sqlite3

from CW_AddParts import CW_AddParts


class CW_Parts(QWidget):
    def __init__(self, ticketWindow):
        super().__init__()
        self.setWindowTitle("Parts Bought")
        self.win_ticketManager = ticketWindow

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.db = QSqlDatabase.addDatabase('QSQLITE')
        self.db.setDatabaseName('CW_DataBase.db')

        # try to open the database
        if not self.db.open():
            raise Error("Could not open the database")

        self.model = QSqlTableModel(self, self.db)
        self.model.setTable('parts')

        self.model.select()

        # Table view of the SQLite table
        self.partsTab = QTableView(self)
        self.partsTab.setModel(self.model)
        self.partsTab.resizeColumnsToContents()
        self.partsTab.hideColumn(0)

        # Combo Box for the available tickets
        lbl_ticketKey = QLabel("Ticket key: ")
        self.combo_ticketKey = QComboBox()
        self.set_values_cb()
        self.combo_ticketKey.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.combo_ticketKey.currentIndexChanged.connect(self.update_table)

        lay_ticketKey = QHBoxLayout()
        lay_ticketKey.addWidget(lbl_ticketKey, 1)
        lay_ticketKey.addWidget(self.combo_ticketKey, 3)

        #Buttons
        btn_addPart = QPushButton("Add Part")
        btn_addPart.clicked.connect(self.addPart_onClicked)
        btn_addPart.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_close = QPushButton("Close")
        btn_close.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_close.clicked.connect(self.close_win)

        h_lay_btn = QHBoxLayout()
        h_lay_btn.addWidget(btn_addPart)
        h_lay_btn.addWidget(btn_close)

        main_layout = QVBoxLayout()
        main_layout.addLayout(lay_ticketKey, 1)
        main_layout.addWidget(self.partsTab, 3)
        main_layout.addLayout(h_lay_btn, 1)

        self.setLayout(main_layout)

    def close_win(self):
        self.win_ticketManager.refreshTable()
        self.conn.close()
        self.db.close()
        self.close()

    def update_table(self):
        key = int(self.combo_ticketKey.currentText())
        self.model.select()
        self.model.setFilter(f"ticket_key = {key}")
        self.partsTab.setModel(self.model)
        self.partsTab.resizeColumnsToContents()
        self.partsTab.hideColumn(0)

    def set_values_cb(self):
        self.cursor.execute("SELECT key FROM tickets")
        items = self.cursor.fetchall()
        ticketList = []

        for key in items:
            ticketList.append(str(key[0])) #Append the rowids of the tickets.

        self.combo_ticketKey.addItems(ticketList)

    def addPart_onClicked(self):
        ticket_key = int(self.combo_ticketKey.currentText())
        self.win_addParts = CW_AddParts(self, ticket_key)
        self.win_addParts.show()

