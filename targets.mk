# add the cutflowclean as an additional target to the clean target
clean: cutflowclean

cutflowclean:
	@rm -f $(MYPXLANA)/cutflow.*

cutflow:
	@echo "Generating cutflow..."
	$(MYPXLANA)/python/gencutflow.py -f $(MYPXLANA)/cutflow.h $(MYPXLANA)/ledge.cc
