//
// Created by 16182 on 6/16/2020.
//

#ifndef TUTORIALS_SOURCEDIR_H
#define TUTORIALS_SOURCEDIR_H

//emscripten file system does not respect the directory of the executable like the native c++ does,
//this is a workaround, but there are probably better systems
#error replace the path below with the correct path for your system
#define ROOTDIRECTORY std::string("C://your/path/to/minimumGL/")


#endif //TUTORIALS_SOURCEDIR_H
