# sine.c

This is a simple scaffold for using `cmake` to build C programs related to [project μ](https://mu.krj.st). 

## why

In my experience learning and preparing to give a talk introducing C++ audio development, I spent a good couple of days working on configuring my environment and build system. I quickly realized: 

- **configuration** is a big part of the process which might deter folks, especially in a single session
- we might want **something to feel good** that provides immediate feedback (like running the jack server)
- DSP is a rather vast topic, but **contributing to this project  doesn't have to be so daunting**. For this we introduce [CMSC388V](https://mu.krj.st/overture/) and [ThinkDSP](https://github.com/AllenDowney/ThinkDSP).


These instructions are for Mac OS X. Even so, once the jack server is running on Windows or Linux, and your build system is working to link the jack.h header (to link the Jack library)...

You will have a way to connect to your audio device in your C programs. Instructions for other systems may be included in the future. 

Jack is a good tool for the toolbox, for learning, audio development or production. We won't always need it but it is good to introduce here. 

## install Jack:
*and `pkg-config` for the following sanity check.*

```
brew install jack pkg-config
```


#### start the the `jackd` service:
`/usr/local/bin/jackd -X coremidi -d coreaudio`

Leave this terminal window open. You should see your audio and midi devices enummerated :smile:.

## sanity check

Before moving on to `cmake` you can check if everything is installed and working using `clang` directly.

#### build and run using `clang`:

`clang sine.c $(pkg-config --cflags --libs jack)`

This will produce a defaultly named `a.out` binary you can run:  

```
$ ./a.out
```

If the Jack server is running, you should hear a sine wave. 


### `cmake`

Because `cmake` is the defacto build system for [JUCE](https://juce.com), et al, this scaffold also introduces `cmake` to link the Jack library. As we move through [project μ](https://mu.krj.st) it will be cool to be able to manage our excursions with `cmake`. 

```
mkdir build && cd build
cmake .. # this will generate your Makefile
cmake --build . 
# alternatively 'make' should work fine here
# if that is a meaningful connection for you.
```

You should now have a binary called `sine` in your `build` folder you can run just the same as `a.out` above. 


## links, follow up questions, and further reading

#### maths

We don't want to reinvent the wheel or try to cover the entirety of the maths involved in this subject. To participate in this lab you don't need to know much, you can just follow along with the coding. But there is math. 

- What do you know about sine waves? 



##### Euler's Formula

$$
e^{i\theta} = cos(\theta) + i \times sin(\theta)
$$

- [What is Euler's formula actually saying?](https://www.youtube.com/watch?v=ZxYOEwM6Wbk)   
- [Integration and the fundamental theorem of calculus](https://www.youtube.com/watch?v=rfG8ce4nNh0)
- [Introduction to integral calculus | Accumulation and Riemann sums](https://www.youtube.com/watch?v=__Uw1SXPW7s)




#### linked libraries

- what are dynamically linked libraries (DLL, dylib)?
- what are statically linked libraries?

#### ThinkDSP

[This book](https://github.com/AllenDowney/ThinkDSP)  is in Python, but it is a relatively gentle intoduction to DSP.


#### CMSC388V (Project µ)

*Project µ may be a label I came up with for CMSC388V, I can't recall. You may hear me refer to it this way.*

- [CMSC388V](https://mu.krj.st/overture/)
> Will you learn how to build a digital audio workstation (DAW) or a production-level VST plugin from scratch after taking this course? Probably not. But I hope in the end you can find out that writing audio or music applications is not as difficult as it seems to be, and not that simple either—full of quirks you need to consider—but you know where to pick up the necessary skills needed to proceed further.


#### RtAudio and openFrameworks
I had thought perhaps we could touch on [openFrameworks](https://openframeworks.cc), which includes [RtAudio](http://www.music.mcgill.ca/~gary/rtaudio/).

- [Here's how to play a saw wave using RtAudio](http://www.music.mcgill.ca/~gary/rtaudio/playback.html).

### TBD: The follow up C++ repo.

This repo will be expanded to include more examples. Again, it's main purpose was to provide an entry point and scaffolding (so that we don't lose people on the first day). 

I will be posting a similar repo for `cmake` with C++ soon. It may just be the RtAudio example above. I have a number of other concepts and resources to introduce. If there is anything jumping out in your mind which isn't introduced here (Faust and Vult come to my mind) it might be because they belong in the follow up repo. That repo will most likely be the intermediary between this one and a demo VST project, but it might be the VST project itself. I want to be able to introduce most of this in one or two hour sessions. 

#### Designing Audio FX Plugins 2nd Edition

This is the book I bought to learn how to develop VSTs. I am listing it last here because the information above  is a great introduction before you start shedding on Will's book. His book is also concise, similar to the way this information has been presented, only straight into VST development.


[https://www.willpirkle.com](https://www.willpirkle.com)
[A not entirely glowing review of the book!](https://www.youtube.com/watch?v=8VPdm-yNCsk)





