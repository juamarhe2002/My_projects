# This Python file uses the following encoding: utf-8
from PySide6.QtWidgets import QWidget, QMessageBox, QAbstractItemView, QPushButton, QSizePolicy, QTableView, QHBoxLayout, QVBoxLayout
from PySide6.QtSql import *

from CW_CreateTicket import CW_CreateTicket
from CW_DeleteTicket import CW_DeleteTicket
from CW_Estimate import CW_Estimate
from CW_Parts import CW_Parts
from CW_FinalCost import CW_FinalCost

class CW_TicketManager(QWidget):
    def __init__(self, mainWindow):
        super().__init__()
        self.setWindowTitle("Ticket Manager")

        self.mainWindow = mainWindow

        self.db = QSqlDatabase.addDatabase('QSQLITE')
        self.db.setDatabaseName('CW_DataBase.db')

        # try to open the database
        if not self.db.open():
            raise Error("Could not open the database")

        self.model = QSqlTableModel(self, self.db)

        query = QSqlQuery()
        query.exec_('select * from tickets')
        self.model.setQuery(query)

        self.model.select()

        # Table view of the SQLite table
        self.ticketTab = QTableView(self)
        self.ticketTab.setModel(self.model)
        self.ticketTab.resizeColumnsToContents()
        self.ticketTab.hideColumn(7)
        self.ticketTab.hideColumn(8)

        #Buttons
        btn_createTicket = QPushButton("Create")
        btn_createTicket.clicked.connect(self.createTicket_onClicked)
        btn_createTicket.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_deleteTicket = QPushButton("Delete")
        btn_deleteTicket.clicked.connect(self.deleteTicket_onClicked)
        btn_deleteTicket.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_estimate = QPushButton("Estimate")
        btn_estimate.clicked.connect(self.estimate_onClicked)
        btn_estimate.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_listParts = QPushButton("List of Parts")
        btn_listParts.clicked.connect(self.listParts_onClicked)
        btn_listParts.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_finalCost = QPushButton("Final cost")
        btn_finalCost.clicked.connect(self.finalCost_onClicked)
        btn_finalCost.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        btn_back = QPushButton("Go Back")
        btn_back.clicked.connect(self.back_onClicked)
        btn_back.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        h_lay_btn = QHBoxLayout() # Button layout
        h_lay_btn.addWidget(btn_createTicket)
        h_lay_btn.addWidget(btn_deleteTicket)
        h_lay_btn.addWidget(btn_estimate)
        h_lay_btn.addWidget(btn_listParts)
        h_lay_btn.addWidget(btn_finalCost)
        h_lay_btn.addWidget(btn_back)

        main_layout = QVBoxLayout()
        main_layout.addWidget(self.ticketTab, 6)
        main_layout.addLayout(h_lay_btn, 1)

        self.setLayout(main_layout)

    def createTicket_onClicked(self):
        self.win_createTicket = CW_CreateTicket(self)
        self.win_createTicket.show()

    def deleteTicket_onClicked(self):
        self.win_deleteTicket = CW_DeleteTicket(self)
        self.win_deleteTicket.show()

    def estimate_onClicked(self):
        self.win_estimate = CW_Estimate(self)
        self.win_estimate.show()

    def listParts_onClicked(self):
        self.win_parts = CW_Parts(self)
        self.win_parts.show()

    def refreshTable(self):
        query = QSqlQuery()
        query.exec_('select * from tickets')
        self.model.setQuery(query)

        self.model.select()
        self.ticketTab.setModel(self.model)
        self.ticketTab.resizeColumnsToContents()
        self.ticketTab.hideColumn(7)
        self.ticketTab.hideColumn(8)

    def back_onClicked(self):
        self.mainWindow.set_values_cb()
        self.mainWindow.set_timeSlots()
        self.mainWindow.show()
        self.db.close()
        self.close()

    def finalCost_onClicked(self):
        self.win_finalCost = CW_FinalCost(self)
        self.win_finalCost.show()
