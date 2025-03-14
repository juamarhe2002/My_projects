# This Python file uses the following encoding: utf-8
from PySide6.QtWidgets import QWidget, QLabel, QLineEdit, QSizePolicy, QHBoxLayout, QVBoxLayout, QPushButton
import sqlite3

class CW_AddParts(QWidget):
    def __init__(self, partsWindow, ticket_key):
        super().__init__()
        self.win_parts = partsWindow
        self.ticket_key = ticket_key

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Add Part")

        lbl_name = QLabel("Name / Short description: ")
        self.le_name = QLineEdit()
        self.le_name.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_name = QHBoxLayout()
        lay_name.addWidget(lbl_name)
        lay_name.addWidget(self.le_name)

        lbl_amount = QLabel("Amount: ")
        self.le_amount = QLineEdit()
        self.le_amount.editingFinished.connect(self.calculate_total)
        self.le_amount.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_amount = QHBoxLayout()
        lay_amount.addWidget(lbl_amount)
        lay_amount.addWidget(self.le_amount)

        lbl_uprice = QLabel("Unit price ($): ")
        self.le_uprice = QLineEdit()
        self.le_uprice.editingFinished.connect(self.calculate_total)
        self.le_uprice.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_uprice = QHBoxLayout()
        lay_uprice.addWidget(lbl_uprice)
        lay_uprice.addWidget(self.le_uprice)

        lbl_total = QLabel("Total price ($): ")
        self.lble_total = QLabel('0')

        lay_total = QHBoxLayout()
        lay_total.addWidget(lbl_total)
        lay_total.addWidget(self.lble_total)

        btn_add = QPushButton("Add")
        btn_add.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_add.clicked.connect(self.addNewPart)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_add)
        lay_btn.addWidget(btn_cancel)

        main_lay = QVBoxLayout()
        main_lay.addLayout(lay_name)
        main_lay.addLayout(lay_amount)
        main_lay.addLayout(lay_uprice)
        main_lay.addLayout(lay_total)
        main_lay.addLayout(lay_btn)

        self.setLayout(main_lay)

    def cancel(self):
        self.conn.close()
        self.close()

    def calculate_total(self):
        amount = self.le_amount.text()
        uprice = self.le_uprice.text()

        try:
            amount_num = int(amount)
            uprice_num = float(uprice)
        except(ValueError):
            return

        total = str(amount_num * uprice_num)
        self.lble_total.setText(total)

    def addNewPart(self):
        name = self.le_name.text()
        amount = self.le_amount.text()
        uprice = self.le_uprice.text()
        total = self.lble_total.text()

        part = (self.ticket_key, name, amount, uprice, total)
        self.cursor.execute("INSERT INTO parts VALUES (?,?,?,?,?);", part)
        self.conn.commit()

        self.win_parts.update_table()
        self.conn.close()
        self.close()


