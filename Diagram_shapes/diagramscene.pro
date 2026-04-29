QT += widgets

HEADERS	    =   mainwindow.h \
                diagramscene.h

SOURCES	    =   mainwindow.cpp \
		main.cpp \
		diagramscene.cpp


# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/diagramscene
INSTALLS += target
