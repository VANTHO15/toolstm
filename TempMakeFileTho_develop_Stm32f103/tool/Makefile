ifeq ($(MODULE),)
    $(error export MODULE before starting tests: example export MODULE=gpio   )
endif

ifeq ($(TEST),)
    $(error export TEST before starting tests: example export TEST=gpio_TS_001   )
endif

include ../test/test_$(MODULE)/make/$(TEST)

PRO_DIR		:= .
PATH_OUTPUT = ../output/$(TEST)
PROJ_NAME	:= $(MODULE)

INCLUDE_DIRS += $(PRO_DIR)/include
SRC_DIRS     += $(PRO_DIR)/source


SRC_FILES      := $(foreach SRC_DIRS,$(SRC_DIRS),$(wildcard $(SRC_DIRS)/*))
INCLUDE_FILES  := $(foreach INCLUDE_DIRS,$(INCLUDE_DIRS),$(wildcard $(INCLUDE_DIRS)/*))

LINKER_FILE	    := $(PRO_DIR)/linker/stm32f1_discovery.ld
COMPILER_DIR 	:= C:/GCC_THO

CC				:= $(COMPILER_DIR)/bin/arm-none-eabi-gcc
LD				:= $(COMPILER_DIR)/bin/arm-none-eabi-ld

INCLUDE_DIRS_OPT := $(foreach INCLUDE_DIRS,$(INCLUDE_DIRS),-I$(INCLUDE_DIRS))

CC_OPT			:= -mcpu=cortex-m3 -c -O0 -g -mthumb $(INCLUDE_DIRS_OPT)
LD_OPT			:= -T $(LINKER_FILE) -Map $(PATH_OUTPUT)/$(PROJ_NAME).map


OJB_FILES  := $(notdir $(SRC_FILES))
OJB_FILES  := $(subst .c,.o,$(OJB_FILES))
PATH_OJBS  := $(foreach OJB_FILES,$(OJB_FILES),$(PATH_OUTPUT)/$(OJB_FILES))

vpath %.c $(SRC_DIRS)
vpath %.h $(INCLUDE_DIRS)

build: $(OJB_FILES) $(LINKER_FILE)
	$(LD) $(LD_OPT) $(PATH_OJBS) -o $(PATH_OUTPUT)/$(PROJ_NAME).elf
	$(COMPILER_DIR)/arm-none-eabi/bin/objcopy.exe -O ihex "$(PATH_OUTPUT)/$(PROJ_NAME).elf" "$(PATH_OUTPUT)/$(PROJ_NAME).hex"
	size $(PATH_OUTPUT)/$(PROJ_NAME).elf

%.o: %.c $(INCLUDE_FILES)
	mkdir -p $(PATH_OUTPUT)
	$(CC) $(CC_OPT) -c $< -o $(PATH_OUTPUT)/$@

.PHONY: clean
clean:
	rm -rf $(PATH_OUTPUT)

.PHONY: run
run:
	$(PRO_DIR)/ST-LINKUtility/ST-LINK_CLI.exe -p "$(PATH_OUTPUT)/$(PROJ_NAME).hex" 0x08000000
	$(PRO_DIR)/ST-LINKUtility/ST-LINK_CLI.exe -rst
	rm -fr $(PATH_OUTPUT)/$(TEST).html
	rm -fr $(PATH_OUTPUT)/result.log
.PHONY: report
# nếu file có data thì else thì 
report:
	$(PRO_DIR)/ST-LINKUtility/ST-LINK_CLI.exe -r32 0x20000000 4 | grep -i 00000000 > $(PATH_OUTPUT)/result.log;\
	if [[ -s $(PATH_OUTPUT)/result.log ]]; then \
		echo "Test $(TEST) PASSED "; \
		cp $(PRO_DIR)/temp_report/FileReport.html $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/CONTENT_TESTSUITE/$(TEST_DETAILS)/g' $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/NAME_TESTCASE/$(TEST)/g' $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/CONTENT_TESTCASE/$(TEST_CASE_CONTENT_1)/g' $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/STATUS_TEST/OK/g' $(PATH_OUTPUT)/$(TEST).html; \
	else \
		echo "Test $(TEST) FAILED "; \
		cp $(PRO_DIR)/temp_report/FileReport.html $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/CONTENT_TESTSUITE/$(TEST_DETAILS)/g' $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/NAME_TESTCASE/$(TEST)/g' $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/CONTENT_TESTCASE/$(TEST_CASE_CONTENT_1)/g' $(PATH_OUTPUT)/$(TEST).html; \
		sed -i 's/STATUS_TEST/NOT OK/g' $(PATH_OUTPUT)/$(TEST).html; \
	fi
.PHONY: info
info:
	@ls ../test/test_$(MODULE)/make
log-%:
	@echo $($(subst log-,,$@))