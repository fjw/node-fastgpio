#include <node.h>
#include <v8.h>

using namespace v8;


// Access from ARM Running Linux

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

void setup_io();


//----





//----



Handle<Value> PrepareGPIO(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 1) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsNumber() || args[0]->NumberValue() <= 0 || args[0]->NumberValue() > 31) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    int num = (int) args[0]->NumberValue();

    INP_GPIO(num); // must use INP_GPIO before we can use OUT_GPIO
    OUT_GPIO(num);

    return scope.Close(Number::New(1));
}



Handle<Value> UnSet(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 1) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsNumber() || args[0]->NumberValue() <= 0 || args[0]->NumberValue() > 31) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    int num = (int) args[0]->NumberValue();

    GPIO_CLR = 1<<num;

    return scope.Close(Number::New(1));

}

Handle<Value> Set(const Arguments& args) {
    HandleScope scope;

    if (args.Length() != 1) {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if (!args[0]->IsNumber() || args[0]->NumberValue() <= 0 || args[0]->NumberValue() > 31) {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    int num = (int) args[0]->NumberValue();

    GPIO_SET = 1<<num;

    return scope.Close(Number::New(1));
}



/*
    Constructor des Moduls
*/
void init(Handle<Object> exports) {

    //GPIO vorbereiten
    setup_io();




    exports->Set(String::NewSymbol("prepareGPIO"), FunctionTemplate::New(PrepareGPIO)->GetFunction());
    exports->Set(String::NewSymbol("set"), FunctionTemplate::New(Set)->GetFunction());
    exports->Set(String::NewSymbol("unset"), FunctionTemplate::New(UnSet)->GetFunction());

}

/*
    GPIO Memory Setup
*/
void setup_io()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
        ThrowException(Exception::TypeError(String::New("can't open /dev/mem")));
        exit(-1); //?
    }

    /* mmap GPIO */
    gpio_map = mmap(
        NULL,             //Any adddress in our space will do
        BLOCK_SIZE,       //Map length
        PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
        MAP_SHARED,       //Shared with other processes
        mem_fd,           //File to map
        GPIO_BASE         //Offset to GPIO peripheral
    );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
        ThrowException(Exception::TypeError(String::New("mmap error" ))); //errno also set! weggenommen: + (int)gpio_map
        exit(-1);
    }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;

}

NODE_MODULE(fastgpio, init)