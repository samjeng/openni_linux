# README #

This README is for the user who

* Want to develop application with LIPS 3D depth camera.
* Already has a LIPS camera module on hand.
* The target platform is Linux
* Develop application with OpenNI 1.5

If you don't have one and are interesting with it, please contact with us by e-mail [info@lips-hci.com](mailto:info@lips-hci.com)

### System Requirements ###

* Ubuntu 14.04 or later

### Prepare Software Development Environment ###

#### Install OpenCV 2 ####

* Install required packages for building OpenCV 2.

```
sudo apt-get install cmake pkg-config libgtk2.0-dev

```

* Download OpenCV source code from https://github.com/opencv/opencv/releases.

* Extract and enter OpenCV root folder, for example
```
cd ~/opencv-2.4.11
```
* Create a folder for cmake and change directory to it, for example,
```
mkdir build && cd build
```
* Enter following command to generate cmake files
```
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..
```
* Once generation is done, enter make command to start the build
```
make
```
* Then, install OpenCV to your system, administrator permission may required.
```
sudo make install
```
#### Install USB-1.0 library ####

```
sudo apt-get install libusb-1.0-0

```

#### Install LIPS 3D depth camera SDK ####

* Download SDK from [LIPS SDK] (http://www.lips-hci.com/products/sdk/)

* Extract the tarball of LIPS 3D depth camera SDK

* Enter the SDK folder and install the SDK with administrator permission
```
sudo ./install.sh
```

### Download LIPS Sample Code ###

#### Install GIT ####

```
sudo apt-get install git-core
```

#### Clone sample code ####
Clone the project into the SDK folder.

```
git clone https://github.com/lips-hci/openni_linux.git LIPS_Sample
```

#### Build Samples ####
##### NiRecorder #####
```
cd LIPS_Sample/NiRecorder
CXX=g++ make
```

##### NiSimpleViewer #####
```
cd LIPS_Sample/NiSimpleViewer
CXX=g++ make
```

#### Build your own application ####
You can base the samples we provided to develop your own application. What you need to know to edit Makefile are:

* Append the source files' name to SRC
* According the path related to SDK, modify the CPPFLAGS and LDFLAGS appropriately. i.e., you man need to add -I and -L to the correct location.
* You can also use Clang to compile your application by change CXX from g++ to clang.

### ARM Platform Application Development ###
For LIPSedge AT developer, since LIPSedge AT is ARM-based CPU architecture platform, we suggest to use [docker] (https://www.docker.com/) to develop the application to save your time of establishing a cross-compile OpenNI-installed environment. You could pull the image from Docker Hub by following command
```
docker pull lips/aarch32_openni
```
Be noted, please install QEMU to emulate ARM CPU architecture on your work station, like the commands below:
```
apt-get install qemu qemu-user-static binfmt-support
update-binfmts --enable qemu-arm
```
Then you could use 'docker run' command to launch the container
```
docker run -it -v /usr/bin/qemu-arm-static:/usr/bin/qemu-arm-static lips/aarch32_openni /bin/bash
```
#### Build LIPS Sample ####
Please refer the section "Download LIPS Sample Code" to download sample code from github, and modify the compile flags defined in Makefile, i.e., modify CPPFLAGS and LDFLAGS from
```
-I../../Include
-L../../Lib
```
to
```
-I/usr/include/ni
-L/usr/lib
```
Then compile the source in the same way
```
CXX=g++ make
```
