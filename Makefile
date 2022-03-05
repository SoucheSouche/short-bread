SRC_DIR=./src
LIB=short-bread
TARGET=lib${LIB}.so
BUILD_DIR=tmp

CXX=g++ -g

TARGET_SRC += $(wildcard $(SRC_DIR)/*.cpp)
TARGET_SRC += $(wildcard $(SRC_DIR)/**/*.cpp)

TARGET_OBJ := $(notdir $(TARGET_SRC:.cpp=.o))
TARGET_OBJ := $(addprefix $(BUILD_DIR)/,$(TARGET_OBJ))

#extend the global setting
override CXXFLAGS+=-std=c++17 -Wall -Wextra -Wconversion -pedantic -fpic

CURL_DIR=/usr/bin/curl

override INC+=-I$(SRC_DIR)
override INC+=-I$(SRC_DIR)/dictionnary
override INC+=-I$(SRC_DIR)/httpClient

override LDFLAGS+=-lcurl
override LDFLAGS+=-shared

.PHONY: all clean install uninstall deb

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INC) $^ -o $@ 

$(BUILD_DIR)/%.o: $(SRC_DIR)/**/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INC) $^ -o $@ 

$(TARGET): $(TARGET_OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

install:
	install -Dm 755 $(TARGET) $(ROOTFS)/usr/lib/$(TARGET)

install_headers:
	find "${SRC_DIR}" -type f -name "*.h" -print | sed 's/^.\/[^/\]*/./g' | xargs -I {} install -Dvm 644 "${SRC_DIR}/{}" "$(ROOTFS)/usr/include/${LIB}/{}"

uninstall:	
	rm -rf $(ROOTFS)/usr/lib/$(TARGET)

#remove build directory and other generated 
clean:
	$(RM) -rf $(TARGET) $(BUILD_DIR)
