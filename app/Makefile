SOURCES=$(shell find . -type f -iname '*.c')
TARGET=sensor_app.out

all: $(TARGET)

$(TARGET): $(SOURCES)
	gcc $(SOURCES) -o $(TARGET) -W -Wall -Wno-unused-parameter -pthread

clean:
	rm -f $(TARGET)
