SRC = ./NiRecorder.cpp
CPPFLAGS = -Dlinux -I../../Include -std=c++11
LDFLAGS = -L../../Lib -lOpenNI

LOCAL_TARGET = NiRecorder

all: $(LOCAL_TARGET)

$(LOCAL_TARGET): $(SRC)
	$(CXX) $(SRC) $(CPPFLAGS) $(LDFLAGS) -o $@

clean:
	rm -rf $(LOCAL_TARGET)
