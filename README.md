node-fast-gpio
==============

This is a node.js gpio library for the raspberry pi using the fastest way to export values via C (http://codeandlife.com/2012/07/03/benchmarking-raspberry-pi-gpio-speed/).

## Installation

Clone the repository after that use
```sh
$ chmod +x configure.sh
$ ./configure.sh
```
to install node-gyp and build the library.


In your node.js file just require the library:
```js
var gpioexport = require( __dirname + "/libc/build/Release/gpioexport" );
```

Now you can prepare your GPIO for output using:
```js
gpioexport.prepareGPIO(18);
```

After that you can set your GPIO to HIGH (turn on) anytime with:
```js
gpioexport.set(18);
```

Or you can set your GPIO to LOW (turn off) anytime with:
```js
gpioexport.unset(18);
```

The library only supports GPIOs as output. But in the fastest possible way from node.js.
It uses the standard GPIO numbers.