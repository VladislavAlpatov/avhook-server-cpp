# AVhook Server Repository
![banner](https://i.imgur.com/2AVGRge.png)

Welcome to the README.md file for our C++ server project!

This project is designed to provide a high-performance, efficient server implementation written in C++. Our server is designed to handle a large number of concurrent connections, while still providing fast response times and low latency.

In this README file, you will find information on how to build, install, and run our server, as well as information on the various features and functionality it provides. We'll cover everything from system requirements and installation instructions to configuration options and API documentation.

We hope that this README file will provide you with all the information you need to get started with our C++ server project, and we look forward to hearing your feedback and suggestions. Thank you for considering our server for your project needs!

# API Documentation
Here, you will find detailed information about the various APIs exposed by our server, including their endpoints, input and output formats, and expected behaviors. This section is designed to help you integrate your application with our server, and to ensure that you are using our APIs correctly and effectively.

We recommend that you review this section carefully before using our server, and that you refer back to it as needed during development. If you have any questions or issues with our APIs, please don't hesitate to reach out to our support team for assistance.
[Click Here.](https://app.gitbook.com/o/i69j9b2SXakPr86nnfg5/s/pP38wppAaA2YbS31sw3F/)

# Building
This section contains information on how to build and compile our server project, including any dependencies or prerequisites you may need to install. We've provided step-by-step instructions to help you get up and running quickly.
At the moment, you can build a project under Linux.

Note: nlohmann-json is already installed int (srv/lib/nlohmann-json), if you 
want to update it, just replace all files in nlohmann-json folder.
1) `sh /scripts/auto-dependency-install.sh`
### CMake
Before we start, make sure you have CMake installed on your development machine. You can download it from the official website or install it using a package manager on your operating system.

To build this project, we'll be using a `CMakeLists.txt` file to define project settings, dependencies, and build targets. This file is used by CMake to generate build artifacts, such as makefiles, which are used to build the project.

In the following sections, we'll walk you through the steps required to build this project on your platform using CMake. If you encounter any issues or have questions, don't hesitate to reach out to our support team.
To build project just run a sh script
1) `sh /scripts/build-server-rel` - will build server for release.
2) `sh /scripts/build-server-dbg`- will build server for debug (no compiler optimization, logging observers are turned on).

### Running
After building got to `out/Release` or `out/Debug` folder and create file with name
`config.json` and paste this:
1)  Creating config file
    ```json
    {
      "database_path" : "/paste/path/to/database/here",
      "port": 7777
    }
    ```
    Replace `"/paste/path/to/database/here"` with your own database path.

    You also can change listening port if you want to.
2) Executing server binary
    Run `./server` command in terminal.  If you see `[LOG] Server online` it means you did it!

