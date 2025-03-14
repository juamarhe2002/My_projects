# This Python file uses the following encoding: utf-8
from PySide6 import QtGui
from PySide6.QtPrintSupport import QPrinter
from PySide6.QtWidgets import QWidget, QCheckBox, QLabel, QLineEdit, QTextEdit, QSizePolicy, QHBoxLayout, QVBoxLayout, QPushButton, QMessageBox, QComboBox
import sqlite3


class CW_Estimate(QWidget):
    def __init__(self, ticketWindow):
        super().__init__()
        self.win_ticketManager = ticketWindow

        self.conn = sqlite3.connect('CW_DataBase.db')
        self.cursor = self.conn.cursor()

        self.setWindowTitle("Estimate")

        lbl_ticketKey = QLabel("Ticket key: ")
        self.comb_ticketKey = QComboBox()
        self.comb_ticketKey.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.comb_ticketKey.currentIndexChanged.connect(self.update_estFields)

        lay_ticketKey = QHBoxLayout()
        lay_ticketKey.addWidget(lbl_ticketKey, 1)
        lay_ticketKey.addWidget(self.comb_ticketKey, 3)

        lbl_desc = QLabel("Description: ")
        self.te_desc = QTextEdit()
        self.te_desc.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)

        lay_desc = QHBoxLayout()
        lay_desc.addWidget(lbl_desc, 1)
        lay_desc.addWidget(self.te_desc, 3)

        lbl_expCost = QLabel("Expected cost: ")
        self.le_expCost = QLineEdit()
        self.le_expCost.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        lay_expCost = QHBoxLayout()
        lay_expCost.addWidget(lbl_expCost, 1)
        lay_expCost.addWidget(self.le_expCost, 3)

        self.chk_estAccepted = QCheckBox("Estimate Accepted")
        self.chk_estAccepted.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)

        self.set_values_cb() #Setting the values of the ComboBox ticketKey.

        # Buttons
        btn_save = QPushButton("Save")
        btn_save.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_save.clicked.connect(self.save_fields)

        btn_savePDF = QPushButton("Save PDF")
        btn_savePDF.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_savePDF.clicked.connect(self.save_PDF)

        btn_cancel = QPushButton("Cancel")
        btn_cancel.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        btn_cancel.clicked.connect(self.cancel)

        lay_btn = QHBoxLayout()
        lay_btn.addWidget(btn_save)
        lay_btn.addWidget(btn_savePDF)
        lay_btn.addWidget(btn_cancel)

        #Main layout
        main_layout = QVBoxLayout()
        main_layout.addLayout(lay_ticketKey, 1)
        main_layout.addLayout(lay_desc, 3)
        main_layout.addLayout(lay_expCost, 1)
        main_layout.addWidget(self.chk_estAccepted, 1)
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
        self.update_estFields()

    def update_estFields(self):
        selected = self.comb_ticketKey.currentText()
        self.cursor.execute("SELECT * FROM tickets WHERE key = ?", (float(selected),))
        item = self.cursor.fetchone()

        self.te_desc.setText(item[7])
        self.le_expCost.setText(str(item[8]))
        self.chk_estAccepted.setChecked(item[9] == 'Yes')

    def save_PDF(self):
        if not self.chk_fields(): return

        ticket = self.comb_ticketKey.currentText()
        filename = "Estimate_Ticket_"+str(ticket)+".pdf"
        printer = QPrinter(QPrinter.PrinterResolution)
        printer.setOutputFormat(QPrinter.PdfFormat)
        printer.setOutputFileName(filename)

        description = self.te_desc.toPlainText()
        expCost = self.le_expCost.text()

        if self.chk_estAccepted.isChecked():
            estAcc = 'Yes'
        else:
            estAcc = 'No'

        document = QtGui.QTextDocument()
        cursor = QtGui.QTextCursor(document)
        cursor.beginEditBlock()
        cursor.insertText(f" Estimate of Ticket No.{ticket} ")
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.endEditBlock()

        cursor.beginEditBlock()
        cursor.insertText("Description: ")
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.insertText(description)
        cursor.insertBlock()
        cursor.insertBlock()
        cursor.endEditBlock()

        cursor.beginEditBlock()
        cursor.insertText(f"Expected Cost: ${expCost}")
        cursor.insertBlock()
        cursor.insertText(f"Estimate Accepted: {estAcc}")
        cursor.endEditBlock()

        document.print_(printer)
        self.save_fields()

    def save_fields(self):
        if not self.chk_fields(): return

        desc = self.te_desc.toPlainText()
        expCost = self.le_expCost.text()

        if self.chk_estAccepted.isChecked():
            estAcc = 'Yes'
        else:
            estAcc = 'No'


        selected = self.comb_ticketKey.currentText()
        update = (desc, float(expCost), estAcc, int(selected))
        self.cursor.execute("""UPDATE tickets
                                SET estimate_desc = ?,
                                    estimate_cost = ?,
                                    estimate_acc = ?
                                WHERE key = ?""", update)
        self.conn.commit()

        self.win_ticketManager.refreshTable()
        self.conn.close()
        self.close()

    def chk_fields(self):
        desc = self.te_desc.toPlainText()
        expCost = self.le_expCost.text()
        if desc == "" or desc == " " :
            self.error_incompleteField('Description')
            return False

        if expCost == "" or expCost == " " :
            self.error_incompleteField('Expected cost')
            return False

        return True

    def error_incompleteField(self, field):
        QMessageBox.critical(self, "Incomplete Field",
                        f"The following field information is missing: {field}", QMessageBox.Ok)



