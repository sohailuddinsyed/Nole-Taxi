CC = g++
 
# executables
NoleTaxi: NoleTaxi.cpp MyRBT.h MyHeap.h
	$(CC) MyHeap.h
	$(CC) MyRBT.h
	$(CC) NoleTaxi.cpp -o NoleTaxi


clean:
	$(RM) $(TARGET)