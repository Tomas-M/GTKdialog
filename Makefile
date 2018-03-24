GTKDIALOG_CFLAGS	:= `pkg-config --cflags gtk+-2.0`
GTKDIALOG_LDFLAGS	:= `pkg-config --libs gtk+-2.0`
GTKDIALOG_OBJECTS	:= gtkdialog.o
CFLAGS	:= -Wall $(GTKDIALOG_CFLAGS)

all: $(GTKDIALOG_OBJECTS)
	$(CC) -o gtkdialog $(GTKDIALOG_OBJECTS) $(GTKDIALOG_LDFLAGS)

clean:
	rm $(GTKDIALOG_OBJECTS)

