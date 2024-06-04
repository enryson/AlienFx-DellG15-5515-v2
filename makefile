# Nome do projeto
PROJECT_NAME_CLI := alienfx-cli
PROJECT_NAME_GUI := alienfx-gui

# Diretórios
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
LIB_DIR := lib
EXTRA_DIR := extra

# Fontes e cabeçalhos
SOURCES_CLI := $(SRC_DIR)/main.cpp
SOURCES_GUI := $(SRC_DIR)/gui.cpp
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
GLADE_FILE := $(SRC_DIR)/layout.glade
DESKTOP_FILE := $(EXTRA_DIR)/AlienFx.desktop
ICONS_DIR := $(EXTRA_DIR)/ui/icons

# Compiler e flags
CXX := g++
CXXFLAGS := -std=c++17 -I$(INCLUDE_DIR) `pkg-config --cflags libusb-1.0 gtkmm-3.0`
LDFLAGS := `pkg-config --libs libusb-1.0 gtkmm-3.0`

# Diretórios de instalação
PREFIX := /usr/local
BINDIR := $(PREFIX)/bin
DATADIR := $(PREFIX)/share/$(PROJECT_NAME_GUI)
ICONSDIR := $(DATADIR)/icons

# Tamanhos de ícones suportados
ICON_SIZES := 16x16 24x24 32x32 48x48 64x64 96x96 128x128 256x256 512x512 1024x1024

# Regras de construção
all: $(BUILD_DIR)/$(PROJECT_NAME_CLI) $(BUILD_DIR)/$(PROJECT_NAME_GUI)

$(BUILD_DIR)/$(PROJECT_NAME_CLI): $(SOURCES_CLI) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_CLI) $(LDFLAGS)

$(BUILD_DIR)/$(PROJECT_NAME_GUI): $(SOURCES_GUI) $(HEADERS) $(GLADE_FILE)
	mkdir -p $(BUILD_DIR)
	cp $(GLADE_FILE) $(BUILD_DIR)  # Copia o arquivo GLADE para o diretório de construção
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES_GUI) $(LDFLAGS)

# Regras de instalação
install: $(BUILD_DIR)/$(PROJECT_NAME_CLI) $(BUILD_DIR)/$(PROJECT_NAME_GUI)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BUILD_DIR)/$(PROJECT_NAME_CLI) $(DESTDIR)$(BINDIR)
	cp $(BUILD_DIR)/$(PROJECT_NAME_GUI) $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(DATADIR)
	cp $(GLADE_FILE) $(DESTDIR)$(DATADIR)
	cp $(DESKTOP_FILE) $(DESTDIR)/usr/share/applications
	mkdir -p $(DESTDIR)$(ICONSDIR)
	# Copia os ícones para as respectivas pastas
	for SIZE in $(ICON_SIZES); do \
		mkdir -p $(DESTDIR)$(ICONSDIR)/$$SIZE; \
		cp -r $(ICONS_DIR)/$$SIZE/* $(DESTDIR)$(ICONSDIR)/$$SIZE/; \
	done

# Regras de limpeza
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean install
