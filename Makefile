# Default trial directory (can be overridden from command line)
TRIAL ?= q3_trial

default:
	@echo
	@echo "---------------------OS MAKE-------------------"
	@echo
	mainframer.sh 'cd os && make'
	@echo
	@echo "---------------------APPS MAKE------------------"
	@echo
	mainframer.sh 'cd apps/$(TRIAL) && make'

run:
	clear
	@echo
	@echo "----------------------OS MAKE-------------------"
	@echo
	mainframer.sh 'cd os && make'
	@echo
	@echo "---------------------APPS MAKE------------------"
	@echo
	mainframer.sh 'cd apps/$(TRIAL) && make'
	@echo
	@echo "---------------------APPS RUN-------------------"
	@echo
# 	mainframer.sh 'cd os && make run'
	mainframer.sh 'cd apps/$(TRIAL) && make run'

clean:
	mainframer.sh 'cd os && make clean'
	mainframer.sh 'cd apps/$(TRIAL) && make clean'