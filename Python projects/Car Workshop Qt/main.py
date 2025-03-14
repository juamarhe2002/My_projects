# This Python file uses the following encoding: utf-8
import sys
from PySide6.QtWidgets import QApplication
import sqlite3

from CW_MainWindow import CW_MainWindow

def create_CWDatabase():
    conn = sqlite3.connect('CW_DataBase.db')

    cursor = conn.cursor()

    cursor.execute("""CREATE TABLE IF NOT EXISTS tickets (
                        key integer,
                        Brand text,
                        Model text,
                        Reg_ID text,
                        Description text,
                        Employee text,
                        Time_slots text,
                        estimate_desc text DEFAULT " ",
                        estimate_cost real DEFAULT 0,
                        estimate_acc text DEFAULT " ",
                        Price_paid real DEFAULT 0
                    )""")
    conn.commit()

    cursor.execute("""CREATE TABLE IF NOT EXISTS employees (
                        name text,
                        price_hour real
                    )""")
    conn.commit()

    cursor.execute("""CREATE TABLE IF NOT EXISTS parts (
                        ticket_key integer,
                        name text,
                        amount integer,
                        unit_price real,
                        total_price real
                    )""")
    conn.commit()

    conn.close()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    create_CWDatabase()

    window = CW_MainWindow(app)
    window.show()

    sys.exit(app.exec())

