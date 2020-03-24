# PLODD - Pong++'s Logging Object Declarations and Definitions:

> WARNING: This ReadMe isn't up to date at all! Check the TODO list, it's on there :{

PLODD (pronounced the same way as the word *plod*) is an implementation of the logging library used in my game Pong++ (Coming Soon). PLODD is meant to be light-weight, easy to use, and easy to incorporate into your project. It's logging "look" is as follows:

```
[<Time>]:<Logger's-name>:<Logging-level>:<Message>
```
<h6><sub>Lots of colons :)</sub></h6>

The syntax of PLODD's objects is shown in the following excerpt from `test.cpp`:

```C++
...
#include <PLODD/file_logger.h>
#include <PLODD/console_logger.h>
#include <PLODD/both.h>

void test_file_logging(){
    logging::file.debug("HEYO! This is a file debug."); 
    logging::file.info("HEYO! This is a file info.");
    logging::file.warn("HEYO! This is a file warn.");
    logging::file.error("HEYO! This is a file error.");
}

void test_console_logging(){
    logging::console.debug("HEYO! This is a file debug."); 
    logging::console.info("HEYO! This is a file info.");
    logging::console.warn("HEYO! This is a file warn.");
    logging::console.error("HEYO! This is a file error.");
}

void test_both_logging(){
    logging::both.debug("HEYO! This is a debug log from the \"both\" logger, heh.");
    logging::both.info("HEYO! This is a info log from the \"both\" logger, heh.");
    logging::both.warn("HEYO! This is a warn log from the \"both\" logger, heh.");
    logging::both.error("HEYO! This is a error log from the \"both\" logger, heh.");
}
...
```

These are only the default loggers, you can make your own! 

Here's an example:

```C++
#include <PLODD/console_logger.h>
#include <PLODD/file_logger.h>
#include <PLOD/both.h>

console_logger my_console_logger("MY_NEW_CONSOLE_LOGGERS_NAME", logging::LEVEL_DEBUG);
my_console_logger.debug("YES! It works!")

file_logger my_file_logger("MY_NEW_FILE_LOGGERS_NAME", logging::LEVEL_INFO);
my_file_logger.init_files("path/other/than/other/loggers/path")
//                         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                         Files are not locked; If you 
//                         use multipule your program will 
//                         probably crash and burn.
my_file_logger.info("HELLO WORLD!")

both_logger my_both_logger;
my_both_logger.debug("HI... My name is Joe... I am going to both the console and file default loggers.")
//                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//                    Logs only to the DEFAULT loggers. Logger "collections" are coming soon. :D
```

As seen in the above two examples, a file logger must be initialized. If you don't you won't be writing to any files. So, you do the following:

```C++
logging::file.init_files(); //Logs are put in the current working directory.
```
or
```C++
logging::file.init_files("Your/path/here"); //Logs are put in the explicit path.
```

---

# Logger Types:


## Multi-File Logger

The multi-file logger outputs to three separate files:

 * `main.log`
 * `debug.log`
 * `errors.log`

`main.log` logs logs that are at or above the current logging level the `logging::file` object is set at. Said level can be set with the `.change_level()` method. You can also name with the `.change_name()` method. You can use the enumeration that comes along with `file_logger.h` and `console_logger.h` to change the level more explicitly: `logging::file.change_level(logging::LEVEL_WARN);`. The default is `logging::LEVEL_INFO`.

As for the other files, `debug.log` file logs all messages, and `errors.log` logs only errors. All files are truncated on thier init. 

## Console Logger

The "console" logger outputs logs to `std::cout`. It's logging level can be set just like the file logging instance since it also inherits from the `base_logger` class. 

The console logger uses colours to help focus your attention on what matters:

1. A light gray for `DEBUG`.
2. A bold white for `INFO`.
3. A bold yellow for `WARN`.
4. A bold red for `ERROR`.

## Both Logger

The `both` logger is a nifty little utility you use when you want to call the same method on all the other ***DEFAULT*** loggers. This could call the `debug` method, could call the `change_level` method, or call anything else that is universally accepted by `base_logger` children. It's syntax is simple:

`logging::both.[method to call]([arguments])`

--just like any other logger. :D

## Logger Collections:

### **>COMING SOON<**

---

# Other:

## PLODD as a CMake `SHARED` Library:

`cmake -G "[generator]" -DBUILD_SHARED_LIBS=ON [path]`

## Licensure:

**PUBLIC DOMAIN!!!!!**

"Anyone can read and contribute to our codebase, guys. Isn't that great?" <br>
*Corporate meeting room goes silent.*


