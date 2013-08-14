var gpioexport = require( __dirname + "/libc/build/Release/gpioexport" );

//Prepare GPIO-18 for output
gpioexport.prepareGPIO(18);

//set GPIO 18 to HIGH
gpioexport.set(18);

setTimeout(function(){

    //set GPIO 18 to LOW
    gpioexport.unset(18);

}, 2000);


