default:
	@echo
	@echo "---------------------OS MAKE-------------------"
	@echo
	mainframer.sh 'cd os && make'
	@echo
	@echo "---------------------APPS MAKE------------------"
	@echo
	mainframer.sh 'cd apps/q3_trial && make'
run:
	clear
	@echo
	@echo "----------------------OS MAKE-------------------"
	@echo
	mainframer.sh 'cd os && make'
	@echo
	@echo "---------------------APPS MAKE------------------"
	@echo
	mainframer.sh 'cd apps/q3_trial && make'
	@echo
	@echo "---------------------APPS RUN-------------------"
	@echo
# 	mainframer.sh 'cd os && make run'
	mainframer.sh 'cd apps/q3_trial && make run'

clean:
	mainframer.sh 'cd os && make clean'
	mainframer.sh 'cd apps/q3_trial && make clean'

