SOURCES=$(shell find . -type f -iname '*.c')
TARGET=driver_test_app.out

all: $(TARGET)

$(TARGET): $(SOURCES)
	gcc $(SOURCES) -o $(TARGET) -W -Wall -Wno-unused-parameter

clean:
	rm -f $(TARGET)
