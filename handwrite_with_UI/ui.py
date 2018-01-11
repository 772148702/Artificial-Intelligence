# -*- coding: utf-8 -*-
import sys, os
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel
from PyQt5.QtGui import QPainter, QPen, QPixmap, QBrush
from PyQt5.QtCore import Qt
import handwrite

class HandwriteBoard(QWidget):
    '''
    widget for hand write
    '''
    def __init__(self):
        super(HandwriteBoard, self).__init__()

        self.resize(600, 400)
        self.move(200, 200)
        self.setWindowTitle("手写识别")

        self.recButton = QPushButton(self)
        self.recButton.setText("识别")
        self.recButton.setShortcut('Ctrl+R')
        self.recButton.clicked.connect(self.recognize)
        self.recButton.setToolTip("识别")
        self.recButton.move(440, 160)

        self.flashButton = QPushButton(self)
        self.flashButton.setText("重画")
        self.flashButton.setShortcut('Ctrl+Z')
        self.flashButton.clicked.connect(self.flash)
        self.flashButton.setToolTip("重画")
        self.flashButton.move(440, 220)

        self.closeButton = QPushButton(self)
        self.closeButton.setText("训练")
        self.closeButton.setShortcut('Ctrl+T')
        self.closeButton.clicked.connect(self.training)
        self.closeButton.setToolTip("训练-需要等待一段时间")
        self.closeButton.move(440, 300)

        self.showLabel = QLabel(self)
        self.showLabel.setText("这里显示信息")
        self.showLabel.setGeometry(440, 80, 200, 20)

        self.setMouseTracking(False)
        self.pos = []

        self.temp = 1

        self.bp = handwrite.Bpnet()

    def flash(self):
        self.pos.clear()
        self.update()

    def recognize(self):
        screen = QApplication.primaryScreen()

        savePix = screen.grabWindow(0, self.geometry().x()+135, self.geometry().y()+110, 200, 200)
        fileName = "sample.png"
        self.temp += 1
        savePix = savePix.scaled(28, 28)

        savePix.save(fileName, 'PNG')
        #self.showLabel.setText("guess number: " + str(number))
        #need further
        number = self.bp.inputAndTest(fileName)
        self.showLabel.setText("预测 " + str(number))

    def training(self):
        self.bp.initial()
        self.bp.train()
        self.bp.test()

    def paintEvent(self, event):
        painter = QPainter()
        painter.begin(self)
        painter.drawRect(135, 110, 200, 200)
        pen = QPen(Qt.black, 8, Qt.SolidLine)
        painter.setPen(pen)

        if len(self.pos) > 1:
            start_pos_x, start_pos_y = self.pos[0]
            for x, y in self.pos:
                if (start_pos_x, start_pos_y) == (-1, -1):
                    start_pos_x, start_pos_y = x, y
                if (x, y) != (-1, -1):
                    painter.drawLine(start_pos_x, start_pos_y, x, y)
                start_pos_x, start_pos_y = x, y
        painter.end()

    def mouseMoveEvent(self, event):

        if event.pos().x() < 0 or event.pos().x() > 420:
            return
        if event.pos().y() < 0 or event.pos().y() > 420:
            return
        self.pos.append((event.pos().x(), event.pos().y()))
        self.update()

    def mouseReleaseEvent(self, event):
        if event.pos().x() < 0 or event.pos().x() > 420:
            return
        if event.pos().y() < 0 or event.pos().y() > 420:
            return
        self.pos.append((-1, -1))
        self.update()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    board = HandwriteBoard()
    board.show()
    app.exec_()
