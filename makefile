CC = g++
 
# executables
gatorTaxi: gatorTaxi.cpp
	$(CC) MyHeap.h
	$(CC) MyRBT.h
	$(CC) gatorTaxi.cpp -o gatorTaxi


clean:
	$(RM) $(TARGET)