# Compiler
CXX = g++

# Targets
TARGET_VIRUS = virus
TARGET_HOST = host   # Make sure this matches exactly
SEED = seed

# Victim binaries
VICTIM1 = victim1
VICTIM2 = victim2
VICTIM3 = victim3

# Source files
SRC_VIRUS = virus.cpp
SRC_HOST = host.cpp

# Build rules
all: $(TARGET_VIRUS) $(TARGET_HOST) $(VICTIM1) $(VICTIM2) $(VICTIM3) $(SEED)

$(TARGET_VIRUS): $(SRC_VIRUS)
	@$(CXX) -Wall $(SRC_VIRUS) -o $(TARGET_VIRUS) && echo "Successfully compiled $(SRC_VIRUS)" || { echo "Failed to compile $(SRC_VIRUS)"; exit 1; }

$(TARGET_HOST): $(SRC_HOST)
	@$(CXX) -Wall $(SRC_HOST) -o $(TARGET_HOST) && echo "Successfully compiled $(SRC_HOST)" || { echo "Failed to compile $(SRC_HOST)"; exit 1; }

# Create victim binaries
$(VICTIM1):
	@cp /bin/ls ./$(VICTIM1)

$(VICTIM2):
	@cp /usr/bin/wc ./$(VICTIM2)

$(VICTIM3):
	@cp /usr/bin/file ./$(VICTIM3)

# Create the seed binary by combining virus, sentinel, and host
$(SEED): $(TARGET_VIRUS) $(TARGET_HOST)
	@cp $(TARGET_VIRUS) $(SEED)
	@printf '\xde\xad\xbe\xef' >> $(SEED)
	@cat $(TARGET_HOST) >> $(SEED)

# Clean up the binaries and generated files
.PHONY: clean
clean:
	@echo "Cleaning up binaries..."
	@rm -f $(TARGET_VIRUS) $(TARGET_HOST) $(SEED) $(VICTIM1) $(VICTIM2) $(VICTIM3)
	@echo "Cleanup complete."

