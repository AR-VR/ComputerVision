PROJECT := program
SCRIPT :=$(PROJECT) #add arguments

#set the compiler option
CFLAGS := -Wall \
					-arch x86_64\
					-g

CC := clang++ -lstdc++

OBJECT_DIR :=obj/
SOURCE_DIR :=src/

#header include
INCLUDES := -I./$(SOURCE_DIR) \
						-I/usr/local/include

OPENCV_LIBS := -lopencv_calib3d -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_highgui -lopencv_imgproc -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab

#library link (-L dynamic library, -l static lib)
LD_LIBS := -L/usr/local/lib/ $(OPENCV_LIBS) 
					 
SOURCES :=$(wildcard $(SOURCE_DIR)*.cpp) 
OBJECTS :=$(SOURCES:$(SOURCE_DIR)%.cpp=$(OBJECT_DIR)%.o)

$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(LD_LIBS)

$(OBJECT_DIR)%.o: $(SOURCE_DIR)%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

all: $(PROJECT) $(OBJECTS)

run: all
	./$(SCRIPT)

clean:
		rm -rf $(OBJECT_DIR)*.o $(PROJECT)
