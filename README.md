# Automated Foosball Table
This is the repository that houses the necessary code to drive our automated foosball table.

## Usage
*This is going to be added after rewrite*


## Dependencies

### OpenCV
The instructions for downloading and installing OpenCV (for linux) can be found [here.](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)

### Spinnaker SDK
**NOTE**
This dependency is technically optional, given that the program can be run without a live camera. However, it must be compiled as "make no-camera". This will not attempt to include the Spinnaker headers or link the respective libraries.

One of the most crucial dependencies is the Spinnaker SDK to interface with the camera.
To install the SDK, download it from [here.](https://www.flir.com/products/spinnaker-sdk/)

Once the SDK is unzipped, running the installation script will put the proper libraries in the `/usr/include` directory.
