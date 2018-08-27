.PHONY: FORCE
all: FORCE
	$(MAKE) -C .. bitcoin5000_qt test_bitcoin5000_qt
clean: FORCE
	$(MAKE) -C .. bitcoin5000_qt_clean test_bitcoin5000_qt_clean
check: FORCE
	$(MAKE) -C .. test_bitcoin5000_qt_check
bitcoin5000-qt bitcoin5000-qt.exe: FORCE
	 $(MAKE) -C .. bitcoin5000_qt
