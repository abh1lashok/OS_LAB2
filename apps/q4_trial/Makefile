default:
	cd makeprocs; make 
	cd producerH2O; make 
	cd producerN3; make 
	cd consumerN3; make 
	cd consumerH2O; make 
	cd consumerN_O2; make 

clean:
	cd makeprocs; make clean
	cd producerH2O; make clean
	cd producerN3; make clean
	cd consumerN3; make clean
	cd consumerH2O; make clean
	cd consumerN_O2; make clean

run:
	cd ../../bin; dlxsim -x os.dlx.obj -a -u makeprocs.dlx.obj 5 3 10;
