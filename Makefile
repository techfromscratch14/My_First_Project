BUILD_DIR = build 

.PHONY: build clean flash

build:
	cmake -B $(BUILD_DIR) -G Ninja
	cmake --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

flash:
	cmake --build $(BUILD_DIR) --target flash