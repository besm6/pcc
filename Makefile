
all:    pcc-libs/Makefile pcc/Makefile
	$(MAKE) -C pcc-libs -j
	$(MAKE) -C pcc -j

install: pcc-libs/Makefile pcc/Makefile
	sudo $(MAKE) -C pcc-libs install
	sudo $(MAKE) -C pcc install

clean:  pcc-libs/Makefile pcc/Makefile
	$(MAKE) -C pcc-libs clean
	$(MAKE) -C pcc clean

distclean: pcc-libs/Makefile pcc/Makefile
	$(MAKE) -C pcc-libs distclean
	$(MAKE) -C pcc distclean

pcc-libs/Makefile:
	cd pcc-libs && ./configure

pcc/Makefile:
	cd pcc && ./configure
