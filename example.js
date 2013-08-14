var fgpio = require( "fastgpio" );

//Prepare GPIO-18 for output
fgpio.prepareGPIO(18);

//set GPIO 18 to HIGH
fgpio.set(18);

setTimeout(function(){

    //set GPIO 18 to LOW
    fgpio.unset(18);

}, 2000);


