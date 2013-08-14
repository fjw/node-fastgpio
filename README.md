node-fastgpio
==============

This is a small **node.js** GPIO library for the **Raspberry Pi** using the fastest way to export values via C (http://codeandlife.com/2012/07/03/benchmarking-raspberry-pi-gpio-speed/).


Installation:

```sh
npm install fastgpio
```

In your node.js file just require the library:
```js
var fastgpio = require( "fastgpio" );
```

Now you can prepare your GPIO for output using:
```js
fastgpio.prepareGPIO(18);
```

After that you can set your GPIO to HIGH (turn on) anytime with:
```js
fastgpio.set(18);
```

Or you can set your GPIO to LOW (turn off) anytime with:
```js
fastgpio.unset(18);
```

The library only supports GPIOs as output, but in the fastest possible way from node.js.
**It uses the standard Raspberry Pi GPIO numbers.**